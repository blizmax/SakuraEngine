#import "PainterMetal.h"
#import "RenderPass.h"
#import "ShaderMetal.h"
#import "Fence.h"
#import "mtlpp/library.hpp"
#import "BufferMetal.h"
#import "SwapChainMetal.hpp"
#import <MetalKit/MetalKit.h>
#import "MTLTransfer.hpp"
#import "RenderPipelineMetal.h"
#import "TextureMetal.h"

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

Fence* PainterMetal::CreateFence()
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
//CAMetalLayer *metalLayer = (CAMetalLayer*)((__bridge MTKView*)m_view.GetPtr()).layer
//id<CAMetalDrawable> *drawable = [metalLayer nextDrawable];
const Drawable& SwapChainMetal::GetDrawable() const
{
    CAMetalLayer *metalLayer = 
        (CAMetalLayer*)((__bridge MTKView*)m_view.GetPtr()).layer;
    //id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
    currentDrawable.drawable = 
        //ns::Handle{ (__bridge void*)drawable };
        ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
    return currentDrawable;
}

RenderPass& SwapChainMetal::GetDefaultRenderPass() const
{
    auto result = new RenderPassMetal(GetRenderPassDescriptor());
    return *result;
}

mtlpp::RenderPassDescriptor SwapChainMetal::GetRenderPassDescriptor() const
{
    return ns::Handle{
        (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentRenderPassDescriptor 
        };
}

GPUTexture& SwapChainMetal::GetDrawableTexture() 
{
    if(GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture().GetPtr() != nullptr)
    {
        currentDrawableTexture.texture =
            GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture();
    }
    return currentDrawableTexture;
}

//---------------RenderPipeline Creation---------------
RenderPipeline* PainterMetal::CreateRenderPipeline(
    const RenderPipelineDescripor& desc)
{
    mtlpp::RenderPipelineDescriptor rpDesc;
    for(auto& function : desc.shaderFunctions)
    {
        ShaderMetal* shaderMtl 
            = (ShaderMetal*)function.GetShader();
        mtlpp::Function func 
            = shaderMtl->shaderFunctions[function.GetEntry()];
        switch(function.GetStage())
        {
        case ShaderStageFlags::VertexStage:
            rpDesc.SetVertexFunction(func);
            continue;
        case ShaderStageFlags::PixelStage:
            rpDesc.SetFragmentFunction(func);
            continue;
        default:
            PainterMetal::warn("PainterMetal: Shader of this stage not supported!");
        }
    }
    for(std::size_t i = 0u; i < desc.colorAttachments.size(); i++)
    {
        auto&& attachment = desc.colorAttachments[i];
        rpDesc.GetColorAttachments()[i].SetBlendingEnabled(attachment.blendingEnabled);
        rpDesc.GetColorAttachments()[i].SetPixelFormat(Transfer(attachment.format));
        if(attachment.blendingEnabled)
        {
            rpDesc.GetColorAttachments()[i].SetRgbBlendOperation(
                Transfer(attachment.rgbBlendOp));
            rpDesc.GetColorAttachments()[i].SetSourceRgbBlendFactor(
                Transfer(attachment.srcRGBBlendFactor));
            rpDesc.GetColorAttachments()[i].SetDestinationRgbBlendFactor(
                Transfer(attachment.dstRGBBlendFactor));
            rpDesc.GetColorAttachments()[i].SetAlphaBlendOperation(
                Transfer(attachment.alphaBlendOp));
            rpDesc.GetColorAttachments()[i].SetSourceAlphaBlendFactor(
                Transfer(attachment.srcAlphaBlendFactor));
            rpDesc.GetColorAttachments()[i].SetDestinationAlphaBlendFactor(
                Transfer(attachment.dstAlphaBlendFactor));
        }
        rpDesc.GetColorAttachments()[i].SetWriteMask(attachment.colorWriteMask);
    }
    auto rpState 
        = device.NewRenderPipelineState(rpDesc, nullptr);
    auto result = new RenderPipelineMetal(rpState);
    return result;
}


//---------------RenderPass Creation---------------
RenderPassMetal::RenderPassMetal(
    const Sakura::Graphics::RenderPassDescriptor& desc)
{
    passDesc.SetRenderTargetArrayLength(desc.colorAttachments.size());
    if(desc.depthAttachment.texture != nullptr)
    {
        mtlpp::RenderPassDepthAttachmentDescriptor depthAttachment;
        depthAttachment.SetClearDepth(desc.depthAttachment.clearDepth);
        depthAttachment.SetTexture(((TextureMetal*)desc.depthAttachment.texture)->texture);
        depthAttachment.SetLoadAction(Transfer(desc.depthAttachment.loadAction));
        depthAttachment.SetStoreAction(Transfer(desc.depthAttachment.storeAction));
        passDesc.SetDepthAttachment(depthAttachment);
    }
    if(desc.stencilAttachment.texture != nullptr)
    {
        mtlpp::RenderPassStencilAttachmentDescriptor stencilAttachment;
        stencilAttachment.SetClearStencil(desc.stencilAttachment.clearStencil);
        stencilAttachment.SetTexture(((TextureMetal*)desc.stencilAttachment.texture)->texture);
        stencilAttachment.SetLoadAction(Transfer(desc.stencilAttachment.loadAction));
        stencilAttachment.SetStoreAction(Transfer(desc.stencilAttachment.storeAction));
        passDesc.SetStencilAttachment(stencilAttachment);
    }
    for(uint32_t i = 0; i < desc.colorAttachments.size(); i++)
    {
        auto&& cAttachment = desc.colorAttachments[i];
        if(cAttachment.texture == nullptr)
            continue;
        passDesc.GetColorAttachments()[i].SetClearColor(
            *(mtlpp::ClearColor*)&cAttachment.clearColor);
        passDesc.GetColorAttachments()[i].SetTexture(
            ((TextureMetal*)cAttachment.texture)->texture);
        passDesc.GetColorAttachments()[i].SetLoadAction(
            Transfer(cAttachment.loadAction));
        passDesc.GetColorAttachments()[i].SetStoreAction(
            Transfer(cAttachment.storeAction));
    }
}
RenderPass* PainterMetal::CreateRenderPass(
    const Sakura::Graphics::RenderPassDescriptor& desc)
{
    return new RenderPassMetal(desc);
}