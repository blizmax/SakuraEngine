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
 * @Date: 2020-05-28 01:19:36
 * @LastEditTime: 2020-06-13 13:53:02
 */ 
#pragma once
#include <Core/Containers/Containers.h>

namespace Sakura::Graphics
{
    struct Painter;
    struct ShaderFunction;
}

namespace Sakura::Graphics
{
    enum class ShaderILBC
    {
        SPIRV,
        DXBC,
        DXIL,
        Count
    };
    enum class ShadingLanguage
    {
        HLSL,
        MSL,
        GLSL,
        Count
    };
    
    enum ShaderStageFlags
    {
        VertexStage         = 0x00000001,
        HullStage           = 0x00000002,
        DomainStage         = 0x00000004,
        GeometryStage       = 0x00000008,
        PixelStage          = 0x00000010,
        ComputeStage        = 0x00000020,
        AllGraphics         = 0x0000001F,
        RayGeneration       = 0x00000100,
        RayAnyHit           = 0x00000200,
        RayClosestHit       = 0x00000400,
        RayMiss             = 0x00000800,
        MeshStage           = 0x00000080,
        AmplificationStage  = 0x00001000,
    };
        
    namespace _Shader
    {
        inline const Sakura::sunordered_map<Sakura::sstring, Sakura::sstring> nullTable;
    }
    
    struct Shader
    {
        friend class ShaderFunction;
        using MacroTable = Sakura::sunordered_map<Sakura::sstring, Sakura::sstring>;
        [[nodiscard]] static Shader* Create(
            Painter&, const char* data, std::size_t dataSize,
            const MacroTable& PreprocessorMacros = _Shader::nullTable);
    protected:
        [[nodiscard]] virtual const void* NewFunctionHandle(
            const Sakura::sstring& functionName)
        {
            return nullptr;
        }
    };

    struct ShaderFunction
    {
        friend struct PainterMetal;
        ShaderFunction() = default;
        ShaderFunction(const ShaderStageFlags _stage,
            Shader* _shader, const Sakura::sstring& _entry)
            : stage(_stage), shader(_shader), entry(_entry)
        {
            funcHandle = shader->NewFunctionHandle(_entry);
        }
        auto GetStage() const 
        {
            return stage;
        }
        auto GetShader() const
        {
            return shader;
        }
        const Sakura::sstring& GetEntry() const
        {
            return entry;
        }
        const void* GetPlatformFunction()
        {
            return funcHandle;
        }
    protected:
        ShaderStageFlags stage;
        Shader* shader = nullptr;
        Sakura::sstring entry;
        // For metal, this is called MTLFunction in MTLLibrary
        // For vulkan, this handle keeps as nullptr
        // For Direct3D12, this handle keeps as nullptr
        const void* funcHandle = nullptr;
    };
}