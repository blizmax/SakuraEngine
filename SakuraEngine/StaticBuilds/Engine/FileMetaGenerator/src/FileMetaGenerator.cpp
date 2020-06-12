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
 * @LastEditTime: 2020-06-12 14:31:42
 */ 
#include "../FileMetaGenerator.h"
#include <codecvt>
#include <filesystem>
#include <sstream>

using namespace Sakura::Engine;
//namespace fs = std::filesystem;
//auto ftime = fs::last_write_time(src);
//std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
#include <iostream>
void FileMetaGenerator::AddInformation(
    const Sakura::swstring& path,
    const Sakura::sstring& title, const Sakura::sstring& data)
{
    int l = -1;
    auto _d = GetInformation(path, title, &l);
    if(_d == data)
        return;
    if(l == -1) // Add new line
    {
        std::ofstream outf(path.c_str(), ios::app);
        outf << title.c_str() << ":" << data.c_str() << "\n";
        outf.close();
    }
    else // edit old line
    {
        std::ifstream inf(path.c_str());
        std::string line;
        std::string strFileData;
        int i = 0;
        while(std::getline(inf, line))
        {
            if (i == l)
            {
                strFileData.append(title.c_str()).append(":").append(data.c_str());
                strFileData += "\n";
            }
            else
            {
                strFileData += line;
                strFileData += "\n";
            }
            i++;
        }
        inf.close();
        ofstream out(path.c_str());
        out.flush();
        out << strFileData;
        out.close();
    }
}

Sakura::sstring FileMetaGenerator::GetInformation(
    const Sakura::swstring& path, const Sakura::sstring& title,
    int* _line)
{
    Sakura::sstring res;
    if(_line != nullptr)
        *_line = -1;
    std::fstream outf(path.c_str(), fstream::in);
    std::string line;
    int l = 0;
    while(std::getline(outf, line))
    {
        if(!line.empty())
        {
            auto cut = line.find(":");
            if(cut > 0)
            {
                if(line.substr(0, cut) == title.c_str())
                {
                    res = line.substr(cut + 1, line.size()).c_str();
                    if(_line != nullptr)
                        *_line = l;
                }
            }
        }
        l++;
    }
    outf.close();
    return res;
}

FileMetaGenerator::MetaMap FileMetaGenerator::GetAllMeta(
    const Sakura::swstring &path)
{
    FileMetaGenerator::MetaMap res;
    std::fstream outf(path.c_str(), fstream::in);
    std::string line;
    while(std::getline(outf, line))
    {
        if(!line.empty())
        {
            auto cut = line.find(":");
            if(cut > 0)
            {
                res[line.substr(0, cut).c_str()] =
                     line.substr(cut + 1, line.size()).c_str();
            }
        }
    }
    outf.close();
    return res;
}

FileMetaGenerator::FileMetaGenerator()
{
    namespace fs = std::filesystem;
    functors.push_back(
        [](const Sakura::swstring& path) -> Sakura::Engine::FileMetaGenerator::MetaPair
    {
        std::time_t t = 
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss << t;
        return {"timestamp", ss.str().c_str()};
    });
}