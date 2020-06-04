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
}

void RenderCommandBufferMetal::SetVertexBuffer(const GPUBuffer& vertexBuffer)
{
    encoder.SetVertexBuffer(
        ((BufferMetal&)vertexBuffer).buffer,
        0, 0);
    encoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
}

void RenderCommandBufferMetal::EndRenderPass()
{
    encoder.EndEncoding();
}