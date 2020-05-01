#import "SwapChainMtl.hpp"
#import <MetalKit/MetalKit.h>
#import "../CGDMetal.hpp"

using namespace Sakura::Graphics::Mtl;

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
    //(*m_render)(*m_window);
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
    //viewController->m_render = render;
    //viewController->m_window = this;

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)_cgd.entity.device.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];

    m_view = ns::Handle{ (__bridge void*)view };
}

mtlpp::Drawable SwapChainMtl::GetDrawable() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentDrawable };
}

mtlpp::RenderPassDescriptor SwapChainMtl::GetRenderPassDescriptor() const
{
    return ns::Handle{ (__bridge void*)((__bridge MTKView*)m_view.GetPtr()).currentRenderPassDescriptor };
}