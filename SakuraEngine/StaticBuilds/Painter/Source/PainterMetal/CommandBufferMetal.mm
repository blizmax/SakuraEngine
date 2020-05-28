#import "CommandBufferMetal.h"
#import "PainterMetal.h"
#import "Fence.h"
#import "mtlpp/command_queue.hpp"

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

void RenderCommandBufferMetal::Signal(Fence& fence)
{

}

void RenderCommandBufferMetal::Wait(Fence& fence)
{

}

void RenderCommandBufferMetal::Commit()
{

}

RenderCommandBufferMetal::RenderCommandBufferMetal(
    mtlpp::CommandQueue& MetalQueue)
    :buffer(MetalQueue.CommandBuffer()), RenderCommandBuffer()
{
    if(buffer.GetPtr() == nullptr)
        PainterMetal::error("Failed to create CommandBuffer Metal!");
}

RenderCommandBuffer* PainterMetal::CreateRenderCommandBuffer()
{
    auto queue = device.NewCommandQueue();
    if(queue.GetPtr() == nullptr)
        PainterMetal::error("Failed to create CommandQueue Metal!");
    auto result = new RenderCommandBufferMetal(queue);
    return result;
}