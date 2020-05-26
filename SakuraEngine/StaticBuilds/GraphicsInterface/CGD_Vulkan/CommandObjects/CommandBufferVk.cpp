/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Vulkan implementation of CommandBuffer
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-11 01:25:06
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-05-06 23:45:30
 */
#include "../../GraphicsCommon/CommandObjects/CommandBuffer.h"
#include "../CGD_Vulkan.h"
#include "CommandBufferVk.h"
#include "Core/EngineUtils/log.h"
#include "../GraphicsObjects/GraphicsPipelineVk.h"
#include "../GraphicsObjects/ComputePipelineVk.h"
#include "../CommandObjects/CommandQueueVk.h"
#include "../GraphicsObjects/RootSignatureVk.h"
#include "../ResourceObjects/GpuResourceVk.h"
#include <set>

#ifndef PROFILING_POOL
//#define PROFILING_POOL 
#endif

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Vk;

CommandBuffer* CGDVk::AllocateCommandBuffer(const CommandQueue& queue,
    ECommandType type, bool bTransiant)
{
    std::lock_guard<std::mutex> LockGurad(contextAllocationMutex);
#ifdef PROFILING_POOL
    for (auto i = 0; i < contextPools[type].size(); i++)
    {
        std::cout << "context no." << i << ": " << 
            ((vkGetFenceStatus(entityVk.device,
            ((CommandBufferVk*)contextPools[type][i].get())->recordingFence) == VK_SUCCESS) ? "free    " : "executing    ") << std::endl;
    }
#endif
    if(!availableContexts[type].empty())
    {
        auto res = availableContexts[type].front();
        if(vkGetFenceStatus(entityVk.device, 
            CommandBufferVk::FromCommandBuffer(res)->recordingFence) == VK_SUCCESS)
        {
            availableContexts[type].pop();
            return res;
        }
    }
    CommandBuffer* newContext = nullptr;
    switch (type)
    {
    case ECommandType::ECommandBufferGraphics:
        newContext = new CommandBufferGraphicsVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
        break;
    case ECommandType::ECommandBufferCompute:
		newContext = new CommandBufferComputeVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
		break;
    case ECommandType::ECommandBufferCopy:
		newContext = new CommandBufferCopyVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
		break;
    default:
        break;
    }
    auto result = std::unique_ptr<CommandBuffer>(newContext);
    auto ptr = result.get();
    contextPools[type].push_back(std::move(result));
    return ptr;
}

CommandBuffer* CGDVk::CreateCommandBuffer(const CommandQueue& queue, ECommandType type, bool bTransiant) const
{
	CommandBuffer* newContext = nullptr;
	switch (type)
	{
	case ECommandType::ECommandBufferGraphics:
		newContext = new CommandBufferGraphicsVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
		break;
	case ECommandType::ECommandBufferCompute:
		newContext = new CommandBufferComputeVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
		break;
	case ECommandType::ECommandBufferCopy:
		newContext = new CommandBufferCopyVk(*this,
            ((const CommandQueueVk&)queue).queueFramilyIndex, bTransiant);
		break;
	default:
		break;
	}
    return newContext;
}

void CGDVk::FreeAllCommandBuffers(ECommandType type)
{
    std::lock_guard<std::mutex> LockGurad(contextAllocationMutex);
    for(auto i = 0; i < contextPools[type].size(); i++)
    {
        availableContexts[type].push(contextPools[type][i].get());
    }
}

void CGDVk::FreeCommandBuffer(CommandBuffer* context)
{
    std::lock_guard<std::mutex> LockGurad(contextAllocationMutex);
    auto vkContext = (CommandBufferVk*)context;
    availableContexts[context->GetCommandBufferType()].push(context);
}


CommandBufferVk::CommandBufferVk(const CGDVk& _cgd, std::uint32_t family, bool bTransiant)
    :cgd(_cgd)
{
	auto indices = family; 
    VkCommandPoolCreateInfo poolInfo = {}; 
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO; 
    poolInfo.queueFamilyIndex = indices; 
    poolInfo.flags = bTransiant ? VK_COMMAND_POOL_CREATE_TRANSIENT_BIT : 0; 
    if (vkCreateCommandPool(_cgd.GetCGDEntity().device, &poolInfo, 
        nullptr, &commandPool) != VK_SUCCESS)
    {
        CGDVk::error("Vulkan: failed to create command pool!"); 
        throw std::runtime_error("failed to create command pool!"); 
    }
    VkCommandBufferAllocateInfo allocInfo = {}; 
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO; 
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; 
    allocInfo.commandBufferCount = 1; 
    if (vkAllocateCommandBuffers(_cgd.GetCGDEntity().device, &allocInfo, 
        & commandBuffer) != VK_SUCCESS)
    {
        CGDVk::error("Vulkan: failed to allocate command buffers!");
        throw std::runtime_error("failed to allocate command buffers!"); 
    }
    VkFenceCreateInfo fenceInfo = {}; 
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO; 
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT; 
    if (vkCreateFence(_cgd.GetCGDEntity().device, &fenceInfo, 
        nullptr, &recordingFence) != VK_SUCCESS)
    {
        CGDVk::error("failed to create synchronization objects for a CmdBuffer!"); 
        throw std::runtime_error("failed to create synchronization objects for a CmdBuffer!"); 
    }
}

CommandBufferGraphicsVk::CommandBufferGraphicsVk(const CGDVk& _cgd,
    std::uint32_t family, bool bTransiant)
    : CommandBufferVk(_cgd, family, bTransiant)
{
    
}

CommandBufferComputeVk::CommandBufferComputeVk(const CGDVk& _cgd,
    std::uint32_t family, bool bTransiant)
    : CommandBufferVk(_cgd, family, bTransiant)
{
   
}

CommandBufferCopyVk::CommandBufferCopyVk(const CGDVk& _cgd,
    std::uint32_t family, bool bTransiant)
    : CommandBufferVk(_cgd, family, bTransiant)
{
    
}

template<typename Buffer>
void Destruct(Buffer* _this)
{
	vkWaitForFences(_this->cgd.GetCGDEntity().device,
		1, &_this->recordingFence, VK_TRUE, UINT64_MAX);
	vkDestroyFence(_this->cgd.GetCGDEntity().device, _this->recordingFence, nullptr);
	vkDestroyCommandPool(_this->cgd.GetCGDEntity().device, _this->commandPool, nullptr);
}

CommandBufferGraphicsVk::~CommandBufferGraphicsVk()
{
    Destruct(this);
}
CommandBufferComputeVk::~CommandBufferComputeVk()
{
    Destruct(this);
}
CommandBufferCopyVk::~CommandBufferCopyVk()
{
    Destruct(this);
}

template<typename Buffer>
void BeginBuffer(Buffer* _this)
{
	_this->bOpen = true;
	vkResetCommandPool(_this->cgd.GetCGDEntity().device,
        _this->commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	if (vkBeginCommandBuffer(_this->commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		CGDVk::error("Vulkan: failed to begin recording command buffer!");
		throw std::runtime_error("failed to begin recording command buffer!");
	}
}
void CommandBufferGraphicsVk::Begin()
{
    BeginBuffer(this);
}
void CommandBufferComputeVk::Begin()
{
    BeginBuffer(this);
}
void CommandBufferCopyVk::Begin()
{
    BeginBuffer(this);
}

void CommandBufferGraphicsVk::BindVertexBuffer(const GpuBuffer& vb)
{
    VkDeviceSize offsets[] = {0};
    VkBuffer bufs[] = {((const GpuResourceVkBuffer&)vb).buffer};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, bufs, offsets);
}

void CommandBufferGraphicsVk::BindIndexBuffer(const GpuBuffer& ib,
    const IndexBufferStride stride)
{
    VkBuffer buf = ((const GpuResourceVkBuffer&)ib).buffer;
    auto index = (stride == IndexBufferStride::IndexBufferUINT16) 
        ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32;
    vkCmdBindIndexBuffer(commandBuffer, buf, 0, index);
}

void CommandBufferComputeVk::BeginComputePass(ComputePipeline* cp)
{
    vkCp = (ComputePipelineVk*)cp;
    if(vkCp->pipeline == VK_NULL_HANDLE)
    {
        CGDVk::error("CGD: please bind VkPipeline first!");
        throw std::runtime_error("CGD: please bind VkPipeline first!");
    }
    vkCmdBindPipeline(commandBuffer,
        VK_PIPELINE_BIND_POINT_COMPUTE, ((ComputePipelineVk*)cp)->pipeline);
}

void CommandBufferComputeVk::DispatchCompute(uint32 groupCountX,
    uint32 groupCountY, uint32 groupCountZ)
{
    vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

void CommandBufferGraphicsVk::BeginRenderPass(
    GraphicsPipeline* gp, const RenderTargetSet& rts)
{
    vkGp = (GraphicsPipelineVk*)gp;
    if(vkGp->graphicsPipeline == VK_NULL_HANDLE)
    {
        CGDVk::error("CGD: please bind VkPipeline first!");
        throw std::runtime_error("CGD: please bind VkPipeline first!");
    }
    vkCmdBindPipeline(commandBuffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS, vkGp->graphicsPipeline);
    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vkGp->progress.renderPass;
    renderPassInfo.framebuffer = vkGp->FindFrameBuffer(rts);
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent =
        Transfer(rts.rts[0].resource.GetExtent());

    std::vector<VkClearValue> clearValues(rts.rtNum);
    for(auto i = 0u; i < rts.rtNum; i++)
    {
        clearValues[i] = *(VkClearValue*)&(rts.rts[i].clearValue);
    }
    
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();
    vkCmdBeginRenderPass(commandBuffer, 
        &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void CommandBufferGraphicsVk::BindRootArguments(const PipelineBindPoint bindPoint,
    const RootArgument** arguments, uint32_t argumentNum)
{
    std::vector<VkDescriptorSet> descriptorSets(argumentNum);
    auto set = 9999;
    for(auto i = 0u; i < argumentNum; i++)
    {
        auto cset = ((const RootArgumentVk**)arguments)[i]->targetSet;
        descriptorSets[i] = 
            (((const RootArgumentVk**)arguments)[i])->descriptorSet;
        set = cset < set ? cset : set;
    }
	vkCmdBindDescriptorSets(commandBuffer, Transfer(bindPoint),
		vkGp->pipelineLayout, set, argumentNum, descriptorSets.data(), 0, nullptr);
	// static samplers
    vkCmdBindDescriptorSets(commandBuffer, Transfer(BindPointGraphics),
		vkGp->pipelineLayout, 3, 1,
		((RootArgumentVk*)arguments[0])->staticSamplers, 0, nullptr);
}

void CommandBufferComputeVk::BindRootArguments(const PipelineBindPoint bindPoint,
	const RootArgument** arguments, uint32_t argumentNum)
{
	std::vector<VkDescriptorSet> descriptorSets(argumentNum);
	auto set = 9999;
	for (auto i = 0u; i < argumentNum; i++)
	{
		auto cset = ((const RootArgumentVk**)arguments)[i]->targetSet;
		descriptorSets[i] =
			(((const RootArgumentVk**)arguments)[i])->descriptorSet;
		set = cset < set ? cset : set;
	}
	vkCmdBindDescriptorSets(commandBuffer, Transfer(bindPoint),
		vkCp->pipelineLayout, set, argumentNum, descriptorSets.data(), 0, nullptr);
}

void CommandBufferGraphicsVk::Draw(uint32 vertexCount, uint32 instanceCount,
    uint32 firstVertex, uint32 firstInstance)
{
    vkCmdDraw(commandBuffer, vertexCount,
        instanceCount, firstVertex, firstInstance);
}

void CommandBufferGraphicsVk::DrawIndexed(const uint32_t indicesCount,
    const uint32_t instanceCount)
{
    vkCmdDrawIndexed(commandBuffer, indicesCount,
        instanceCount, 0, 0, 0);
}

void CommandBufferCopyVk::CopyResource(GpuBuffer& src, GpuBuffer& dst,
    const uint64 size, const uint64 srcOffset, const uint64 dstOffset)
{
    VkBufferCopy copyRegion = {};
    copyRegion.dstOffset = dstOffset;
    copyRegion.srcOffset = srcOffset;
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer,
        ((GpuResourceVkBuffer&)src).buffer,
        ((GpuResourceVkBuffer&)dst).buffer, 1, &copyRegion);
}

void CommandBufferCopyVk::CopyResource(GpuBuffer& src, GpuTexture& dst,
    const BufferImageCopy& info)
{
    VkBufferImageCopy region = {};
    region.bufferOffset = info.bufferOffset;
    region.bufferRowLength = info.bufferRowLength;
    region.bufferImageHeight = info.bufferImageHeight;
    region.imageSubresource.aspectMask = info.imageSubresource.aspectMask;
    region.imageSubresource.mipLevel = info.imageSubresource.mipLevel;
    region.imageSubresource.baseArrayLayer = info.imageSubresource.baseArrayLayer;
    region.imageSubresource.layerCount = info.imageSubresource.layerCount;
    region.imageOffset = *(VkOffset3D*)&info.imageOffset;
    region.imageExtent = *(VkExtent3D*)&info.imageExtent;
    vkCmdCopyBufferToImage(commandBuffer,
        ((GpuResourceVkBuffer&)src).buffer,
        ((GpuResourceVkImage&)dst).image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}

void CommandBufferCopyVk::CopyResource(GpuBuffer& src, GpuTexture& dst,
        const uint32_t imageWidth, const uint32_t imageHeight,
        const ImageAspectFlags aspectFlags, const uint64_t srcOffset)
{
    VkBufferImageCopy region = {};
    region.bufferOffset = srcOffset;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = aspectFlags;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset = {0, 0, 0};
    region.imageExtent = {
        imageWidth,
        imageHeight,
        1
    };
    vkCmdCopyBufferToImage(commandBuffer,
        ((GpuResourceVkBuffer&)src).buffer,
        ((GpuResourceVkImage&)dst).image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}

// Create an image memory barrier for changing the layout of
// an image and put it into an active command buffer
// See chapter 11.4 "Image Layout" for details

void setImageLayout(
    VkCommandBuffer cmdbuffer,
    VkImage image,
    VkImageLayout oldImageLayout,
    VkImageLayout newImageLayout,
    VkImageSubresourceRange subresourceRange,
    VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask)
{
    // Create an image barrier object
    VkImageMemoryBarrier imageMemoryBarrier {};
    imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imageMemoryBarrier.oldLayout = oldImageLayout;
    imageMemoryBarrier.newLayout = newImageLayout;
    imageMemoryBarrier.image = image;
    imageMemoryBarrier.subresourceRange = subresourceRange;
    // Source layouts (old)
    // Source access mask controls actions that have to be finished on the old layout
    // before it will be transitioned to the new layout
    switch (oldImageLayout)
    {
    case VK_IMAGE_LAYOUT_GENERAL:
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
        break;
    case VK_IMAGE_LAYOUT_UNDEFINED:
        // Image layout is undefined (or does not matter)
        // Only valid as initial layout
        // No flags required, listed only for completeness
        imageMemoryBarrier.srcAccessMask = 0;
        break;
    case VK_IMAGE_LAYOUT_PREINITIALIZED:
        // Image is preinitialized
        // Only valid as initial layout for linear images, preserves memory contents
        // Make sure host writes have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
        // Image is a color attachment
        // Make sure any writes to the color buffer have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
        // Image is a depth/stencil attachment
        // Make sure any writes to the depth/stencil buffer have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
        // Image is a transfer source 
        // Make sure any reads from the image have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        break;

    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
        // Image is a transfer destination
        // Make sure any writes to the image have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
        // Image is read by a shader
        // Make sure any shader reads from the image have been finished
        imageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        break;
    default:
        // Other source layouts aren't handled (yet)
        break;
    }

    // Target layouts (new)
    // Destination access mask controls the dependency for the new image layout
    switch (newImageLayout)
    {
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
        // Image will be used as a transfer destination
        // Make sure any writes to the image have been finished
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_GENERAL:
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
        break;
        
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
        // Image will be used as a transfer source
        // Make sure any reads from the image have been finished
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        break;

    case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
        // Image will be used as a color attachment
        // Make sure any writes to the color buffer have been finished
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
        // Image layout will be used as a depth/stencil attachment
        // Make sure any writes to depth/stencil buffer have been finished
        imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        break;

    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
        // Image will be read in a shader (sampler, input attachment)
        // Make sure any writes to the image have been finished
        if (imageMemoryBarrier.srcAccessMask == 0)
        {
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT | VK_ACCESS_TRANSFER_WRITE_BIT;
        }
        imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        break;
    default:
        // Other source layouts aren't handled (yet)
        break;
    }

    // Put barrier inside setup command buffer
    vkCmdPipelineBarrier(
        cmdbuffer,
        srcStageMask,
        dstStageMask,
        0,
        0, nullptr,
        0, nullptr,
        1, &imageMemoryBarrier);
}

void resourceBarrier(VkCommandBuffer& commandBuffer, GpuTexture& texture,
    const ImageLayout oldLayout, const ImageLayout newLayout,
    const TextureSubresourceRange& range)
{
	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = *(VkImageLayout*)&oldLayout;
	barrier.newLayout = *(VkImageLayout*)&newLayout;
	barrier.subresourceRange.aspectMask = range.aspectMask;
	barrier.subresourceRange.baseMipLevel = range.baseMipLevel;
	barrier.subresourceRange.levelCount = range.mipLevels;
	barrier.subresourceRange.baseArrayLayer = range.baseArrayLayer;
	barrier.subresourceRange.layerCount = range.layerCount;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;
	switch (barrier.oldLayout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_GENERAL:
		sourceStage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		break;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		break;
	default:
		CGDVk::error("unsupported layout transition!");
		throw std::invalid_argument("unsupported layout transition!");
		break;
	}
	switch (barrier.newLayout)
	{
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		break;
	case VK_IMAGE_LAYOUT_GENERAL:
		destinationStage = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
		break;
	default:
		CGDVk::error("unsupported layout transition!");
		throw std::invalid_argument("unsupported layout transition!");
		break;
	}
	setImageLayout(commandBuffer, ((const GpuResourceVkImage&)texture).image,
		Transfer(oldLayout), Transfer(newLayout),
		barrier.subresourceRange,
		sourceStage, destinationStage);
}

void CommandBufferGraphicsVk::ResourceBarrier(GpuTexture& texture,
    const ImageLayout oldLayout, const ImageLayout newLayout,
    const TextureSubresourceRange& range)
{
    resourceBarrier(commandBuffer, texture, oldLayout, newLayout, range);
}
void CommandBufferComputeVk::ResourceBarrier(GpuTexture& texture,
	const ImageLayout oldLayout, const ImageLayout newLayout,
	const TextureSubresourceRange& range)
{
	resourceBarrier(commandBuffer, texture, oldLayout, newLayout, range);
}
void CommandBufferCopyVk::ResourceBarrier(GpuTexture& texture,
	const ImageLayout oldLayout, const ImageLayout newLayout,
	const TextureSubresourceRange& range)
{
	resourceBarrier(commandBuffer, texture, oldLayout, newLayout, range);
}

void generateMipmaps(VkCommandBuffer& commandBuffer, GpuTexture& texture, Format format,
    uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels)
{
	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.image = ((GpuResourceVkImage&)texture).image;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;
	barrier.subresourceRange.levelCount = 1;

	int32_t mipWidth = texWidth;
	int32_t mipHeight = texHeight;

	for (uint32_t i = 1; i < mipLevels; i++) {
		barrier.subresourceRange.baseMipLevel = i - 1;
		barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

		vkCmdPipelineBarrier(commandBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &barrier);

		VkImageBlit blit = {};
		blit.srcOffsets[0] = { 0, 0, 0 };
		blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
		blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blit.srcSubresource.mipLevel = i - 1;
		blit.srcSubresource.baseArrayLayer = 0;
		blit.srcSubresource.layerCount = 1;
		blit.dstOffsets[0] = { 0, 0, 0 };
		blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
		blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blit.dstSubresource.mipLevel = i;
		blit.dstSubresource.baseArrayLayer = 0;
		blit.dstSubresource.layerCount = 1;

		vkCmdBlitImage(commandBuffer,
			((GpuResourceVkImage&)texture).image,
			VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			((GpuResourceVkImage&)texture).image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1, &blit,
			VK_FILTER_LINEAR);

		barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		vkCmdPipelineBarrier(commandBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &barrier);

		if (mipWidth > 1) mipWidth /= 2;
		if (mipHeight > 1) mipHeight /= 2;
	}

	barrier.subresourceRange.baseMipLevel = mipLevels - 1;
	barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

	vkCmdPipelineBarrier(commandBuffer,
		VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
		0, nullptr,
		0, nullptr,
		1, &barrier);
}

void CommandBufferComputeVk::GenerateMipmaps(GpuTexture& texture, Format format,
    uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels)
{
	VkFormatProperties formatProperties;
	vkGetPhysicalDeviceFormatProperties(
		cgd.GetCGDEntity().physicalDevice, Transfer(format), &formatProperties);

	if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
	{
		CGDVk::error("texture image format does not support linear blitting!");
		throw std::runtime_error("texture image format does not support linear blitting!");
	}
    generateMipmaps(commandBuffer, texture, format, texWidth, texHeight, mipLevels);
}

void CommandBufferCopyVk::GenerateMipmaps(GpuTexture& texture, Format format,
	uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels)
{
	VkFormatProperties formatProperties;
	vkGetPhysicalDeviceFormatProperties(
		cgd.GetCGDEntity().physicalDevice, Transfer(format), &formatProperties);

	if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
	{
		CGDVk::error("texture image format does not support linear blitting!");
		throw std::runtime_error("texture image format does not support linear blitting!");
	}
	generateMipmaps(commandBuffer, texture, format, texWidth, texHeight, mipLevels);
}


void CommandBufferGraphicsVk::Reset()
{
	vkResetCommandPool(cgd.GetCGDEntity().device,
		commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	if (bOpen)
		End();
}
void CommandBufferComputeVk::Reset()
{
	vkResetCommandPool(cgd.GetCGDEntity().device,
		commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
	if (bOpen)
		End();
}
void CommandBufferCopyVk::Reset()
{
    vkResetCommandPool(cgd.GetCGDEntity().device,
        commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT); 
    if(bOpen)
        End();
}

void CommandBufferGraphicsVk::EndRenderPass()
{
    vkCmdEndRenderPass(commandBuffer);
}

void CommandBufferGraphicsVk::End()
{
    bOpen = false;
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) 
    {
        CGDVk::error("Vulkan: failed to record command buffer!");
        throw std::runtime_error("failed to record command buffer!");
    }
}
void CommandBufferComputeVk::End()
{
	bOpen = false;
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
	{
		CGDVk::error("Vulkan: failed to record command buffer!");
		throw std::runtime_error("failed to record command buffer!");
	}
}
void CommandBufferCopyVk::End()
{
	bOpen = false;
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
	{
		CGDVk::error("Vulkan: failed to record command buffer!");
		throw std::runtime_error("failed to record command buffer!");
	}
}
