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
 * @Date: 2020-04-29 11:33:30
 * @LastEditTime: 2020-05-08 12:31:14
 */
#pragma once
extern "C"
{
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_surface.h"
	#include "SDL2/SDL_vulkan.h"
	#undef main
}
#include "SakuraEngine/StaticBuilds/GraphicsInterface/GraphicsCommon/CGD.h"
#include "SakuraEngine/StaticBuilds/GraphicsInterface/CGD_Metal/CGDMetal.hpp"
#include "SakuraEngine/StaticBuilds/GraphicsInterface/CGD_Metal/AppleWindow.hpp"
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
using namespace Sakura::Graphics;

ShaderFunction vertFunction, pixelFunction;
extern std::unique_ptr<Sakura::Graphics::SwapChain> swapChain;
std::unique_ptr<AppleWindow> appleWindow;
std::unique_ptr<CommandBufferGraphics> graphicsBuffer;
std::unique_ptr<Sakura::Graphics::Mtl::CGDMtl> cgd;
std::unique_ptr<Sakura::Graphics::Shader> shader;
std::unique_ptr<Sakura::Graphics::RenderPass> renderPass;
std::unique_ptr<Sakura::Graphics::GraphicsPipeline> graphicsPipeline;
std::unique_ptr<Sakura::Graphics::GpuBuffer> vertexBuffer;

float vertexData[] =
{
    0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

void call()
{
    graphicsBuffer.reset(
        cgd->CreateCommandBufferGraphics(*cgd->GetGraphicsQueue()));
    RenderTarget rt{
        &swapChain->GetDrawable(),
        &swapChain->GetDrawableView(), {0.f, 0.f, 0.f, 0.f}};
    RenderTargetSet rtset{&rt, 1};
    graphicsBuffer->Begin();
    graphicsBuffer->BeginRenderPass(graphicsPipeline.get(), rtset);

    graphicsBuffer->EndRenderPass();
    graphicsBuffer->End();
    cgd->Present(swapChain.get());
}

class MtlDevApp
{
public:
    void run()
    {
        Sakura::Graphics::CGDInfo cgd_info;
        cgd = std::make_unique<Sakura::Graphics::Mtl::CGDMtl>();
        cgd->Initialize(cgd_info);
        cgd->InitializeDevice(nullptr);
        shader.reset(cgd->CreateShader(shadersSrc, strlen(shadersSrc)));
        graphicsBuffer.reset(
            (CommandBufferGraphics*)cgd->CreateCommandBuffer(
                *cgd->GetGraphicsQueue(), ECommandType::ECommandBufferGraphics));

        appleWindow = std::make_unique<AppleWindow>(1920, 1080);
        swapChain.reset(
            cgd->CreateSwapChain(1920, 1080, (void*)appleWindow->GetNSWindow().GetPtr()));
        
        RenderPassCreateInfo rpInfo;
        AttachmentDescription colorAttachment;
        colorAttachment.format = R8G8B8A8_UNORM;
        rpInfo.AttachColor(colorAttachment);
        renderPass.reset(cgd->CreateRenderPass(rpInfo));
        
        GraphicsPipelineCreateInfo pplInfo;
        vertFunction 
            = ShaderFunction(ShaderStageFlags::VertexStage, shader.get(), "vertFunc");
        pixelFunction 
            = ShaderFunction(ShaderStageFlags::PixelStage, shader.get(), "fragFunc");
        pplInfo.PushShaderStage(vertFunction, pixelFunction);
        graphicsPipeline.reset(
            cgd->CreateGraphicsPipeline(pplInfo, *renderPass.get()));
        
        vertexBuffer.reset(cgd->CreateGpuBuffer(sizeof(vertexData),
            BufferUsage::VertexBuffer, Sakura::Graphics::CPUAccessFlags::ReadWrite));
        vertexBuffer->UpdateValue([&](void* mapped){
            memcpy(mapped, &vertexData, sizeof(vertexData));
        });
        appleWindow->Run();
    };
};