/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-05-01 17:06:33
 * @LastEditTime: 2020-05-02 19:17:58
 */
#include "CommandBufferMtl.h"
#include "CommandQueueMtl.h"
#include "../CGDMetal.hpp"

using namespace Sakura::Graphics::Mtl;

Sakura::Graphics::CommandBuffer* CGDMtl::CreateCommandBuffer(
    const CommandQueue& queue, ECommandType type, bool bTransiant) const
{
    return new CommandBufferGraphicsMtl(entity,
        ((CommandQueueMtl&)queue));
}

CommandBufferEntityMtl::CommandBufferEntityMtl(
    const CGDEntityMtl& _entity, CommandQueueMtl& queue)
    :entity(_entity)
{
    commandBuffer = queue.queue.CommandBuffer();
    if(!commandBuffer.Validate())
    {
        CGDMtl::debug_error("CGDMtl: Failed to create Metal CommandBuffer!");
    }
}

CommandBufferGraphicsMtl::CommandBufferGraphicsMtl(
    const CGDEntityMtl& entity, CommandQueueMtl& queue)
    :CommandBufferEntityMtl(entity, queue)
{
    
}

void CommandBufferGraphicsMtl::Begin()
{
    bOpen = true;
}

void CommandBufferGraphicsMtl::End()
{
    bOpen = false;
}

void CommandBufferGraphicsMtl::Reset()
{
    encoder.EndEncoding();
    commandBuffer = commandBuffer.GetCommandQueue().CommandBuffer();
}

void CommandBufferGraphicsMtl::ResourceBarrier(GpuTexture& toTransition,
    const ImageLayout oldLayout, const ImageLayout newLayout,
    const TextureSubresourceRange& subresourceRange)
{
    
}

std::unique_ptr<Sakura::Graphics::SwapChain> swapChain;
void CommandBufferGraphicsMtl::BeginRenderPass(
    GraphicsPipeline* gp, const RenderTargetSet& rts)
{
    if(bOpen)
    {
        auto desc = ((SwapChainMtl*)swapChain.get())->GetRenderPassDescriptor();
        desc.GetColorAttachments()[0].SetClearColor(mtlpp::ClearColor(
            0.f, 1.f, 1.f, 1.f));
        encoder = commandBuffer.RenderCommandEncoder(desc);
        if(swapChain.get() != nullptr)
        {
            CGDMtl::debug_error("CGDMtl: Failed to create Metal RenderCommandEncoder!");
        }
    }
    else
        CGDMtl::debug_error("CGDMtl: Please Begin CommandBuffer before BeginRenderPass!");
}

void CommandBufferGraphicsMtl::EndRenderPass()
{
    encoder.EndEncoding();
    commandBuffer.Commit();
    commandBuffer.WaitUntilCompleted();
}

void CommandBufferGraphicsMtl::Draw(uint32 vertexCount, uint32 instanceCount,
    uint32 firstVertex, uint32 firstInstance)
{
    
}

void CommandBufferGraphicsMtl::DrawIndexed(const uint32_t indicesCount,
    const uint32_t instanceCount)
{

}

void CommandBufferGraphicsMtl::BindVertexBuffer(const GpuBuffer& vb)
{
    
}

void CommandBufferGraphicsMtl::BindIndexBuffer(const GpuBuffer& ib,
    const IndexBufferStride stride)
{

}

void CommandBufferGraphicsMtl::BindRootArguments(
    const PipelineBindPoint bindPoint,
    const RootArgument** arguments, uint32_t argumentNum)
{

}