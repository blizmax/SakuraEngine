#import "BufferMetal.h"
#import "PainterMetal.h"

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

std::uint32_t BufferMetal::GetSize() const
{
    return 0;
}

BufferMetal::BufferMetal(mtlpp::Buffer buf, const GPUBuffer::BufferUsage usage)
    :buffer(buf), GPUBuffer(usage)
{
    if(buf.GetPtr() == nullptr)
    {
        PainterMetal::error("Create Metal Buffer Failed!");
    }
}