/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-11 01:38:49
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-05-01 13:22:12
 */
#pragma once
#include "../../GraphicsCommon/CommandObjects/CommandBuffer.h"
#include "vulkan/vulkan.h"

namespace Sakura::Graphics::Vk
{
    class GraphicsPipelineVk;
    class ComputePipelineVk;
    class CommandQueueVk;
}

namespace Sakura::Graphics::Vk
{
    class CommandBufferVk
    {
    public:
        VkCommandBuffer commandBuffer;
        const CGDVk& cgd;
        GraphicsPipelineVk* vkGp = nullptr;
        VkCommandPool commandPool;
        VkFence recordingFence = VK_NULL_HANDLE;
        static CommandBufferVk* FromCommandBuffer(CommandBuffer* cmdBuffer);
	protected:
		CommandBufferVk(const CGDVk& _cgd, std::uint32_t family, bool bTransiant = false);
    };

    class CommandBufferGraphicsVk : simplements CommandBufferGraphics, public CommandBufferVk
    {
        friend class CGDVk;
        friend class CommandQueueVk;
        virtual ~CommandBufferGraphicsVk() override final;
    public:
        virtual void Begin() override final;
        virtual void End() override final;
        virtual void Reset() override final;

		virtual void ResourceBarrier(GpuTexture& toTransition,
			const ImageLayout oldLayout, const ImageLayout newLayout,
			const TextureSubresourceRange & = plainTextureSubresourceRange) override final;

        // CommandBufferGraphics Interfaces
        virtual void EndRenderPass() override final;

        virtual void BeginRenderPass(
            GraphicsPipeline* gp, const RenderTargetSet& rts) override final;

        virtual void Draw(uint32 vertexCount, uint32 instanceCount,
            uint32 firstVertex, uint32 firstInstance) override final;

        virtual void DrawIndexed(const uint32_t indicesCount,
            const uint32_t instanceCount) override final;

        virtual void BindVertexBuffer(
            const Sakura::Graphics::GpuBuffer& vb) override final;
        virtual void BindIndexBuffer(const Sakura::Graphics::GpuBuffer& ib,
            const IndexBufferStride stride = IndexBufferStride::IndexBufferUINT32) override final;

        virtual void BindRootArguments(const PipelineBindPoint bindPoint,
            const RootArgument** arguments, uint32_t argumentNum) override final;
    protected:
        GraphicsPipelineVk* vkGp = nullptr;
		CommandBufferGraphicsVk(const CGDVk& _cgd, std::uint32_t family, bool bTransiant = false);
    };

    class CommandBufferComputeVk : simplements CommandBufferCompute, public CommandBufferVk
    {
		friend class CGDVk;
		friend class CommandQueueVk;
		friend class ComputePipelineVk;
		virtual ~CommandBufferComputeVk() override final;
    public:
        // CommandBuffer Interfaces
		virtual void Begin() override final;
		virtual void End() override final;
		virtual void Reset() override final;

		virtual void ResourceBarrier(GpuTexture& toTransition,
			const ImageLayout oldLayout, const ImageLayout newLayout,
			const TextureSubresourceRange & = plainTextureSubresourceRange) override final;

        // CommandBufferCompute Interfaces
		virtual void BindRootArguments(const PipelineBindPoint bindPoint,
			const RootArgument** arguments, uint32_t argumentNum) override final;

		virtual void BeginComputePass(ComputePipeline* cp) override final;

		virtual void DispatchCompute(uint32 groupCountX, uint32 groupCountY,
			uint32 groupCountZ) override final;

		virtual void GenerateMipmaps(GpuTexture& texture, Format format,
			uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels) override final;
	protected:
        ComputePipelineVk* vkCp = nullptr;
        CommandBufferComputeVk(const CGDVk& _cgd, std::uint32_t family, bool bTransiant = false);
    };

    class CommandBufferCopyVk : simplements CommandBufferCopy, public CommandBufferVk
    {
		friend class CGDVk;
		friend class CommandQueueVk;
		virtual ~CommandBufferCopyVk() override final;
	public:
		// CommandBuffer Interfaces
		virtual void Begin() override final;
		virtual void End() override final;
		virtual void Reset() override final;

		virtual void ResourceBarrier(GpuTexture& toTransition,
			const ImageLayout oldLayout, const ImageLayout newLayout,
			const TextureSubresourceRange & = plainTextureSubresourceRange) override final;

        // CommandBufferCopy Resources
		virtual void CopyResource(GpuBuffer& src, GpuBuffer& dst,
			const uint64_t size,
			const uint64_t srcOffset = 0, const uint64_t dstOffset = 0) override final;

		virtual void CopyResource(GpuBuffer& src, GpuTexture& dst,
			const uint32_t imageWidth, const uint32_t imageHeight,
			const ImageAspectFlags aspectFlags, const uint64_t srcOffset = 0) override final;

		virtual void CopyResource(GpuBuffer& src, GpuTexture& dst,
			const BufferImageCopy& info) override final;

		virtual void GenerateMipmaps(GpuTexture& texture, Format format,
			uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels) override final;
	protected:
        CommandBufferCopyVk(const CGDVk& _cgd, std::uint32_t family, bool bTransiant = false);
    };


    inline CommandBufferVk* CommandBufferVk::FromCommandBuffer(CommandBuffer* cmdBuffer)
    {
        switch (cmdBuffer->GetCommandBufferType())
        {
        case ECommandType::ECommandBufferGraphics:
            return static_cast<CommandBufferGraphicsVk*>(cmdBuffer);
        case ECommandType::ECommandBufferCompute:
            return static_cast<CommandBufferComputeVk*>(cmdBuffer);
        case ECommandType::ECommandBufferCopy:
            return static_cast<CommandBufferCopyVk*>(cmdBuffer);
        default:
            break;
        }
    }
} // namespace Sakura::Graphics

