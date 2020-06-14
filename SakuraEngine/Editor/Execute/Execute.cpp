/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-24 13:24:40
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-07 01:24:34
 */
//#include "SakuraEngine/Core/EngineUtils/os.h"
#include "Modules.generated.h"//include generated file in the root path
#include "SPA/include/modulemanager.h"
#include "SakuraEngine/StaticBuilds/TaskSystem/TaskSystem.h"
#include "SakuraEngine/Core/Core.h"
#include <iostream>
#include <filesystem>

int main(void)
{
    auto mng = GetModuleManager();
    auto path = std::filesystem::path(Sakura::os::exepath().c_str());
    auto dir = path.remove_filename();
    Sakura::string root = dir.string().c_str();
    mng->Mount(root);
    std::string mainName = "EditorModule";//Need a module as the entry, this module can be the total dispatcher
    mng->MakeModuleGraph(mainName.c_str(), true);
    mng->InitModuleGraph();
    mng->DestroyModuleGraph();
    return 0;
}
