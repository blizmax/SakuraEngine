/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Descripttion: CopyRight SaeruHikari
 * @Version: 0.1.0
 * @Author: SaeruHikari
 * @Date: 2020-02-02 17:25:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-14 16:37:50
 */
#pragma once
#define EA_CPP14_CONSTEXPR constexpr
#include "Core/CoreMinimal/CoreMinimal.h"
#include "SVariant.h"
#include "SMap.h"
#include "SString.h"
#include "SVector.h"
#include "MemoryPool.h"
#include <EASTL/unique_ptr.h>
#include <EASTL/bitset.h>
#include <EASTL/functional.h>

namespace Sakura
{
    using eastl::function;
    using eastl::unique_ptr;
}