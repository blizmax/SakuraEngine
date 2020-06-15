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
 * @Date: 2020-06-15 14:35:47
 * @LastEditTime: 2020-06-16 02:46:50
 */ 
#include "../VirtualFileSystem.h"

namespace virtual_filesystem = Sakura::Engine::virtual_filesystem;
using namespace virtual_filesystem;
using path = virtual_filesystem::path;

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
inline virtual_filesystem::file_type Transfer(std::filesystem::file_type type)
{
    namespace fs = std::filesystem;
    namespace vfs = virtual_filesystem;
    switch(type)
    {
        case fs::file_type::none:
            return vfs::file_type::none;
        case fs::file_type::directory:
            return vfs::file_type::directory;
        case fs::file_type::symlink:
            return vfs::file_type::symlink;
        case fs::file_type::regular:
            return vfs::file_type::regular;
        case fs::file_type::not_found:
            return vfs::file_type::not_found;
        default:
            return vfs::file_type::unknown;
    }
}

file_status directory_entry_local::status() const
{
    namespace fs = std::filesystem;
    file_status engine_status = this->directory_entry::status();
    auto os_status = stl_entry.status();
    engine_status.type = Transfer(os_status.type());
    fs::perms readable
        = fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read;
    fs::perms wirtable
        = fs::perms::owner_write | fs::perms::group_write | fs::perms::others_write;
    fs::perms exec
        = fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec;
    if((os_status.permissions() & wirtable) == fs::perms::none)
        engine_status.permissions = engine_status.permissions ^ perms::write;
    if((os_status.permissions() & readable) == fs::perms::none)
        engine_status.permissions = engine_status.permissions ^ perms::read;
    if((os_status.permissions() & exec) == fs::perms::none)
        engine_status.permissions = engine_status.permissions ^ perms::exec;
    return engine_status;
}

file_status directory_entry_local::symlink_status() const
{
    auto engine_status = this->directory_entry::symlink_status();
    return engine_status;
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


//------------------root_local----------------------//
void directory_root_local::on_mount()
{
    // Just do nothing when mounted to local filesystem
    return;
}
Sakura::string_view directory_root_local::get_mount_method() const
{
    return this->mount_method;
}


path directory_root_local::absolute(const path &path) const
{
    return std::filesystem::absolute(path);
}

path directory_root_local::canonical(const path &path) const
{
    return std::filesystem::canonical(path);
}

path directory_root_local::proximate(
    const path &path, const virtual_filesystem::path& base) const
{
    if(base.empty())
        return std::filesystem::proximate(path);
    return std::filesystem::proximate(path, base);
}

bool directory_root_local::equivalent(const path &lhs, const path &rhs) const
{
    return std::filesystem::equivalent(lhs, rhs);
}

bool directory_root_local::is_directory(const path &pth) const
{
    return std::filesystem::is_directory(pth);
}

bool directory_root_local::is_regular_file(const path &path) const
{
    return std::filesystem::is_regular_file(path);
}

std::uintmax_t directory_root_local::file_size(const path& pth) const
{
    return std::filesystem::file_size(pth);    
}

file_status directory_root_local::status(const path &p) const
{
    return this->entry(p)->status();
}

file_status directory_root_local::symlink_status(const path &p) const
{
    return this->entry(p)->symlink_status();
}

file_time_type directory_root_local::last_write_time(const path& p) const
{
    return std::filesystem::last_write_time(p);
}

bool directory_root_local::exists(const path &path) const
{
    return std::filesystem::exists(path);
}






bool directory_root_local::create_directory(const path& p, const path& existing_p) 
{
    if(existing_p.empty())
        return std::filesystem::create_directory(p);
    return std::filesystem::create_directory(p, existing_p);
}

bool directory_root_local::create_directories(const path& p)
{
    return std::filesystem::create_directories(p);
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
bool directory_root_local::remove(const path& p)
{
    return std::filesystem::remove(p);
}

std::uintmax_t directory_root_local::remove_all(const path& p)
{
    return std::filesystem::remove_all(p);
}

void directory_root_local::rename(const path& old_p, const path& new_p)
{
    return std::filesystem::rename(old_p, new_p);
}

void directory_root_local::resize_file(const path& old_p, std::uintmax_t size)
{
    return std::filesystem::resize_file(old_p, size);
}

void directory_root_local::last_write_time(const path& p, file_time_type new_time)
{
    return std::filesystem::last_write_time(p, new_time);
}

void directory_root_local::foreach(
    const path &path, virtual_filesystem::entry_visitor visitor)
{
    namespace fs = std::filesystem;
    if(fs::exists(path))
    {
        if(fs::is_directory(path))
        {
            Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(Sakura::move(entry_shared));
            for (const auto& entry : fs::directory_iterator(path))
            {
                Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
                visitor(Sakura::move(entry_shared));
            }
        }
        else if(fs::is_regular_file(path))
        {
            Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(Sakura::move(entry_shared));
        }
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
            Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(Sakura::move(entry_shared));
            for (const auto& entry : fs::recursive_directory_iterator(path))
            {
                Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
                visitor(Sakura::move(entry_shared));
            }
        }
        else if(fs::is_regular_file(path))
        {
            Sakura::unique_ptr<directory_entry> entry_shared(
                    new_entry_local(path));
            visitor(Sakura::move(entry_shared));
        }
    }
}

Sakura::unique_ptr<directory_entry> directory_root_local::entry(const path& p) const
{
    Sakura::unique_ptr<directory_entry> entry_unique(new_entry_local(p));
    return Sakura::move(entry_unique);
}
