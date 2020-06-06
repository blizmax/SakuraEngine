/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-08 13:58:16
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-06 16:30:01
 */
// Excellent Prototype from Star Engine :
// https://github.com/star-e/StarEngine/blob/master/Star/SMap.h
// Thanks for the great idea and work !
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include <EASTL/unordered_map.h>
#include <EASTL/map.h>
#include "Core/EngineUtils/SHash.h"
#include "Core/CoreMinimal/SKeyWords.h"

namespace Sakura
{
    struct StringHasher
    {
        inline std::size_t operator()(const std::string &key) const
        {
            using std::size_t;
            using std::hash;
            return Sakura::hash::hash(key, Sakura::hash::defaultseed);
        }
        
        inline std::size_t operator()(const eastl::string &key) const
        {
            using std::size_t;
            using std::hash;
            return Sakura::hash::hash(key, Sakura::hash::defaultseed);
        }
    };
}