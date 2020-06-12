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
 * @LastEditTime: 2020-06-12 17:58:56
 */ 
#pragma once
#include "SakuraEngine/Core/Containers/Containers.h"
#include "yaml.hpp"
#include <fstream>

namespace Sakura::Engine
{
    //timestamp : 24123
    //hash : 1232142321
    struct FileMetaGenerator
    {
        using MetaPair = eastl::pair<Sakura::sstring, Sakura::sstring>;
        using MetaMap = Sakura::smap<Sakura::sstring, Sakura::sstring>;
        using Functor = eastl::function<MetaPair(FileMetaGenerator&, const Sakura::swstring&)>;
        void AddMeta(Functor functor)
        {
            functors.push_back(functor);
        }
        FileMetaGenerator();
        FileMetaGenerator(Sakura::svector<Functor> _functors)
            :functors(_functors)
        {
            FileMetaGenerator();
        }
        void GenMeta(const Sakura::swstring& path)
        {
            for(auto& functor : functors)
            {
                AddInformation(path,
                    functor(*this, path).first, functor(*this, path).second);
            }
        }
        Sakura::sstring GetMeta(
            const Sakura::swstring& path, const Sakura::sstring& title)
        {
            return GetInformation(path, title);
        }
        bool HasMeta(
            const Sakura::swstring& path, const Sakura::sstring& title)
        {
            int line = -1;
            GetInformation(path, title, &line);
            return line != -1;
        }
        MetaMap GetAllMeta(const Sakura::swstring& path);
    protected:
        static void AddInformation(
            const Sakura::swstring& path,
            const Sakura::sstring& title, const Sakura::sstring& data);

        static Sakura::sstring GetInformation(
            const Sakura::swstring& path,
            const Sakura::sstring& title, int* line = nullptr);
        Sakura::svector<Functor> functors;
    };
}