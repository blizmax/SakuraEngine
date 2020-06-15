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
 * @LastEditTime: 2020-06-16 00:26:44
 */ 
#pragma once
#include <filesystem>
#include <Core/Containers/Containers.h>

namespace Sakura::Engine
{
    // 1. Mount Virtual File on a string-name
    namespace virtual_filesystem
    {
        //using path = std::filesystem::path;
        struct path : public std::filesystem::path 
        {
            using super = std::filesystem::path;
            path() = default;
            path(const char* str_c);
            path(const std::filesystem::path& p);
            inline bool is_sakura_vfs_absolute_path()
            {
                return is_vfs_path;
            }
            ~path() = default;
            // 1.Windows: C:/
            // 2.Unix: /...
            // 3.Our VFS: SakuraVFS:${mounted_method}/
            // For example: SakuraVFS:Project/ 
            path root_path();
            path root_name();
            Sakura::string_view relative_path();
            bool has_relative_path();
            path make_preferred();
            
        private:
            // Hide this: VFS only support absolute path.
            Sakura::string __root_name();
            Sakura::string __root_path();
            Sakura::string_view __path();
            bool has_root_path()
            {
                return true;
            }
            bool has_root_name()
            {
                return !root_name().empty();
            }
            bool is_absolute()
            {
                return true;
            }
            bool is_relative()
            {
                return false;
            }
            path lexically_normal()
            {
                return *this;
            }
            path lexically_relative(const path& base)
            {
                return *this;
            }
            path lexically_proximate(const path& base)
            {
                return *this;
            }
            bool is_vfs_path = false;
        };
        using copy_options = std::filesystem::copy_options;
        using file_time_type = std::filesystem::file_time_type;
        enum class file_type 
        {
            none  /* unspecified */,
            not_found /* unspecified */,
            regular  /* unspecified */,
            directory  /* unspecified */,
            symlink  /* unspecified */,
            //block = /* unspecified */,
            //character = /* unspecified */,
            //fifo = /* unspecified */,
            //socket = /* unspecified */,
            unknown  /* unspecified */,
            /* implementation-defined */
        };
        enum class perms : unsigned
        {
            none,
            read,
            write,
            exec,
            all
        };
        inline constexpr perms operator&(perms _LHS, perms _RHS) {
        return static_cast<perms>(static_cast<unsigned>(_LHS) &
                                    static_cast<unsigned>(_RHS));
        }

        inline constexpr perms operator|(perms _LHS, perms _RHS) {
        return static_cast<perms>(static_cast<unsigned>(_LHS) |
                                    static_cast<unsigned>(_RHS));
        }

        inline constexpr perms operator^(perms _LHS, perms _RHS) {
        return static_cast<perms>(static_cast<unsigned>(_LHS) ^
                                    static_cast<unsigned>(_RHS));
        }
        struct file_status
        {
            perms permissions = perms::all;
            file_type type = file_type::none;
        };

        inline constexpr Sakura::string_view 
            mount_method_local_filesystem = "lfs";
        inline Sakura::string_view default_mount_method = mount_method_local_filesystem;
        void set_default_mount_method(Sakura::string_view mount_method);

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
            virtual file_status status() const
            {
                // Mention that file_type is always none.
                // Please validate in at implementation-classes.
                return file_status();
            }
            virtual file_status symlink_status() const
            {
                assert(0 && "Wait for implementation of VFS SymLink Protocol!");
            }
            /**
             * @description: The VFS is an upper layer, and the symlink would 
            // link cross different mounted roots!
            // A Cross-Mount-Method SymLink Protocol is provided here:
            // 1. Has extension name: .ssymlink
            // 2. Has YAML content matches:
            //      1) link-to: ${URL}
             * @author: SaeruHikari
             */
            virtual bool is_symlink() const
            {
                return path().extension() == virtual_filesystem::path(".ssymlink");
            }
            virtual std::uintmax_t file_size() const = 0;
            virtual file_time_type last_write_time() const = 0;
        };
        
        using entry_visitor = Sakura::function<void(Sakura::unique_ptr<directory_entry>&&)>;
        struct directory_root
        {
            virtual ~directory_root(){};
            virtual bool exists(const path& path) const = 0;
            virtual void on_mount() = 0;
            virtual Sakura::string_view get_mount_method() const = 0;
            virtual bool is_directory(const path& pth) const = 0;
            virtual bool is_regular_file(const path& pth) const = 0;
            virtual path current_path() const = 0;
            virtual file_status status(const path& p) const = 0;
            virtual file_status symlink_status(const path& p) const = 0;

            // path operations
            virtual path absolute(const path& p) const = 0;
            virtual path canonical(const path& p) const = 0;
            virtual path weakly_canonical(const path& p) const = 0;
            virtual path relative(
                const path& p, const path& base = path()) const = 0;
            virtual path proximate(
                const path& p, const path& base = path()) const = 0;
            virtual bool equivalent(const path& lhs, const path& rhs) const = 0;
    
            // file operations
            virtual bool create_directory(
                const path& p, const path& existing_p = path()) = 0;
            virtual void create_symlink(const path& target, const path& link)
            {
                assert(0 && "Wait for implementation of VFS SymLink Protocol!");
            }
            virtual void create_directory_symlink(const path& target, const path& link) 
            {
                assert(0 && "Wait for implementation of VFS SymLink Protocol!");
            }
            virtual bool create_directories(const path& p) = 0;
            virtual bool copy_file(const path& from, const path& to,
                copy_options options = copy_options::none) = 0;
            virtual void copy(const path& from, const path& to,
                copy_options options = copy_options::none) = 0;
            virtual bool remove(const path& p) = 0;
            virtual std::uintmax_t remove_all(const path& p) = 0;
            virtual void rename(const path& old_p, const path& new_p) = 0;

            virtual bool is_root(const path& root_path) const = 0;

            // entry operations
            virtual void foreach(const path& path, entry_visitor visitor) = 0;
            virtual void foreach_recursively(const path& path, entry_visitor visitor) = 0;
            virtual Sakura::unique_ptr<directory_entry> entry(const path& p) const = 0;
        };
        // Observers
        bool mount(directory_root* entry);
        bool exists(const path& pth);
        bool is_directory(const path& pth);
        bool is_regular_file(const path& pth);
        path current_path(
            Sakura::string_view mount_method = Sakura::string_view());
        file_status status(const path& p);
        file_status symlink_status(const path& p);


        path absolute(const path& pth);
        path canonical(const path& pth);
        path weakly_canonical(const path& pth);
        path relative(const path& pth, const path& base = path());
        path proximate(const path& pth, const path& base = path());
        bool equivalent(const path& lhs, const path& rhs);


        bool create_directory(
            const path& p, Sakura::string_view mount_method = Sakura::string_view(),
            const path& existing_p = path());
        bool create_directories(
            const path& p, Sakura::string_view mount_method = Sakura::string_view());
        bool copy_file(const path& from, const path& to,
            copy_options options = copy_options::none);
        void copy(const path& from, const path& to,
            copy_options options = copy_options::none);
        bool remove(const path& p);
        std::uintmax_t remove_all(const path& p);
        void rename(const path& old_p, const path& new_p);

        void resize_file(const path& old_p, std::uintmax_t size);
        
        void foreach(const path& path, entry_visitor visitor);
        void foreach_recursively(const path& path, entry_visitor visitor);
        
        inline Sakura::unique_ptr<directory_entry> entry(const path& p);
        inline Sakura::vector<Sakura::unique_ptr<directory_root>> mounted_roots;
        
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
            virtual std::uintmax_t file_size() const override;
            virtual file_time_type last_write_time() const override;
            virtual file_status status() const override;
            virtual file_status symlink_status() const override;


            ~directory_entry_local() = default;
        protected:
            directory_entry_local(const std::filesystem::directory_entry& stl_e);
            directory_entry_local(const std::filesystem::path& stl_path);
            std::filesystem::directory_entry stl_entry;
        };

        struct directory_root_local final : public directory_root
        {
            virtual void on_mount() override;
            virtual Sakura::string_view get_mount_method() const override;


            virtual bool exists(const path& path) const override;
            virtual bool is_directory(const path& path) const override;
            virtual bool is_regular_file(const path& path) const override;
            virtual bool is_root(const path& root_path) const override;
            virtual path current_path() const override;
            virtual file_status status(const path& p) const override;
            virtual file_status symlink_status(const path& p) const override;


            virtual path absolute(const path& path) const override;
            virtual path canonical(const path& p) const override;
            virtual path weakly_canonical(const path& p) const override;
            virtual path relative(const path& path,
                const virtual_filesystem::path& base = virtual_filesystem::path()) const override;
            virtual path proximate(const path& path,
                const virtual_filesystem::path& base = virtual_filesystem::path()) const override;
            virtual bool equivalent(const path& lhs, const path& rhs) const override;

            
            virtual bool create_directory(
                const path& p, const path& existing_p = path()) override;
            virtual bool create_directories(const path& p) override;
            virtual bool copy_file(const path& from, const path& to,
                copy_options options = copy_options::none) override;
            virtual void copy(const path& from, const path& to,
                copy_options options = copy_options::none) override;
            virtual bool remove(const path& p) override;
            virtual std::uintmax_t remove_all(const path& p) override;
            virtual void rename(const path& old_p, const path& new_p) override;

                
            virtual void foreach(const path& path, entry_visitor visitor) override;
            virtual void foreach_recursively(const path& path, entry_visitor visitor) override;
            virtual Sakura::unique_ptr<directory_entry> entry(const path& p) const override;


            inline static constexpr Sakura::string_view mount_method = "lfs";

            // Pool Allocate for better performance
            static directory_entry_local* new_entry_local(
                const std::filesystem::path& stl_e);
        };
    }; 
}