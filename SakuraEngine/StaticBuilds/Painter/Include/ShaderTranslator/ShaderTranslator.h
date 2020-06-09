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
 * @Date: 2020-06-08 23:19:06
 * @LastEditTime: 2020-06-09 13:39:49
 */ 
#pragma once
#include <Core/Containers/Containers.h>
#include "../Shader.h"
#include <dxc/dxcapi.h>         // Be sure to link with dxcompiler.lib.

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
    struct ShaderCompileDesc 
    {
        Sakura::swstring shaderFileName;
        Sakura::swstring entryPoint;
        Sakura::swstring binaryPath;
        Sakura::swstring pdbPath;
        ShaderStageFlags shaderStage;
        // Advanced Options
        bool bEnableDebugInformation = false;
        Sakura::smap<Sakura::swstring, Sakura::swstring> macroDefs;
        Sakura::svector<Sakura::swstring> compilerArgs;
    };
    struct ShaderCompileQuery
    {
        CComPtr<IDxcBlob> compiledBlob;
        CComPtr<IDxcBlobUtf16> shaderName;
        CComPtr<IDxcBlob> shaderHash;
    };
    /**
     * @description: Accepts HLSL shader file and translate to variant
     * shader backends like GLSL, MSL, etc.
     * SM support level keeps same as respository:
     * https://github.com/microsoft/DirectXShaderCompiler
     * @author: SaeruHikari
     */
    struct HLSLShaderCompiler
    {
        bool Compile(const ShaderCompileDesc& compileDesc,
            const ShaderILBC target = ShaderILBC::SPIRV,
            ShaderCompileQuery* query = nullptr);
        CComPtr<IDxcUtils> pUtils;
        CComPtr<IDxcCompiler3> pCompiler;
        CComPtr<IDxcIncludeHandler> pIncludeHandler;
    };

    struct SPIRVShaderTranslator
    {
        bool Compile(
            const uint32_t *ir_, size_t word_count,
            const ShadingLanguage sl = ShadingLanguage::MSL);
    };
}