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
 * @LastEditTime: 2020-06-15 00:52:59
 */ 
#include "../VirtualFileSystem.h"

namespace virtual_filesystem = Sakura::Engine::virtual_filesystem;
using namespace virtual_filesystem;

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

bool virtual_filesystem::is_directory(const path &pth) 
{
    for(auto&& root : mounted_roots)
    {
        if(root->is_directory(pth))
            return true;
    }
    return false;
}

bool virtual_filesystem::is_regular_file(const path &pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->is_directory(pth))
            return true;
    }
    return false;
}

//-----------------local filesystem(based on stl)----------------------
directory_entry_local::directory_entry_local(
    const std::filesystem::directory_entry& stl_e)
    :stl_entry(stl_e)
{
    
}
directory_entry_local::directory_entry_local
    (const std::filesystem::path& stl_path)
    :stl_entry(stl_path)
{
    
}

//-------------------modifiers of entry_local--------------------//
void directory_entry_local::replace_filename(const virtual_filesystem::path& p)
{
    return stl_entry.replace_filename(p);
}

void directory_entry_local::assign(const virtual_filesystem::path &p)
{
    return stl_entry.assign(p);
}

void directory_entry_local::refresh()
{
    return stl_entry.refresh();
}

//------------------observers of entry_local----------------------//
bool directory_entry_local::exists() const
{
    return stl_entry.exists();
}

bool directory_entry_local::is_regular_file() const
{
    return stl_entry.is_regular_file();
}

bool directory_entry_local::is_directory() const
{
    return stl_entry.is_directory();
}

path directory_entry_local::path() const
{
    return stl_entry.path();
}

bool directory_entry_local::is_symlink() const
{
    namespace fs = std::filesystem;
    return directory_entry::is_symlink() || fs::is_symlink(stl_entry.path());
}

std::uintmax_t directory_entry_local::file_size() const
{
    return stl_entry.file_size();
}

file_time_type directory_entry_local::last_write_time() const
{
    return stl_entry.last_write_time();
}


directory_entry_local* directory_root_local::new_entry_local(
    const std::filesystem::path& stl_path)
{
    return new directory_entry_local(stl_path);
}


//------------------
void directory_root_local::on_mount()
{
    // Just do nothing when mounted to local filesystem
    return;
}


path directory_root_local::absolute(const path &path) const
{
    return std::filesystem::absolute(path);
}


bool directory_root_local::is_directory(const path &pth) const
{
    return std::filesystem::is_directory(pth);
}

bool directory_root_local::is_regular_file(const path &path) const
{
    return std::filesystem::is_regular_file(path);
}



bool directory_root_local::exists(const path &path) const
{
    return std::filesystem::exists(path);
}
Sakura::string_view directory_root_local::get_mount_method() const
{
    return this->mount_method;
}

void directory_root_local::copy(
    const path &from, const path &to, copy_options options)
{
    std::filesystem::copy(from, to, options);
}

bool directory_root_local::copy_file(
    const path &from, const path &to, copy_options options)
{
    return std::filesystem::copy_file(from, to, options);
}

void directory_root_local::foreach(
    const path &path, virtual_filesystem::entry_visitor visitor)
{
    namespace fs = std::filesystem;
    if(fs::exists(path))
    {
        if(fs::is_directory(path))
        {
            Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(entry_shared);
            for (const auto& entry : fs::directory_iterator(path))
            {
                Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
                visitor(entry_shared);
            }
        }
        else if(fs::is_regular_file(path))
        {
            Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(entry_shared);
        }
    }
}

void virtual_filesystem::foreach_recursively(
    const path& path, entry_visitor visitor)
{
    for(auto&& root : mounted_roots)
    {
        root->foreach_recursively(path, visitor);
    }
}



void directory_root_local::foreach_recursively(
    const path &path, virtual_filesystem::entry_visitor visitor)
{
    namespace fs = std::filesystem;
    if(fs::exists(path))
    {
        if(fs::is_directory(path))
        {
            Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(entry_shared);
            for (const auto& entry : fs::recursive_directory_iterator(path))
            {
                Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
                visitor(entry_shared);
            }
        }
        else if(fs::is_regular_file(path))
        {
            Sakura::shared_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(entry_shared);
        }
    }
}


___local_detail::vfs_initializer::vfs_initializer()
{
    directory_root_local* local_root = new directory_root_local();
    virtual_filesystem::mount(local_root);

    virtual_filesystem::path path("/Users/huangzheng/Coding/SakuraEngine/SakuraEngine/Version.h");
    Sakura::shared_ptr<directory_entry> entry_holder;
    virtual_filesystem::foreach_recursively(path,
        [&](auto entry)
        {
            std::cout << entry->is_regular_file() << std::endl;
            entry_holder = entry;
        });
}