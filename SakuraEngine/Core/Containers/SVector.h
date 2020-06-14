/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-09 09:34:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-14 15:53:55
 */
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include "Core/CoreMinimal/SDefination.h"
#include <boost/container/small_vector.hpp>
#include <EASTL/vector.h>

namespace Sakura
{
    template<class T, size_t N>
    using small_vector = boost::container::small_vector<T, N>;

    template<class T>
    using vector = eastl::vector<T>;
}
