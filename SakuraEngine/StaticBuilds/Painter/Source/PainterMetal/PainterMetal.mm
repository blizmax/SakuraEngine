#import "PainterMetal.h"
#import "RenderPass.h"
#import "ShaderMetal.h"
#import "Fence.h"
#import "mtlpp/library.hpp"
#import "BufferMetal.h"
#import "SwapChainMetal.hpp"
#import <MetalKit/MetalKit.h>

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

Fence* PainterMetal::CreateFence()
{
    return nullptr;
}

RenderPass* PainterMetal::CreateRenderPass(const RenderPassDesc& desc)
{
    return nullptr;
}

//---------------Shader Create---------------
ShaderMetal::ShaderMetal(mtlpp::Library lib)
    :library(lib)
{
    if(library.GetPtr() == nullptr)
        PainterMetal::error("Failed to create ShaderLibrary Metal!");
}

const void* ShaderMetal::NewFunctionHandle(
    const eastl::string& entryName)
{
    if(shaderFunctions.find(entryName) == shaderFunctions.end())
    {
        mtlpp::Function func = library.NewFunction(entryName.c_str());
        if(func.GetPtr() == nullptr)
        {
            PainterMetal::error("Create Metal Shader Function Failed!");
        }
        shaderFunctions[entryName] = func;
    }
    if(shaderFunctions[entryName].GetPtr() == nullptr)
        PainterMetal::error("Failed to create ShaderFunction Metal!");
    return shaderFunctions[entryName].GetPtr();
}

Shader* PainterMetal::CreateShader(
    const char* data, std::size_t dataSize, const Shader::MacroTable& macroTable)
{
    mtlpp::Library library 
        = device.NewLibrary(data, mtlpp::CompileOptions(), nullptr);
    return new ShaderMetal(library);
}


//---------------GPU Resource Create---------------
GPUBuffer* PainterMetal::CreateBuffer( 
    const GPUBuffer::BufferUsage usage, 
    const GPUResource::ResourceOptions options, 
    std::uint32_t length, const void* pointer)
{
    assert(pointer != nullptr);
    auto flag = 
        (options == GPUResource::ResourceOptions::Default) ? 
        mtlpp::ResourceOptions::StorageModePrivate :
        (options == GPUResource::ResourceOptions::Query) ?
        mtlpp::ResourceOptions::StorageModeManaged :
        mtlpp::ResourceOptions::StorageModeShared;
    return new BufferMetal(
            device.NewBuffer(pointer, length,
            mtlpp::ResourceOptions::HazardTrackingModeUntracked | flag),
        usage);
}


//---------------SwapChain Create and Initialization---------------
SwapChainMetal::SwapChainMetal(
    Painter& painter, const std::uint32_t frameCount, 
    SwapChainMetal::NSWindowH _window)
    :SwapChain(painter, frameCount)
{
    mtlpp::Device& device = ((PainterMetal&)painter).device;
    if(_window.GetPtr() == nullptr)
    {
        PainterMetal::error("SwapChainMetal: inValid NSWindow Received!");
        return;
    }
    NSWindow* window = (__bridge NSWindow*)_window.GetPtr();

    NSRect frame = NSMakeRect(0, 0,
        window.frame.size.width, window.frame.size.height);

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)device.GetPtr();
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window orderFrontRegardless];
    m_view = ns::Handle{ (__bridge void*)view };
    if(m_view.GetPtr() == nullptr)
    {
        PainterMetal::error("SwapChainMetal: MTLView Create Failed!");
        return;
    }
}

std::uint32_t SwapChainMetal::GetFrameCount() const
{
    if(m_view.GetPtr() == nullptr)
    {
        PainterMetal::error("SwapChainMetal: CAMetal Layer Ref Lost!");
        return 999999;
    }
    return ((CAMetalLayer*)((__bridge MTKView*)m_view.GetPtr()).layer).maximumDrawableCount;
}

const Drawable& SwapChainMetal::GetDrawable() const
{
    //mtlpp::Drawable db = ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
    id<MTLDrawable> drawable = ((__bridge MTKView*)m_view.GetPtr()).currentDrawable;
    uint64_t _id = drawable.drawableID;
    //uint64_t _id = db.GetDrawableID();
    if(currentDrawable.drawable.GetPtr() == nullptr ||
       _id != currentDrawable.drawable.GetDrawableID() )
    {
        currentDrawable.drawable = 
            ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
    }
    return currentDrawable;
}