#import "SwapChainMtl.hpp"
#import <MetalKit/MetalKit.h>
#import "../CommandObjects/CommandBufferMtl.h"
#import "../CGDMetal.hpp"
#import "../Flags/FormatMtl.hpp"

using namespace Sakura::Graphics::Mtl; 

extern void call();

@interface WindowViewController : NSViewController<MTKViewDelegate> {
    //@public void (*m_render)(const Window&);
    //@public const Window* m_window;
}
@end

@implementation WindowViewController
-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

-(void)drawInMTKView:(nonnull MTKView *)view
{
    call();
}
@end

SwapChainMtl::MtlView::MtlView(const ns::Handle& handle)
    : ns::Object(handle) 
{
    if(!this->Validate())
    {
        CGDMtl::debug_error("Failed to create MTLView!");
    }
}

Sakura::Graphics::Extent2D SwapChainMtl::GetExtent() const
{
    return {
        uint32_t(((__bridge MTKView*)m_view.GetPtr()).frame.size.width),
        uint32_t(((__bridge MTKView*)m_view.GetPtr()).frame.size.height)};
}

SwapChainMtl::SwapChainMtl(const int width, const int height,
    const CGDMtl& _cgd, void* _window)
    :cgd(_cgd), SwapChain((const CGD&)_cgd, 2)
{
    window = (NSWindow*)_window;
    NSRect frame = NSMakeRect(0, 0, width, height);
    WindowViewController* viewController = [WindowViewController new];

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)_cgd.entity.device.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
    view.clearColor = MTLClearColorMake(
        0.0, 0.5, 1.0, 1.0);
    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];

    m_view = ns::Handle{ (__bridge void*)view };

    frameCount = ((CAMetalLayer*)((__bridge MTKView*)m_view.GetPtr()).layer).maximumDrawableCount;
    textures.resize(frameCount);
    drawableViews.resize(frameCount);
    for(auto ind = 0; ind < frameCount; ind++)
    {
        textures[ind] = nullptr;
        drawableViews[ind] = nullptr;
    }
}

mtlpp::Drawable SwapChainMtl::GetMtlDrawable() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
}

mtlpp::RenderPassDescriptor SwapChainMtl::GetRenderPassDescriptor() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentRenderPassDescriptor };
}

const GpuTexture& SwapChainMtl::GetDrawable() const
{
    if(textures[frameIndex] == nullptr)
    {
        auto result = new GpuResourceMtlTexture(cgd,
            GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture(),
            this->GetExtent(),
            Transfer(GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture().GetPixelFormat()),
            ResourceViewType::ImageView2D);
        textures[frameIndex] = result;
    }
    return *textures[frameIndex];
}

const ResourceView& SwapChainMtl::GetDrawableView() const
{

if(drawableViews[frameIndex] == nullptr)
    {
        auto result = new ResourceViewMtlImage(cgd,
            GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture(),
            Transfer(GetRenderPassDescriptor().GetColorAttachments()[0].GetTexture().GetPixelFormat()),
            ResourceViewType::ImageView2D);
        drawableViews[frameIndex] = result;
    }
    return *drawableViews[frameIndex];
}