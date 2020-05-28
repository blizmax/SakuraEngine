#import "../Include/SDLSupport.h"
#import "SDL2/SDL_metal.h"
#import <MetalKit/MetalKit.h>

namespace Sakura::Graphics::Metal
{
    SwapChainMetal::CAMetalLayer GetMtlLayer(SDL_Window* window)
    {
        PainterMetal::debug_info("Created a swap chain from SDL_Window!");
        SDL_MetalView metalview = SDL_Metal_CreateView(window);
        NSView *uiview = (__bridge NSView *)metalview;
        CAMetalLayer *metallayer = (CAMetalLayer *)uiview.layer;
        SwapChainMetal::CAMetalLayer layer{(__bridge void*)metallayer};
        return layer;
    }
}