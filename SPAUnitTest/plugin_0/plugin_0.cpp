/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-22 11:23:44
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-17 03:55:39
 */
#include "plugin_0.h"
#include <iostream>

void SModule0::OnLoad()
{
    std::cout << "SMoudle 0 Loaded!" << std::endl;
} 

void SModule0::OnUnload()
{
    std::cout << "SModule 0 Unloaded!" << std::endl;
}
