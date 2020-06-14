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
 * @Description: Virtual File System of Sakura Engine
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-06-14 00:28:25
 * @LastEditTime: 2020-06-14 15:52:38
 */ 
#pragma once
#include <filesystem>
#include <Core/Containers/Containers.h>

namespace Sakura::Engine
{
    // 1. Mount Virtual File on a string-name
    namespace virtual_filesystem
    {
        using path = std::filesystem::path;

        static constexpr Sakura::string_view 
            mount_method_local_filesystem = "lfs";
        static Sakura::string_view default_mount_method = mount_method_local_filesystem;
        static void set_default_mount_method(Sakura::string_view mount_method);

        struct directory_entry
        {
            virtual ~directory_entry(){};
            virtual bool exists() = 0;
        };

        struct directory_root
        {
            virtual ~directory_root(){};
            virtual bool exists(const path& path) = 0;
            virtual void on_mount() = 0;
            virtual Sakura::string_view get_mount_method() = 0;
            virtual void foreach(const path& path,
                Sakura::function<void(directory_entry*)> visitor) = 0;
            virtual void foreach_recursively(const path& path,
                Sakura::function<void(directory_entry*)> visitor) = 0;
        };


        static bool exists(const path& pth);
        static bool mount(directory_root* entry);
        static bool is_directory(const path& pth);
        static bool is_regular_file(const path& pth);
        static bool equivalent(const path& lhs, const path& rhs);


        static Sakura::vector<
            Sakura::unique_ptr<directory_root>> mounted_roots;

        static void foreach(
            const path& path, Sakura::function<void(directory_entry*)> visitor);
        static void foreach_recursively(
            const path& path, Sakura::function<void(directory_entry*)> visitor);
        
        struct directory_entry_local final : public directory_entry
        {
            virtual bool exists() override;
            std::filesystem::directory_entry stl_entry;
        };

        struct directory_root_local final : public directory_root
        {
            virtual void on_mount() override;
            virtual bool exists(const path& path) override;
            virtual Sakura::string_view get_mount_method() override;
            virtual void foreach(const path& path,
                Sakura::function<void(directory_entry*)> visitor) override;
            virtual void foreach_recursively(const path& path,
                Sakura::function<void(directory_entry*)> visitor) override;
            static constexpr Sakura::string_view mount_method = "lfs";
        };

        namespace ___local_detail
        {
            struct vfs_initializer
            {
                vfs_initializer();
            };
            static vfs_initializer __init = vfs_initializer();
        }
         
    }; 
}