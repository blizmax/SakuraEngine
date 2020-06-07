/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-14 00:31:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-08 00:43:57
 */
#pragma once
#include <EASTL/string.h>

namespace Sakura
{
    using sstring = eastl::string;
    using sstring_view = eastl::string_view;
}

namespace Sakura::SPA
{
    /**
     * @description: Represents a dependency as specified in the 
     * plugin.json file. A list of dependencies is stored in each
     * PluginInfo Object. 
     * @author: SaeruHikari
     */
    struct Dependency
    {
        Sakura::sstring name; //!< The name of the dependency
        Sakura::sstring version; //!< The version of the dependency
    };

    /**
     * @description: Struct that contains all plugin metadata
     * @author: SaeruHikari
     */
    struct ModuleInfo
    {
        Sakura::sstring name; //!< name of the plugin
        Sakura::sstring prettyname;//!< formatted name of the plugin
        Sakura::sstring engine_version;//!< version of the engine
        Sakura::sstring version;// !< version of the plugin
        Sakura::sstring linking;// !< linking of the plugin
        Sakura::sstring license;//!< license of the plugin
        Sakura::sstring url; //!< url of the plugin 
        Sakura::sstring copyright;//!< copyright of the plugin
        Sakura::sstring make;//!<making method

        // Dependencies array
        eastl::vector<Dependency> dependencies;
    };
}