/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-22 11:26:19
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-17 03:55:46
 */
#include "plugin_1.h"
#include <iostream>

void SModule1::OnLoad()
{
    std::cout << "SMoudle 1 Loaded!" << std::endl;
} 

void SModule1::OnUnload()
{
    std::cout << "SModule 1 Unloaded!" << std::endl;
}
