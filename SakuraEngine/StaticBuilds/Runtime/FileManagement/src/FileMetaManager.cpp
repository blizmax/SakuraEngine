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
 * @Date: 2020-06-13 00:44:24
 * @LastEditTime: 2020-06-14 11:14:08
 */ 
#include "../FileMetaManager.h"
#include "Core/EngineUtils/log.h"

using namespace Sakura::Engine;

MetaManager::MetaManager(
    const Sakura::wstring& _bash, const eastl::wstring& suffix)
    :MetaGenerator(suffix), bashes({_bash.c_str()})
{
    std::filesystem::path newBash = _bash.c_str();
    CollectMetaUnder(newBash);
}

MetaManager::MetaManager(const Sakura::vector<MetaPropertyRegister>& registers,
    const Sakura::wstring& _bash, const Sakura::wstring& suffix)
    :MetaGenerator(registers, suffix), bashes({_bash.c_str()})
{
    std::filesystem::path newBash = _bash.c_str();
    CollectMetaUnder(newBash);
}

void MetaManager::CollectMetaUnder(const std::filesystem::path &path)
{
    namespace fs = std::filesystem;
    std::filesystem::path suffix_path = file_suffix.c_str();
    if (fs::exists(path) && fs::is_directory(path))
    {
        for (const auto& entry : fs::recursive_directory_iterator(path))
        {
            auto filename = entry.path().filename();
            if (fs::is_directory(entry.status()))
                ;// This is a folder, thus we do nothing here.
            else if (fs::is_regular_file(entry.path()) && entry.path().has_extension())
            {
                // Collect all managed files
                if(entry.path().extension() == suffix_path)
                {
                    auto result = GetMeta("GUID", entry.path());
                    if(result.IsNull())
                    {
                        std::string res = "Meta File Parse Error: GUID is NULL! Please Check: ";
                        Sakura::log::error(res.append(entry.path().c_str()));
                        continue;
                    }
                    else
                    {
                        Sakura::Guid guid = Sakura::Guid(result.as<std::string>());
                        // Add meta to the indexed map.
                        managedMetas[entry.path()][guid] = entry.path();
                    }
                }
            }
        }
    }
}

void MetaManager::VisitAllMetaFiles(FileVisitor visitor)
{
    for(auto& iter : managedMetas)
    {
        for(auto&& iteriter : iter.second)
        {
            visitor(iteriter.second);
        }
    }
}

std::filesystem::path MetaManager::GetMetaWithGUID(const Sakura::Guid &guid)
{
    std::filesystem::path result;
    for(auto& iter : managedMetas)
    {
        if(iter.second.find(guid) != iter.second.end())
        {
            result = iter.second[guid];
        }
    }
    return result;
}

void MetaManager::Mount(const Sakura::wstring &bash)
{
    std::filesystem::path newBash = bash.c_str();
    for(auto i = 0u; i < bashes.size(); i++)
    {
        auto&& path = bashes[i];
        Sakura::string_view ab_path = std::filesystem::absolute(path).c_str();
        Sakura::string_view ab_new = std::filesystem::absolute(path).c_str();
        // if newBash is included in a mounted bash, then return directly
        if(ab_new.starts_with(ab_path))
            return;
        // if a mounted bash is included in newBash, then replace it
        if(ab_path.starts_with(ab_new))
        {
            bashes[i] = newBash;
        }
    }
    bashes.push_back(newBash);
    // Iterate around newBash Path and recollect meta-paths
    CollectMetaUnder(newBash);
}