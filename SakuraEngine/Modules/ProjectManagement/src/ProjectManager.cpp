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
 * @Date: 2020-06-12 17:52:28
 * @LastEditTime: 2020-06-12 18:43:02
 */ 
#include "../ProjectManager.hpp"
#include <fstream>
#include <codecvt>

using namespace Sakura::Engine;

void ProjectManager::NewProjectEntry(
    const Sakura::swstring& path, const Sakura::swstring& projectName)
{
    auto projectDirection  = path;
    projectDirection = 
        projectDirection.append(L"/").append(projectName).append(L".sproject");
    std::string utf8N;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    utf8N = conv.to_bytes(projectDirection.c_str());
    std::ofstream fout(projectDirection.c_str());
    YAML::Node config = YAML::LoadFile(utf8N);
    config["EngineVersion"] = ENGINE_VERSION;
    fout << config;
}