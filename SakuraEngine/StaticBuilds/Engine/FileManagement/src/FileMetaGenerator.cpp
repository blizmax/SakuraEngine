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
 * @Date: 2020-06-11 23:39:56
 * @LastEditTime: 2020-06-13 02:36:12
 */ 
#include "../FileMetaGenerator.h"
#include <filesystem>
#include <sstream>
#include "SakuraEngine/Core/CoreMinimal/SGUID.h"

using namespace Sakura::Engine;
//namespace fs = std::filesystem;
//auto ftime = fs::last_write_time(src);
//std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

using namespace Sakura::Engine;

MetaGenerator::MetaGenerator(const Sakura::swstring& suffix)
    :file_suffix(suffix)
{
    registers.push_back(
        [](MetaGenerator& manager)->MetaGenerator::MetaProperty
    {
        YAML::Node title("EngineVersion");
        YAML::Node data(ENGINE_VERSION);
        return {title, data};
    });
    registers.push_back(
        [](MetaGenerator& manager)->MetaGenerator::MetaProperty
    {
        YAML::Node title("GUID");
        Sakura::Guid guid = Sakura::newGuid();
        std::stringstream ss;
        ss << guid;
        YAML::Node data(ss.str());
        return {title, data};
    });
}

MetaGenerator::MetaGenerator(
    const Sakura::svector<MetaPropertyRegister>& _registers,
    const Sakura::swstring& file_suf)
    :registers(_registers)
{
    MetaGenerator(file_suf.c_str());
}

void MetaGenerator::NewMetaFile(
    const Sakura::swstring& path, const Sakura::swstring& fileName)
{
    auto projectDirection  = path;
    projectDirection = 
        projectDirection.append(L"/").append(fileName).append(file_suffix);
    std::filesystem::path _path = projectDirection.c_str();
    if(std::filesystem::exists(_path))
        return;
    std::ofstream fout(_path);
    YAML::Node config = YAML::LoadFile(_path);
    for(auto& functor : registers)
    {
        auto&& pair = functor(*this);
        config[pair.first] = pair.second;
    }
    fout << config;
}

