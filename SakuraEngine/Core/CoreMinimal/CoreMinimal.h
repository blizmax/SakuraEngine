/*
 * @Descripttion: The minmum core of the Engine.
 * @Version: Do not edit
 * @Author: SaeruHikari
 * @Date: 2020-02-02 09:36:54
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-12 14:48:15
 */
#pragma once
// Concepts
#include "SFlags.h"
// Definations
#include "SDefination.h"
// UUID
#include "SGUID.h"
// Interfaces
#include "sinterface.h"
// Assert
#include "SAssert.h"
#ifdef SAKURA_TARGET_PLATFORM_WIN
#include "SWinDefination.h"
#elif defined(SAKURA_TARGET_PLATFFORM_OSX)
#include "SMacDefination.h"
#elif defined(SAKURA_TARGET_PLATFORM_LINUX)
#include "SLinuxDefination.h"
#elif defined(SAKURA_TARGET_PLATFORM_UNKNOWN)
static_assert(0, "NO TARGET PLATFORM!");
#endif
