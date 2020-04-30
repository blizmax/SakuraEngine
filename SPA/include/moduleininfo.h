/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-14 00:31:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-04-30 17:13:43
 */
#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <EASTL/string.h>

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
        eastl::string name; //!< The name of the dependency
        eastl::string version; //!< The version of the dependency
    };

    /**
     * @description: Struct that contains all plugin metadata
     * @author: SaeruHikari
     */
    struct ModuleInfo
    {
        eastl::string name; //!< name of the plugin
        eastl::string prettyname;//!< formatted name of the plugin
        eastl::string engine_version;//!< version of the engine
        eastl::string version;// !< version of the plugin
        eastl::string linking;// !< linking of the plugin
        eastl::string license;//!< license of the plugin
        eastl::string url; //!< url of the plugin 
        eastl::string copyright;//!< copyright of the plugin
        eastl::string make;//!<making method

        // Dependencies array
        eastl::vector<Dependency> dependencies;
    };
}