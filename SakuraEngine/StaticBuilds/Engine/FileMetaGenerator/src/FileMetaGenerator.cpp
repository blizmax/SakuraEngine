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
 * @LastEditTime: 2020-06-12 00:48:54
 */ 
#include "../FileMetaGenerator.h"
#include <codecvt>
#include <filesystem>

using namespace Sakura::Engine;
//namespace fs = std::filesystem;
//auto ftime = fs::last_write_time(src);
//std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

void FileMetaGenerator::AddInformation(
    const Sakura::sstring& path,
    const Sakura::sstring& title, const Sakura::sstring& data)
{
    int l = -1;
    GetInformation(path, title, &l);
    std::fstream outf(path.c_str(), std::ios::binary);
    if(l == -1) // Add new line
    {
        outf << title.c_str() << " : " << data.c_str() << std::endl;
    }
    else // edit old line
    {
        
    }
}

Sakura::sstring FileMetaGenerator::GetInformation(
    const Sakura::sstring& path, const Sakura::sstring& title,
    int* _line)
{
    Sakura::sstring res;
    if(_line != nullptr)
        *_line = -1;
    std::fstream outf(path.c_str(), std::ios::binary);
    std::string line;
    int l = 0;
    while(std::getline(outf, line))
    {
        auto cut = line.find(":");
        if(cut > 0 && line.substr(1, cut - 1) == title.c_str())
        {
            res = line.substr(cut + 1, line.size()).c_str();
            if(_line != nullptr)
                *_line = l;
        }
        l++;
    }
    return res;
}
