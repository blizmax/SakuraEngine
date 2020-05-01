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
 * @LastEditTime: 2020-05-02 01:18:48
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
        vertFunction 
            = ShaderFunction(ShaderStageFlags::VertexStage, shader.get(), "vertFunc");
    };
    ShaderFunction vertFunction;
    std::unique_ptr<CommandBufferGraphics> graphicsBuffer;
    std::unique_ptr<Sakura::Graphics::Mtl::CGDMtl> cgd;
    std::unique_ptr<Sakura::Graphics::Shader> shader;
};