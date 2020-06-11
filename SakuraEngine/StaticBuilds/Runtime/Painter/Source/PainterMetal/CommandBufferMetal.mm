#import "CommandBufferMetal.h"
#import "SwapChainMetal.hpp"
#import "PainterMetal.h"
#import "Fence.h"
#import "mtlpp/command_queue.hpp"
#import "RenderPipelineMetal.h"
#import "TextureMetal.h"
#import "BufferMetal.h"

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

void RenderCommandBufferMetal::Signal(Fence& fence)
{

}

void RenderCommandBufferMetal::Wait(Fence& fence)
{
    //commandBuffer.WaitUntilCompleted();
}

void RenderCommandBufferMetal::WaitUntilCompleted()
{
    commandBuffer.WaitUntilCompleted();
}

void RenderCommandBufferMetal::Commit()
{
    commandBuffer.Commit();
}

void RenderCommandBufferMetal::Present(const Drawable& drawable)
{
    commandBuffer.Present(((DrawableMetal&)drawable).drawable);
}

RenderCommandBufferMetal::RenderCommandBufferMetal(
    mtlpp::CommandQueue& MetalQueue)
    :commandBuffer(MetalQueue.CommandBuffer()), RenderCommandBuffer()
{
    if(commandBuffer.GetPtr() == nullptr)
        PainterMetal::error("Failed to create CommandBuffer Metal!");
}

RenderCommandBuffer* PainterMetal::CreateRenderCommandBuffer()
{
    if(queue.queue.GetPtr() == nullptr)
        PainterMetal::error("Failed to create CommandQueue Metal!");
    return new RenderCommandBufferMetal(queue.queue);
}


void RenderCommandBufferMetal::BeginRenderPass(const RenderPass& pass)
{
    encoder = commandBuffer.RenderCommandEncoder(
        ((RenderPassMetal&)pass).passDesc
    );
}

void RenderCommandBufferMetal::SetRenderPipeline(const RenderPipeline& pipeline)
{
    encoder.SetRenderPipelineState(
        ((RenderPipelineMetal&)pipeline).rpState);
    next_draw_prim = ((RenderPipelineMetal&)pipeline).primitiveType;
}

void RenderCommandBufferMetal::SetVertexBuffer(const GPUBuffer& vertexBuffer)
{
    if(vertexBuffer.usage != GPUBuffer::BufferUsage::VertexBuffer)
        PainterMetal::error("Buffer setted as vertex buffer must has the usage of VertexBuffer!");
    encoder.SetVertexBuffer(
        ((BufferMetal&)vertexBuffer).buffer,
        0, 0);
}

void RenderCommandBufferMetal::Draw(uint32_t vertexStart, uint32_t vertexCount)
{
    encoder.Draw(next_draw_prim, vertexStart, vertexCount);
}

void RenderCommandBufferMetal::DrawIndexed(
    uint32_t indexCount, Sakura::Graphics::IndexType indexType,
    const GPUBuffer& indexBuffer, uint32_t indexBufferOffset)
{
    if(indexBuffer.usage != GPUBuffer::BufferUsage::IndexBuffer)
        PainterMetal::error("Buffer used as index buffer must has the usage of IndexBuffer!");
    mtlpp::IndexType type = 
        (indexType == Sakura::Graphics::IndexType::UINT16 ? 
            mtlpp::IndexType::UInt16 : mtlpp::IndexType::UInt32);
    encoder.DrawIndexed(next_draw_prim, indexCount, type, 
        ((BufferMetal&)indexBuffer).buffer,
        indexBufferOffset);
}

void RenderCommandBufferMetal::EndRenderPass()
{
    encoder.EndEncoding();
}