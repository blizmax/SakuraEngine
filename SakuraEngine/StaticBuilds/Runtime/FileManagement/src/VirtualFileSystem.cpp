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
 * @Date: 2020-06-14 00:57:52
 * @LastEditTime: 2020-06-14 11:22:57
 */ 
#include "../VirtualFileSystem.h"

namespace virtual_filesystem = Sakura::Engine::virtual_filesystem;
using namespace virtual_filesystem;

//------------------path------------------------








//------------------virtual filesystem interface-------------------
static void virtual_filesystem::set_default_mount_method(
    Sakura::string_view mount_method)
{
    default_mount_method = mount_method;
}

bool virtual_filesystem::exists(const path& pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return true;
    }
    return false;
}

bool virtual_filesystem::mount(directory_root* entry)
{
    Sakura::unique_ptr<directory_root> entry_e;
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root.get() == entry)
            return false;//Already mounted, can't remount the same root.
    }
    entry->on_mount();
    entry_e.reset(entry);
    mounted_roots.push_back(Sakura::move(entry_e));
    return true;
}


//-----------------local filesystem(based on stl)----------------------
bool directory_entry_local::exists()
{
    return stl_entry.exists();
}
void directory_root_local::on_mount()
{
    // Just do nothing when mounted to local filesystem
    std::cout << "on mount!" << std::endl;
    return;
}

bool directory_root_local::exists(const path &path)
{
    return std::filesystem::exists(path);
}

Sakura::string_view directory_root_local::get_mount_method()
{
    return this->mount_method;
}

void directory_root_local::foreach(
    const path &path, Sakura::function<void (directory_entry *)> visitor)
{
    namespace fs = std::filesystem;
    if(fs::exists(path))
    {
        if(fs::is_directory(path))
        {
            for (const auto& entry : fs::directory_iterator(path))
            {

            }
        }
        else if(fs::is_regular_file(path))
        {
            
        }
    }
}

void directory_root_local::foreach_recursively(
    const path &path, Sakura::function<void (directory_entry *)> visitor)
{
    assert(0);
}


___local_detail::vfs_initializer::vfs_initializer()
{
    directory_root_local* local_root = new directory_root_local();
    virtual_filesystem::mount(local_root);
}