#pragma once
#include "SakuraEngine/StaticBuilds/Painter/Include/SakuraPainter.h"
#include "SakuraEngine/StaticBuilds/Painter/Include/SDLSupport.h"
extern "C"
{
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_surface.h"
	#include "SDL2/SDL_metal.h"
	#undef main
}
#include <iostream>

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

struct NullExtension : public Extension
{
    NullExtension(int index)
    {
        
    }
    static bool EnableIf(Painter* painter)
    {
        return true;
    }
    void NullTest()
    {
        std::cout << name << std::endl;
    }
    inline static constexpr const char* name = "NullExtension";
};

const char shadersSrc[] = R"""(
    #include <metal_stdlib>
    using namespace metal;

    vertex float4 vertFunc(
        const device packed_float3* vertexArray [[buffer(0)]],
        unsigned int vID[[vertex_id]])
    {
        return float4(vertexArray[vID], 1.0);
    }

    fragment half4 fragFunc()
    {
        return half4(1.0, 0.0, 0.0, 1.0);
    }
)""";

const float vertexData[] =
{
    0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
};

class PainterMetalApp
{
public:
    void run()
    {
        // Init SDL Window
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        auto win = SDL_CreateWindow(
            "Metal",
            200, 200,
            720, 480, 
            SDL_WINDOW_RESIZABLE);
        if(!win)
        {
            Sakura::log::debug_error<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to create SDL window!");
        }

        // Create Painter Objects
        Painter* painter = Painter::Create<Metal::PainterMetal>(true);
        SwapChain* chain = Metal::SwapChainMetal::Create(*painter, win);
        auto ext = painter->EnableExtension<NullExtension>(5);
        if(ext)
            ext->NullTest();
        auto shader = Shader::Create(*painter, shadersSrc, strlen(shadersSrc));
        auto vertFunction 
            = ShaderFunction(ShaderStageFlags::VertexStage, shader, "vertFunc");
        auto pixelFunction 
            = ShaderFunction(ShaderStageFlags::PixelStage, shader, "fragFunc");
        auto renderCmdBuffer = RenderCommandBuffer::Create(*painter);
        auto vertexBuffer = GPUBuffer::Create(*painter,
            GPUBuffer::BufferUsage::VertexBuffer,
            GPUResource::ResourceOptions::Upload,
            sizeof(vertexData), vertexData);

        // Step into main loop
        int run = 1;
        while (run)
        {
            SDL_Event evt;
            while (SDL_PollEvent(&evt))
            {
                switch (evt.type)
                {
                case SDL_QUIT:
                    run = 0; break;
                case SDL_WINDOWEVENT:
					if (evt.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
						std::cout << "MESSAGE:Resizing window...\n";
					}
                default:
                    break;
                }
            }
        }
        //SDL_Metal_CreateView
        return;
    }
};