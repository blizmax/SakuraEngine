/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-22 12:05:59
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-17 03:57:15
 */
#include "plugin_main.h"
#include <iostream>

void SModule::OnLoad()
{
    std::cout << "SMoudle Loaded!" << std::endl;
}

void SModule::OnUnload()
{
    std::cout << "SMoudle UnLoad!" << std::endl;
}