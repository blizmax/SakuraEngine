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
 * @Date: 2020-06-13 00:37:44
 * @LastEditTime: 2020-06-13 11:10:25
 */ 
#pragma once
#include "FileMetaGenerator.h"
#include <filesystem>

namespace Sakura::Engine
{
    class MetaManager : public MetaGenerator
    {
    public:
        MetaManager(
            const Sakura::swstring& bash, const Sakura::swstring& suffix);
        
        MetaManager(const Sakura::svector<MetaPropertyRegister>& registers,
            const Sakura::swstring& bash, const Sakura::swstring& suffix);

        void Mount(const Sakura::swstring& bash);

        using FileVisitor = Sakura::function<void(const std::filesystem::path&)>;
        void VisitAllMetaFiles(FileVisitor visitor);
        
        std::filesystem::path GetMetaWithGUID(const Sakura::Guid& guid);
    protected:
        void CollectMetaUnder(const std::filesystem::path& path);
        Sakura::smap<std::filesystem::path, Sakura::smap<Sakura::Guid, std::filesystem::path>> managedMetas;
        Sakura::svector<std::filesystem::path> bashes;
    };
}