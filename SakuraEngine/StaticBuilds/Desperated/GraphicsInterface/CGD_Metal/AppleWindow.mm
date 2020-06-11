#import "AppleWindow.hpp"
#import <MetalKit/MetalKit.h>
#import <Cocoa/Cocoa.h>
#import "CGDMetal.hpp"

AppleWindow::NsWindow::NsWindow(const ns::Handle& handle)
    : ns::Object(handle) 
{
    if(!this->Validate())
    {
        Sakura::Graphics::Mtl::CGDMtl::debug_error("Failed to create NsWindow!");
    }
}

AppleWindow::AppleWindow(int32_t width, int32_t height)
{
    NSRect frame = NSMakeRect(0, 0, width, height);
    NSWindow* _window = [[NSWindow alloc] initWithContentRect:frame
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
#else
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask)
#endif
        backing:NSBackingStoreBuffered
        defer:NO];
    _window.title = [[NSProcessInfo processInfo] processName];
    window = ns::Handle{ (__bridge void*)_window };
}

void AppleWindow::Run()
{
    NSApplication * application = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSMenu* menubar = [NSMenu new];
    NSMenuItem* appMenuItem = [NSMenuItem new];
    NSMenu* appMenu = [NSMenu new];
    NSMenuItem* quitMenuItem = [[NSMenuItem alloc] initWithTitle:@"Quit" action:@selector(stop:) keyEquivalent:@"q"];
    [menubar addItem:appMenuItem];
    [appMenu addItem:quitMenuItem];
    [appMenuItem setSubmenu:appMenu];
    [NSApp setMainMenu:menubar];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
}

