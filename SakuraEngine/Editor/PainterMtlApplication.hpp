/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-05-29 02:48:38
 * @LastEditTime: 2020-06-05 00:55:55
 */ 
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
        return half4(0.0, 1.0, 1.0, 1.0);
    }
)""";

const float vertexData[] =
{
    0.0f,  1.f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
};

#include <EASTL/chrono.h>

class PainterMetalApp
{
public:
    void run()
    {
        // Init SDL Window
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        auto win = SDL_CreateWindow(
            "Metal",
            0, 0,
            1920, 1080, 
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
        if(!win)
        {
            Sakura::log::debug_error<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to create SDL window!");
        }
        // Create Painter Objects
        Painter* painter = Painter::Create<Metal::PainterMetal>(true);
        auto asyncExt = painter->EnableExtension<AsyncComputeExtension>();
        if(!asyncExt)
        {
            Sakura::log::debug_error<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to enable Async Compute Extension.");
        }
        // Create SwapChain
        SwapChainMetal* chain 
            = (SwapChainMetal*)Metal::SwapChainMetal::Create(*painter, 3, win);
        // Create Shader
        auto shader = Shader::Create(*painter, shadersSrc, strlen(shadersSrc));
        // Create RenderPipeline
        RenderPipelineDescripor desc;
        desc.shaderFunctions = {
            ShaderFunction(VertexStage, shader, "vertFunc"), 
            ShaderFunction(PixelStage, shader, "fragFunc")
        };
        RenderPipelineColorAttachmentDescriptor colorAttachment;
        colorAttachment.format = PixelFormat::B8G8R8A8_UNORM;
        desc.colorAttachments = {
            colorAttachment
        };
        auto renderPipeline = RenderPipeline::Create(*painter, desc);
        // Create Vertex Buffer
        auto vertexBuffer = GPUBuffer::Create(*painter,
            GPUBuffer::BufferUsage::VertexBuffer,
            GPUResource::ResourceOptions::Upload,
            sizeof(vertexData), vertexData);

        auto startTime = eastl::chrono::high_resolution_clock::now();
        eastl::unique_ptr<RenderCommandBuffer> commandBuffer;
        eastl::unique_ptr<RenderPass> renderPass;
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
                    run = 0; return;
                case SDL_WINDOWEVENT:
					if (evt.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
						std::cout << "MESSAGE:Resizing window...\n";
					}
                default:
                    break;
                }
            }
            auto currentTime = eastl::chrono::high_resolution_clock::now();
            float time = eastl::chrono::duration<float, eastl::chrono::seconds::period>(currentTime - startTime).count();
            if(time > 0.0016)
            {
                startTime = currentTime;
                run = (run % 600) + 1;
                RenderPassColorAttachmentDescriptor cAttachment;
                cAttachment.clearColor = {0.00167f * run, .6, 1, 1};
                cAttachment.texture = &chain->GetDrawableTexture();
                cAttachment.loadAction = LoadAction::Clear;
                cAttachment.storeAction = StoreAction::Store;
                RenderPassDescriptor pdesc;
                pdesc.colorAttachments.push_back(cAttachment);
                renderPass.reset(RenderPass::Create(*painter, pdesc));
                commandBuffer.reset(
                    RenderCommandBuffer::Create(*painter));
                if(renderPass != nullptr)
                {
                    commandBuffer->BeginRenderPass(*renderPass.get());
                    commandBuffer->SetRenderPipeline(*renderPipeline);
                    commandBuffer->SetVertexBuffer(*vertexBuffer);
                    commandBuffer->Draw(0, 3);
                    commandBuffer->EndRenderPass();
                    commandBuffer->Present(chain->GetDrawable());
                }
                commandBuffer->Commit();
                commandBuffer->WaitUntilCompleted();
                run++;
            }
        }
        return;
    }
};