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
 * @LastEditTime: 2020-06-16 02:49:38
 */ 
#include "../VirtualFileSystem.h"
#include "Core/EngineUtils/log.h"

namespace virtual_filesystem = Sakura::Engine::virtual_filesystem;
using namespace virtual_filesystem;
using path = virtual_filesystem::path;

//-------------------vfs path implementation-----------------------
path::path(const char* str_c)
    :super(str_c)
{
    if(super::is_absolute() || super::empty())
        return;
    else if(super::generic_string().starts_with("SakuraVFS:"))
        is_vfs_path = true;
    else
        Sakura::log::error("VFS path do not support relative path!");
    // TODO: automatically fix relative-path as absolute-path
}
path::path(const std::filesystem::path& p)
    :super(p)
{
    if(super::is_absolute() || super::empty())
        return;
    else if(super::generic_string().starts_with("SakuraVFS:"))
        is_vfs_path = true;
    else
        Sakura::log::error("VFS path do not support relative path!");
    // TODO: automatically fix relative-path as absolute-path
}
path path::root_name() const
{
    if(is_vfs_path)
        return *super::begin();
    else
        return super::root_name();
}

path path::root_path() const
{
    if(is_vfs_path)
        return __root_path().c_str();
    else
        return super::root_path();
}

Sakura::string_view path::relative_path() const
{
    if(is_vfs_path)
    {
        auto splitAt = __root_path().size();
        return __path().substr(splitAt, __path().size());
    }
    else
        return super::relative_path().c_str();
}

bool path::has_relative_path() const
{
    return !relative_path().empty();
}

path path::make_preferred() 
{
    if(!is_vfs_path)
        return super::make_preferred();
    return *this;
}

Sakura::string_view path::__path() const
{
    return super::c_str();
}
Sakura::string path::__root_name() const
{
    return (*super::begin()).c_str();
}
Sakura::string path::__root_path() const
{
    return __root_name().append("/");
}

//----------------virtual filesystem implementation-----------------
void virtual_filesystem::set_default_mount_method(
    Sakura::string_view mount_method)
{
    if(mount_method.empty())
        mount_method = virtual_filesystem::default_mount_method;
    default_mount_method = mount_method;
}

bool virtual_filesystem::mount(directory_root* entry)
{
    Sakura::unique_ptr<directory_root> entry_e;
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root.get() == entry)
            return false;//Already mounted, can't remount the same root.
        if(entry->get_mount_method() == mounted_root->get_mount_method())
        {
            Sakura::log::error("Can't mount two filesystem on the same root.");
            return false;//Cannot mount two filesystem on the same root.
        }
    }
    entry->on_mount();
    entry_e.reset(entry);
    mounted_roots.push_back(Sakura::move(entry_e));
    return true;
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

bool virtual_filesystem::is_directory(const path &pth) 
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->is_directory(pth);
    }
    return false;
}

bool virtual_filesystem::is_regular_file(const path &pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->is_regular_file(pth);
    }
    return false;
}

std::uintmax_t virtual_filesystem::file_size(const path& pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->file_size(pth);
    }
    return 0;
}

file_time_type virtual_filesystem::last_write_time(const path& p)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(p))
        {
            return mounted_root->last_write_time(p);
        }
    }
}



file_status virtual_filesystem::status(const path& p)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(p))
            return root->status(p);
    }
    file_status none;
    none.type = file_type::not_found;
    none.permissions = perms::none;
    return none;
}

file_status virtual_filesystem::symlink_status(const path& p)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(p))
            return root->symlink_status(p);
    }
    file_status none;
    none.type = file_type::not_found;
    none.permissions = perms::none;
    return none;
}


virtual_filesystem::path virtual_filesystem::absolute(const path& pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->absolute(pth);
    }
    return pth;
}

virtual_filesystem::path virtual_filesystem::canonical(const path& pth)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->canonical(pth);
    }
    return pth;
}


virtual_filesystem::path virtual_filesystem::proximate(
    const path& pth, const path& base)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(pth))
            return root->proximate(pth, base);
    }
    return pth;
}

bool virtual_filesystem::equivalent(const path& lhs, const path& rhs)
{
    for(auto&& root : mounted_roots)
    {
        if(root->exists(lhs) && root->exists(rhs))
            return root->equivalent(lhs, rhs);
    }
    return false;
}




void virtual_filesystem::create_symlink(
    const path& target, const path& link)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->under_root_symbol(link))
        {
            return mounted_root->create_symlink(target, link); 
        }
    }
}
void virtual_filesystem::create_directory_symlink(
    const path& target, const path& link)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->under_root_symbol(link))
        {
            return mounted_root->create_directory_symlink(target, link); 
        }
    }
}

bool virtual_filesystem::create_directory(
    const path& p, const path& existing_p)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->under_root_symbol(p))
        {
            if(existing_p.empty())
                return mounted_root->create_directory(p); 
            else
                return mounted_root->create_directory(p, existing_p);    
        }
    }
    return false;
}

bool virtual_filesystem::create_directories(const path& p)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->under_root_symbol(p))
        {
            return mounted_root->create_directories(p);
        }
    }
    return false;
}

bool virtual_filesystem::copy_file(const path& from, const path& to,
    copy_options options)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(to))
        {
            return mounted_root->copy_file(from, to);
        }
    }
    return false;
}

void virtual_filesystem::copy(const path& from, const path& to,
    copy_options options)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(to))
        {
            return mounted_root->copy(from, to);
        }
    }
}

bool virtual_filesystem::remove(const path &p)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(p))
        {
            return mounted_root->remove(p);
        }
    }
    return false;
}

std::uintmax_t virtual_filesystem::remove_all(const path &p)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(p))
        {
            return mounted_root->remove_all(p);
        }
    }
    return 0;
}

void virtual_filesystem::rename(const path& old_p, const path& new_p)
{
    if(virtual_filesystem::exists(new_p))
    {
        Sakura::string warn_info = "vfs rename: new path: ";
        warn_info.append(new_p.c_str()).append(" already exists, please notice it");
        Sakura::log::warn(warn_info.c_str());
        return;
    }
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(old_p))
        {
            return mounted_root->rename(old_p, new_p);
        }
    }
}

void virtual_filesystem::resize_file(const path& old_p, std::uintmax_t size)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(old_p))
        {
            return mounted_root->resize_file(old_p, size);
        }
    }
}

void virtual_filesystem::last_write_time(const path& p, file_time_type new_time)
{
    for(auto&& mounted_root : mounted_roots)
    {
        if(mounted_root->exists(p))
        {
            return mounted_root->last_write_time(p, new_time);
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

void virtual_filesystem::foreach(
    const path& path, entry_visitor visitor)
{
    for(auto&& root : mounted_roots)
    {
        root->foreach(path, visitor);
    }
}

Sakura::unique_ptr<directory_entry> virtual_filesystem::entry(const path& p)
{
    for(auto&& root : mounted_roots)
    {
        return root->entry(p);
    }
    return nullptr;
}


