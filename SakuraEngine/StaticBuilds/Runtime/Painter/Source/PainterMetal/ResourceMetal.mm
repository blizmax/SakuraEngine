#import "BufferMetal.h"
#import "TextureMetal.h"
#import "PainterMetal.h"
#include <iostream>
using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

std::uint32_t BufferMetal::GetSize() const
{
    return buffer.GetLength();
}

BufferMetal::BufferMetal(mtlpp::Buffer buf, const GPUBuffer::BufferUsage usage)
    :buffer(buf), GPUBuffer(usage)
{
    if(buf.GetPtr() == nullptr)
    {
        PainterMetal::error("Create Metal Buffer Failed!");
    }
}

Extent2D TextureMetal::GetExtent() const
{
    return {texture.GetWidth(), texture.GetHeight()};
}