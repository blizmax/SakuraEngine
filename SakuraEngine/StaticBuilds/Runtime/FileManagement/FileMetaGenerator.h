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
 * @Description: Module for file increment. 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-06-11 23:32:58
 * @LastEditTime: 2020-06-13 02:51:25
 */ 
#pragma once
#include "SakuraEngine/Core/Containers/Containers.h"
#include "yaml.hpp"
#include <fstream>
#include <codecvt>

namespace Sakura::Engine
{
    // Generate YAML meta files
    class MetaGenerator
    {
    public:
        using MetaProperty =
            Sakura::pair<YAML::Node, YAML::Node>;
        using MetaProperties = 
            Sakura::sunordered_map<YAML::Node, YAML::Node>;
        using MetaPropertyRegister = 
            Sakura::function<MetaProperty(MetaGenerator&)>;
        MetaGenerator(const Sakura::swstring& suffix);
        MetaGenerator(
            const Sakura::svector<MetaPropertyRegister>& registers, const Sakura::swstring& suffix);
    public:
        void NewMetaFile(
            const Sakura::swstring& path, const Sakura::swstring& fileName);

        //using MetaVisitor = Sakura::function<void(YAML::Node&)>;
        template<typename MetaVisitor>
        void VisitMeta(
            const Sakura::swstring& path, const Sakura::swstring& fileName,
            MetaVisitor visitor)
        {
            auto projectDirection  = path;
            projectDirection = 
                projectDirection.append(L"/").append(fileName).append(file_suffix);
            std::string utf8N;
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            utf8N = conv.to_bytes(projectDirection.c_str());
            YAML::Node config = YAML::LoadFile(utf8N);
            visitor(config);
        }
        
        template<typename MetaVisitor>
        void VisitMeta(const std::filesystem::path& path,
            MetaVisitor visitor)
        {
            YAML::Node config = YAML::LoadFile(path);
            visitor(config);
        }

        template<typename Key, typename... T>
        inline YAML::Node GetMeta(
            const Key& title, T&&... args)
        {
            YAML::Node result;
            VisitMeta(std::forward<T>(args)..., 
                [&](YAML::Node& master){
                if(master[title])
                    result = master[title];
            });
            return result;
        }

        void RegistNewProperty(MetaPropertyRegister _register)
        {
            registers.push_back(_register);
        }
    protected:
        Sakura::swstring file_suffix;
        Sakura::svector<MetaPropertyRegister> registers;
    };
}