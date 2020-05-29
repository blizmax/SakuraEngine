#import "../Include/SDLSupport.h"
#import "SDL2/SDL.h"
#import "SDL2/SDL_syswm.h"
#import <MetalKit/MetalKit.h>

namespace Sakura::Graphics::Metal
{
    SwapChainMetal::NSWindowH GetNSWindow(SDL_Window* window)
    {
        PainterMetal::debug_info("Created a swap chain from SDL_Window!");
        if(window == nullptr)
        {
            PainterMetal::error("SwapChainMetal: null SDL_Window received!");
        }
        SDL_SysWMinfo info;
        if(!SDL_GetWindowWMInfo(window, &info))
            PainterMetal::error("SDL2 ToolKit: Failed to Get SDL WindowWMInfo!");
        NSWindow *nswindow = info.info.cocoa.window;
        if(nswindow == nullptr)
        {
            PainterMetal::error("SDL2 Tkit: Failed to get NSWindow handle from SDL Window!");
        }
        SwapChainMetal::NSWindowH result
            = ns::Handle{ (__bridge void*)nswindow };
        return result;
    }
}