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
 * @Date: 2020-06-16 00:19:59
 * @LastEditTime: 2020-06-18 17:59:10
 */ 
#include "../VirtualFileSystem.h"
#include <fstream>

namespace virtual_filesystem = Sakura::Engine::virtual_filesystem;
using namespace virtual_filesystem;

struct interfaces
{
    interfaces() = default;
    virtual ~interfaces() = default;
    virtual void f() = 0;
protected:
    float ff = 1;
};

struct imple : public interfaces
{
    imple(int i)
    {
        j = 1;
    }
    imple() = default;
    ~imple() = default;
    void f() override 
    {
        std::cout << "WTF" << std::endl;
    }
    int j;
};

int main(void)
{
    imple im(5);
    directory_root_local* local_root = new directory_root_local();
    virtual_filesystem::mount(local_root);

    virtual_filesystem::path path_test("SakuraVFS:Project/shaders/../shaders/SakuraTest.sproject");
    std::cout << "full: " << path_test.c_str() << std::endl;
    std::cout << "root name: " << path_test.root_name().c_str() << std::endl;
    std::cout << "root path: " << path_test.root_path().c_str() << std::endl;
    std::cout << "relative path: " << path_test.relative_path().data() << std::endl << std::endl;
    std::cout << "abs: " << virtual_filesystem::absolute(path_test) << std::endl;
    std::cout << "canonical: " << virtual_filesystem::canonical(path_test) << std::endl;
    for(auto& iter : path_test)
    {
        std::cout << iter.c_str() << std::endl;
    }   
    std::cout << std::endl;
#ifdef SAKURA_TARGET_PLATFORM_OSX
    virtual_filesystem::path path("/Users/huangzheng/Coding/SakuraEngine/../SakuraEngine/SakuraEngine/Version.h");
#elif SAKURA_TARGET_PLATFORM_WIN
    virtual_filesystem::path path("/Users/huangzheng/Coding/SakuraEngine/SakuraEngine/Version.h");
#endif
    std::cout << "full: " << path.c_str() << std::endl;
    std::cout << "root name: " << path.root_name().c_str() << std::endl;
    std::cout << "root path: " << path.root_path().c_str() << std::endl;
    std::cout << "relative path: " << path.relative_path().data() << std::endl;
    std::cout << "abs: " << virtual_filesystem::absolute(path) << std::endl;
    std::cout << "canonical: " << virtual_filesystem::canonical(path) << std::endl;
    for(auto& iter : path)
    {
        std::cout << iter.c_str() << std::endl;
    }    
    Sakura::unique_ptr<directory_entry> entry_holder;
    namespace fs = std::filesystem;
    virtual_filesystem::foreach(path,
        [&](auto&& entry)
        {
            std::cout << entry->is_regular_file() << std::endl;
            std::cout << "file size: " << virtual_filesystem::file_size(path) << std::endl;
            //virtual_filesystem::resize_file(path, 1500);//This is okay
            auto ftime = virtual_filesystem::last_write_time(path);
            std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
            std::cout << std::asctime(std::localtime(&cftime));
            entry_holder = Sakura::move(entry);
        });
    try
    {
        virtual_filesystem::path pathh("/Users/huangzheng/Coding/SakuraEngine/SKTest");
        virtual_filesystem::remove_all(pathh);
    }
    catch(std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "WTF" << std::endl;
    return 0;
}