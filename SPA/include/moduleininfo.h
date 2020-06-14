/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-14 00:31:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-14 15:56:22
 */
#pragma once
#include <EASTL/string.h>

namespace Sakura
{
    using string = eastl::string;
    using string_view = eastl::string_view;
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
        Sakura::string name; //!< The name of the dependency
        Sakura::string version; //!< The version of the dependency
    };

    /**
     * @description: Struct that contains all plugin metadata
     * @author: SaeruHikari
     */
    struct ModuleInfo
    {
        Sakura::string name; //!< name of the plugin
        Sakura::string prettyname;//!< formatted name of the plugin
        Sakura::string engine_version;//!< version of the engine
        Sakura::string version;// !< version of the plugin
        Sakura::string linking;// !< linking of the plugin
        Sakura::string license;//!< license of the plugin
        Sakura::string url; //!< url of the plugin 
        Sakura::string copyright;//!< copyright of the plugin
        Sakura::string make;//!<making method

        // Dependencies array
        eastl::vector<Dependency> dependencies;
    };
}