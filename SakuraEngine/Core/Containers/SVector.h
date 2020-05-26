/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-09 09:34:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-04-17 03:40:41
 */
#pragma once
#include "Core/CoreMinimal/SDefination.h"
#include <vector>
#include <boost/container/small_vector.hpp>

namespace Sakura
{
    template<class T, size_t N>
    using SSmallVector = boost::container::small_vector<T, N>;

    template<class T>
    using SVector = eastl::vector<T>;
}
