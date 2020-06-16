/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-08 13:58:16
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-16 23:50:12
 */
// Excellent Prototype from Star Engine :
// https://github.com/star-e/StarEngine/blob/master/Star/SMap.h
// Thanks for the great idea and work !
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include <EASTL/unordered_map.h>
#include <EASTL/map.h>
#include "SString.h"
#include "Core/EngineUtils/SHash.h"
#include "Core/CoreMinimal/SKeyWords.h"
#ifndef TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS
#define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
#endif
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_map.h>

namespace Sakura
{
    using eastl::map;
    using eastl::unordered_map;
    using tbb::concurrent_unordered_map;
    using tbb::concurrent_map;
    
    struct StringHasher
    {
        inline std::size_t operator()(const std::string &key) const
        {
            using std::size_t;
            using std::hash;
            return Sakura::hash::hash(key, Sakura::hash::defaultseed);
        }
    };
}