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
 * @Date: 2020-02-25 22:25:45
 * @LastEditTime: 2020-04-30 17:24:08
 */
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include "../../Extern/include/version/version.h"
#include "../../DependencyGraph/Graph.h"
#include <functional>
#include <memory>
#include <stdint.h>
#include <iostream>
#include <string>
#include <string_view>
#include "moduleininfo.h"
#include "imodule.h"
#include <unordered_map>
#include <EASTL/map.h>
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#define DLLEXPORT EMSCRIPTEN_KEEPALIVE
#define SPA_API EMSCRIPTEN_KEEPALIVE
#define DLLLOCAL __attribute__((visibility("hidden")))
#define __stdcall 
#elif defined(__GNUC__)
#define SPA_API __attribute__((visibility("default")))
#define DLLEXPORT __attribute__((visibility("default")))
#define DLLLOCAL __attribute__((visibility("hidden")))
#define __stdcall 
#else
#define DLLEXPORT __declspec(dllexport)
#ifdef API_EXPORTS
#define SPA_API __declspec(dllexport)
#else
#define SPA_API __declspec(dllimport)
#endif
#endif
  
namespace Sakura::SPA
{
    class ModuleManager;
}

extern "C" SPA_API Sakura::SPA::ModuleManager* __stdcall GetModuleManager();

namespace Sakura::SPA
{
    using namespace boost;
    struct ModuleProp_t
    {
        using kind = vertex_property_tag; 
    };
    struct ModuleProperty
    {
        bool bActive = false;
        eastl::string name;
    };
    using registerer = std::function<std::unique_ptr<IModule>(void)>;
    using ModuleProp = property<ModuleProp_t, ModuleProperty>;
    using ModuleGraph = DAG::Graph<ModuleProp>;
    using ModuleNode = DAG::GraphVertex<ModuleProp>;
 
    class ModuleManager
    {
        friend struct IModule;
    public:
        ModuleManager() = default;
        virtual IModule* GetModule(const eastl::string& name);
    
        virtual const ModuleGraph& MakeModuleGraph(const eastl::string& entry, 
            bool shared = false);
        virtual bool InitModuleGraph(void);
        virtual bool DestroyModuleGraph(void);
    public:
        virtual void Mount(const eastl::string& rootdir);
        virtual eastl::string_view GetRoot(void);
        virtual void RegisterStaticallyLinkedModule(
            const char* moduleName, registerer _register);
        virtual IModule* SpawnStaticModule(const eastl::string& moduleName);
        virtual IModule* SpawnDynamicModule(const eastl::string& moduleName);
        virtual ModuleProperty GetModuleProp(const eastl::string& name);
        virtual void SetModuleProp(const eastl::string& name, const ModuleProperty& prop);
    private:
        bool __internal_DestroyModuleGraph(const eastl::string& nodename);
        void __internal_MakeModuleGraph(const eastl::string& entry,
            bool shared = false);
        bool __internal_InitModuleGraph(const eastl::string& nodename);
        Version CoreVersion{"0.1.0"};
        ModuleInfo ParseMetaData(const char* metadata);
    private:
        eastl::string moduleDir;
        std::vector<eastl::string> roots;
        eastl::string mainModuleName;
        ModuleGraph moduleDependecyGraph;
        eastl::map<eastl::string, int, std::less<>> NodeMap;
        eastl::map<eastl::string, registerer, std::less<>> InitializeMap;
        eastl::map<eastl::string, std::unique_ptr<IModule>, std::less<>>
            ModulesMap;
    };

    template<typename ModuleClass>
    struct SStaticallyLinkedModuleRegistrant
    {
        SStaticallyLinkedModuleRegistrant(const char* InModuleName)
        {
            std::function<std::unique_ptr<IModule>(void)> func =
                []()
                {
                    return std::make_unique<ModuleClass>();                     
                };
            GetModuleManager()
                ->RegisterStaticallyLinkedModule(InModuleName, func);
        }
    };

    #define IMPLEMENT_STATIC_MODULE(ModuleImplClass,ModuleName) \
        inline static const Sakura::SPA::SStaticallyLinkedModuleRegistrant\
        <ModuleImplClass> ModuleRegistrant##ModuleName(#ModuleName);

    #define IMPLEMENT_DYNAMIC_MODULE(ModuleImplClass, ModuleName) \
        extern "C" DLLEXPORT Sakura::SPA::IModule* InitializeModule##ModuleName()\
        {\
            return new ModuleImplClass();\
        }
    
}
