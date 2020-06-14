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
 * @Date: 2020-06-13 13:43:25
 * @LastEditTime: 2020-06-13 14:21:02
 */ 
#pragma once
#include "Shader.h"
#include <filesystem>
#include <Core/EngineUtils/log.h>
#include <StaticBuilds/Runtime/FileManagement/FileMetaManager.h>

namespace Sakura::Graphics
{   
    /**
    * @description: This is a cross-platform shader reference.
    * pivots to a HLSL-shader source file
    * and links to several generated-shaders which are platform-specified.
    */
    struct PainterShader
    {
        using MacroTable = Sakura::unordered_map<Sakura::string, Sakura::string>;
        // Find or create platform-specified shader BC or IL
        // And Initialize ShaderFunction for Pipeline Setting.
        PainterShader(Sakura::string_view backend,
            const Sakura::wstring& hlslPath,
            const Sakura::string& entryName, const ShaderStageFlags shaderStage,
            const MacroTable& PreprocessorMacros = _Shader::nullTable,
            const Sakura::wstring& generatedPath = L"");
    protected:
        const Sakura::string_view backendName;
        // Shader and shader function will be created automatically
        Shader* shader = nullptr;
        ShaderFunction function;
    };
    class SharedShaderManager : public Sakura::Engine::MetaManager
    {
    public:
        DECLARE_LOGGER("SharedShaderManager");
        SharedShaderManager(const Sakura::wstring& bash);
        /**
         * @description: Create a shader with hlsl-source directry.
         * @param {const char*} source code or binary code of shader.
         * @return: Shader pointer
         * @author: SaeruHikari
         */   
        [[nodiscard]] PainterShader* CreateShader(
            const Sakura::wstring& path, 
            const Shader::MacroTable& macroTable = _Shader::nullTable);
    };
}