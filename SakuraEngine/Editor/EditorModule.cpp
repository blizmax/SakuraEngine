/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-24 13:05:07
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-04-20 23:50:52
 */
#include "EditorModule.h"
#include "SakuraEngine/Core/Core.h"
//#include "VkTestApplication.hpp"

Sakura::fs::file vs_srv
    ("D:\\Coding\\SakuraEngine\\SakuraTestProject\\shaders\\SRV\\SRVVertex.spv",
        'r');  
Sakura::fs::file fs_srv
    ("D:\\Coding\\SakuraEngine\\SakuraTestProject\\shaders\\SRV\\SRVPixel.spv",
        'r');

void EditorModule::OnLoad()
{
    EditorModule::debug_info<Sakura::flags::DEBUG_EDITOR>
        ("EditorModule Loaded!");
	return;
}

void EditorModule::OnUnload()
{
    EditorModule::debug_info<Sakura::flags::DEBUG_EDITOR>
        ("EditorModule Unloaded!");
	return;
}

void EditorModule::MainPluginExec()
{
    EditorModule::debug_info<Sakura::flags::DEBUG_EDITOR>
        ("Editor Module: Main Plugin Exec!");

    //auto app = std::make_unique<VkTestApplication>();
    //auto app = std::make_unique<RenderGraphTestApplication>();
	//app->run();
    return;
}
