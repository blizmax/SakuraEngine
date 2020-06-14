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
 * @Date: 2020-06-13 13:45:59
 * @LastEditTime: 2020-06-13 14:20:55
 */ 
#include "SharedShaderManager.h"

using namespace Sakura::Graphics;

PainterShader::PainterShader(Sakura::string_view backend,
    const Sakura::wstring& hlslPath,
    const Sakura::string& entryName, const ShaderStageFlags shaderStage,
    const PainterShader::MacroTable& PreprocessorMacros,
    const Sakura::wstring& generatedPath)
{
    // find generated File in meta file
    
}

SharedShaderManager::SharedShaderManager(const Sakura::wstring& bash)
    :Sakura::Engine::MetaManager(bash, L".shader.meta")
{
    std::filesystem::path bash_path(bash.c_str());
    if(!std::filesystem::exists(bash_path))
    {
        Sakura::string error_info = "Construct error: path ";
        error_info.append(bash_path.c_str()).append(" does not exist!");
        SharedShaderManager::error(error_info.c_str());
        assert(0);
    }
}
