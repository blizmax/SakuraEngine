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
 * @LastEditTime: 2020-06-13 02:03:35
 */ 
#pragma once
#include "SakuraEngine/StaticBuilds/Runtime/Painter/Include/SakuraPainter.h"
#include "SakuraEngine/StaticBuilds/Runtime/Painter/Include/SDLSupport.h"
#include "StaticBuilds/Engine/FileManagement/FileMetaGenerator.h"
#include "StaticBuilds/Runtime/Painter/Include/ShaderTranslator/ShaderTranslator.h"
extern "C"
{
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_surface.h"
	#include "SDL2/SDL_metal.h"
	#undef main
}
#include <EASTL/chrono.h>
#include <iostream>
#include <Modules/ProjectManagement/ProjectManager.hpp>

using namespace Sakura::Graphics;
using namespace Sakura::Graphics::Metal;

const uint32_t indexData[] =
{
    0, 1, 2
};
const float vertexData[] =
{
    0.0f,  1.f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
};


class PainterMetalApp
{
public:
    void run()
    {
        using ProjectManager = Sakura::Engine::ProjectManager;
        ProjectManager projectManager;
        projectManager.RegistNewProperty(
            [](auto& manager) -> ProjectManager::ProjectProerty
            {
                YAML::Node title("TestEditor");
                YAML::Node data("MetalBackend");
                YAML::Node res;
                res[title] = data;
                return {title, res};
            });
        projectManager.NewProjectEntry(
            L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/",
            L"SakuraTest");

        // Meta Manager
        Sakura::Engine::MetaManager s_gen(
            L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest",
            L".meta");
        s_gen.NewMetaFile(
            L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest", 
            L"TrianglePS");



        // Init SDL Window
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        auto win = SDL_CreateWindow(
            "Metal",
            0, 0,
            1280, 720, 
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
        if(!win)
        {
            Sakura::log::debug_error<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to create SDL window!");
        }
        // Create Painter Objects
        Painter* painter = Painter::Create<Metal::PainterMetal>(true);
        // Enable extensions like this:
        auto asyncExt = painter->EnableExtension<AsyncComputeExtension>();
        if(!asyncExt)
        {
            Sakura::log::debug_warn<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to enable Async Compute Extension.");
        }
        // Create SwapChain
        SwapChainMetal* chain = 
            (SwapChainMetal*)Metal::SwapChainMetal::Create(*painter, 3, win);
        // Create Shader
        HLSLShaderCompiler compiler;
        SPIRVShaderTranslator translator;
        ShaderCompileDesc shaderCompileDesc;
        ShaderCompileQuery query;
        shaderCompileDesc.shaderFileName 
            = L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.hlsl";
        shaderCompileDesc.binaryPath 
            = L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.spv";
        shaderCompileDesc.shaderStage = ShaderStageFlags::VertexStage;
        shaderCompileDesc.entryPoint = L"vertFunc";
        if(!compiler.Compile(shaderCompileDesc, ShaderILBC::SPIRV, &query))
            Sakura::log::debug_warn<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to compile hlsl shader to spirv.");
        auto vsrc = translator.Translate(
            (const uint32_t*)query.GetCompiledShaderBlob(), 
            query.GetCompiledShaderSize() / sizeof(uint32_t),
            ShadingLanguage::MSL,
            L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/Triangle.mtl"
        );
        //
        shaderCompileDesc.shaderFileName 
            = L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/TrianglePS.hlsl";
        shaderCompileDesc.binaryPath 
            = L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/TrianglePS.spv";
        shaderCompileDesc.shaderStage = ShaderStageFlags::PixelStage;
        shaderCompileDesc.entryPoint = L"fragFunc";
        if(!compiler.Compile(shaderCompileDesc, ShaderILBC::SPIRV, &query))
            Sakura::log::debug_warn<Sakura::flags::DEBUG_GAME_AND_EDITOR>
                ("Failed to compile hlsl shader to spirv.");
        auto psrc = translator.Translate(
            (const uint32_t*)query.GetCompiledShaderBlob(), 
            query.GetCompiledShaderSize() / sizeof(uint32_t),
            ShadingLanguage::MSL,
            L"/Users/huangzheng/Coding/SakuraEngine/SakuraTestProject/shaders/SPIRVTest/TrianglePS.mtl"
        );
        
        
        // MTL Shader
        auto vertShader = 
            Shader::Create(*painter, vsrc.c_str(), vsrc.size());
        auto fragShader = 
            Shader::Create(*painter, psrc.c_str(), psrc.size());
        // Create RenderPipeline
        RenderPipelineDescripor desc
        {
            .shaderFunctions = {
                ShaderFunction(VertexStage, vertShader, "vertFunc"), 
                ShaderFunction(PixelStage, fragShader, "fragFunc")
            },
            .colorAttachments = {
                RenderPipelineColorAttachmentDescriptor(PixelFormat::B8G8R8A8_UNORM)
            },
            .vertexAttributes = {
                VertexAttribute("POSITION", sizeof(float) * 3, 0, VertexFormat::Float3)
            }
        };
        auto renderPipeline = RenderPipeline::Create(*painter, desc);

        // Create Vertex & Index Buffers
        auto vertexBuffer = GPUBuffer::Create(*painter,
            GPUBuffer::BufferUsage::VertexBuffer,
            GPUResource::ResourceOptions::Upload,
            sizeof(vertexData), vertexData);
        auto indexBuffer = GPUBuffer::Create(*painter,
            GPUBuffer::BufferUsage::IndexBuffer,
            GPUResource::ResourceOptions::Upload,
            sizeof(indexData), indexData);

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
						std::cout << "MESSAGE:Resizing window...\n";
                default:
                    break;
                }
            }

            auto currentTime = eastl::chrono::high_resolution_clock::now();
            float time = eastl::chrono::duration<float, eastl::chrono::seconds::period>(currentTime - startTime).count();
            if(time > 0.016)
            {
                startTime = currentTime;
                run = (run % 60) + 1;
                RenderPassDescriptor pdesc
                {
                    .colorAttachments = 
                    {
                        RenderPassColorAttachmentDescriptor 
                        {
                            .clearColor = {0.0167f * run, .6, 1, 1},
                            .loadAction = LoadAction::Clear,
                            .storeAction = StoreAction::Store,
                            .texture = &chain->GetDrawableTexture(),
                        }
                    }
                };
                renderPass.reset(RenderPass::Create(*painter, pdesc));
                commandBuffer.reset(RenderCommandBuffer::Create(*painter));
                if(renderPass != nullptr)
                {
                    commandBuffer->Present(chain->GetDrawable());
                    commandBuffer->BeginRenderPass(*renderPass.get());
                    commandBuffer->SetRenderPipeline(*renderPipeline);
                    commandBuffer->SetVertexBuffer(*vertexBuffer);
                    commandBuffer->DrawIndexed(
                        3, IndexType::UINT32, *indexBuffer, 0);
                    commandBuffer->EndRenderPass();
                }
                commandBuffer->Commit();
                commandBuffer->WaitUntilCompleted();
                run++;
            }
        }
        return;
    }
};