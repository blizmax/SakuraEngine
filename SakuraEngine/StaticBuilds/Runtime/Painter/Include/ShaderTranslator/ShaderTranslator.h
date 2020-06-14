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
 * @LastEditTime: 2020-06-12 02:44:11
 */ 
#pragma once
#include <Core/Containers/Containers.h>
#include "../Shader.h"
#include <dxc/dxcapi.h>         // Be sure to link with dxcompiler.lib.

namespace Sakura::Graphics
{
    struct ShaderCompileDesc 
    {
        Sakura::wstring shaderFileName;
        Sakura::wstring entryPoint;
        Sakura::wstring binaryPath;
        Sakura::wstring pdbPath;
        ShaderStageFlags shaderStage;
        // Advanced Options
        bool bEnableDebugInformation = false;
        Sakura::map<Sakura::wstring, Sakura::wstring> macroDefs;
        Sakura::vector<Sakura::wstring> compilerArgs;
    };
    
    struct ShaderCompileQuery
    {
        friend class HLSLShaderCompiler;
        const void* GetCompiledShaderBlob() const 
        {
            return compiledBlob->GetBufferPointer();
        }
        const auto GetCompiledShaderSize() const 
        {
            return compiledBlob->GetBufferSize();
        }
        void Reset()
        {
            compiledBlob.Release();
            shaderName.Release();
            shaderHash.Release();
        }
    protected:
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
    class HLSLShaderCompiler
    {
    public:
        bool Compile(const ShaderCompileDesc& compileDesc,
            const ShaderILBC target = ShaderILBC::SPIRV,
            ShaderCompileQuery* query = nullptr);
    protected:
        CComPtr<IDxcUtils> pUtils;
        CComPtr<IDxcCompiler3> pCompiler;
        CComPtr<IDxcIncludeHandler> pIncludeHandler;
    };

    struct SPIRVShaderTranslator
    {
        Sakura::string Translate(
            const uint32_t *ir_, size_t word_count,
            const ShadingLanguage sl = ShadingLanguage::MSL,
            const Sakura::wstring& outputPath = Sakura::wstring());
    };
}