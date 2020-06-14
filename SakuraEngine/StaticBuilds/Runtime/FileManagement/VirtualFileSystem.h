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
 * @LastEditTime: 2020-06-15 00:51:47
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
        using copy_options = std::filesystem::copy_options;
        using file_time_type = std::filesystem::file_time_type;

        static constexpr Sakura::string_view 
            mount_method_local_filesystem = "lfs";
        static Sakura::string_view default_mount_method = mount_method_local_filesystem;
        static void set_default_mount_method(Sakura::string_view mount_method);

        struct directory_entry
        {
            virtual ~directory_entry(){};
            //---------------------modifiers-----------------------//
            virtual void replace_filename(const path& p) = 0;
            virtual void assign(const path& p) = 0;
            virtual void refresh() = 0;
            // --------------------observers----------------------//
            virtual bool exists() const = 0;
            virtual bool is_regular_file() const = 0;
            virtual bool is_directory() const = 0;
            virtual path path() const = 0;
            /**
             * @description: The VFS is an upper layer, and the symlink would 
            // link cross different mounted roots!
            // A Cross-Mount-Method SymLink Protocol is provided here:
            // 1. Has extension name: .ssymlink
            // 2. Has YAML content matches:
            //      1) from: URL
            //      2) to: URL
            // More protocals shold be supported in implementation-classes
            // For more information you can visit the local filesystem implementation.
             * @author: SaeruHikari
             */
            virtual bool is_symlink() const
            {
                return path().extension().compare(".ssymlink");
            }
            virtual std::uintmax_t file_size() const = 0;
            virtual file_time_type last_write_time() const = 0;
        };
        
        using entry_visitor = Sakura::function<void(Sakura::shared_ptr<directory_entry>)>;
        struct directory_root
        {
            virtual ~directory_root(){};
            virtual bool exists(const path& path) const = 0;
            virtual void on_mount() = 0;
            virtual Sakura::string_view get_mount_method() const = 0;
            virtual bool is_directory(const path& pth) const = 0;
            virtual bool is_regular_file(const path& pth) const = 0;

            virtual bool copy_file(const path& from, const path& to,
                copy_options options = copy_options::none) = 0;
            virtual void copy(const path& from, const path& to,
                copy_options options = copy_options::none) = 0;
            virtual path absolute(const path& p) const = 0;
            


            virtual void foreach(const path& path, entry_visitor visitor) = 0;
            virtual void foreach_recursively(const path& path, entry_visitor visitor) = 0;
        };
        static bool mount(directory_root* entry);
        static bool exists(const path& pth);
        static bool is_directory(const path& pth);
        static bool is_regular_file(const path& pth);
        static bool equivalent(const path& lhs, const path& rhs);
        static Sakura::vector<Sakura::unique_ptr<directory_root>> mounted_roots;
        static void foreach(const path& path, entry_visitor visitor);
        static void foreach_recursively(const path& path, entry_visitor visitor);
        



        
        struct directory_entry_local final : public directory_entry
        {
            friend struct directory_root_local;
            //---------------------modifiers---------------------//
            virtual void replace_filename(const virtual_filesystem::path& p) override;
            virtual void assign(const virtual_filesystem::path& p) override;
            virtual void refresh() override;
            
            //---------------------observers---------------------//
            virtual bool exists() const override;
            virtual bool is_regular_file() const override;
            virtual bool is_directory() const override;
            virtual virtual_filesystem::path path() const override;
            virtual bool is_symlink() const override;
            virtual std::uintmax_t file_size() const override;
            virtual file_time_type last_write_time() const override;



            ~directory_entry_local() = default;
        protected:
            directory_entry_local(const std::filesystem::directory_entry& stl_e);
            directory_entry_local(const std::filesystem::path& stl_path);
            std::filesystem::directory_entry stl_entry;
        };


        struct directory_root_local final : public directory_root
        {
            virtual void on_mount() override;
            virtual bool exists(const path& path) const override;
            virtual Sakura::string_view get_mount_method() const override;

            virtual path absolute(const path& path) const override;

            virtual bool copy_file(const path& from, const path& to,
                copy_options options = copy_options::none) override;
            virtual void copy(const path& from, const path& to,
                copy_options options = copy_options::none) override;

                
            virtual void foreach(const path& path, entry_visitor visitor) override;
            virtual void foreach_recursively(const path& path, entry_visitor visitor) override;


            virtual bool is_directory(const path& path) const override;
            virtual bool is_regular_file(const path& path) const override;
            static constexpr Sakura::string_view mount_method = "lfs";

            // Pool Allocate for better performance
            static directory_entry_local* new_entry_local(
                const std::filesystem::path& stl_e);
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