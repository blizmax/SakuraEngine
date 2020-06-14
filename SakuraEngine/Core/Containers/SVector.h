/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-09 09:34:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-14 16:29:03
 */
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include "Core/CoreMinimal/SDefination.h"
#include <boost/container/small_vector.hpp>
#include <EASTL/vector.h>
#ifndef TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS
#define TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS 1
#endif
#include <tbb/concurrent_vector.h>

namespace Sakura
{
    using boost::container::small_vector;

    using eastl::vector;
    
    using tbb::concurrent_vector;
}
