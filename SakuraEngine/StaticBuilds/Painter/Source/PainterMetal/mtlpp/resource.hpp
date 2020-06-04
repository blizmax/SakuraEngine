/*
 * @CopyRight: MIT License
 * Copyright (c) 2020 SaeruHikari
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THESOFTWARE.
 * 
 * 
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-05-27 01:40:41
 * @LastEditTime: 2020-06-04 18:51:20
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include "defines.hpp"
#include "ns.hpp"

namespace mtlpp
{
    class Heap;

    static const uint32_t ResourceCpuCacheModeShift        = 0;
    static const uint32_t ResourceStorageModeShift         = 4;
    static const uint32_t ResourceHazardTrackingModeShift  = 8;

    enum class PurgeableState
    {
        KeepCurrent = 1,
        NonVolatile = 2,
        Volatile    = 3,
        Empty       = 4,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class CpuCacheMode
    {
        DefaultCache  = 0,
        WriteCombined = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class StorageMode
    {
        Shared                                = 0,
        Managed    MTLPP_AVAILABLE(10_11, NA) = 1,
        Private                               = 2,
        Memoryless MTLPP_AVAILABLE(NA, 10_0)  = 3,
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    enum ResourceOptions
    {
        CpuCacheModeDefaultCache                                = uint32_t(CpuCacheMode::DefaultCache)  << ResourceCpuCacheModeShift,
        CpuCacheModeWriteCombined                               = uint32_t(CpuCacheMode::WriteCombined) << ResourceCpuCacheModeShift,

        StorageModeShared           MTLPP_AVAILABLE(10_11, 9_0) = uint32_t(StorageMode::Shared)     << ResourceStorageModeShift,
        StorageModeManaged          MTLPP_AVAILABLE(10_11, NA)  = uint32_t(StorageMode::Managed)    << ResourceStorageModeShift,
        StorageModePrivate          MTLPP_AVAILABLE(10_11, 9_0) = uint32_t(StorageMode::Private)    << ResourceStorageModeShift,
        StorageModeMemoryless       MTLPP_AVAILABLE(NA, 10_0)   = uint32_t(StorageMode::Memoryless) << ResourceStorageModeShift,

        HazardTrackingModeUntracked MTLPP_AVAILABLE(NA, 10_0)   = 0x1 << ResourceHazardTrackingModeShift,

        OptionCpuCacheModeDefault                               = CpuCacheModeDefaultCache,
        OptionCpuCacheModeWriteCombined                         = CpuCacheModeWriteCombined,
    };
    using ResourceOptionsVal = uint32_t;
    MTLPP_AVAILABLE(10_11, 8_0);

    class Resource : public ns::Object
    {
    public:
        Resource() { }
        Resource(const ns::Handle& handle, bool retain = true) 
            : ns::Object(handle, retain) { }

        ns::String   GetLabel() const;
        CpuCacheMode GetCpuCacheMode() const;
        StorageMode  GetStorageMode() const MTLPP_AVAILABLE(10_11, 9_0);
        Heap         GetHeap() const MTLPP_AVAILABLE(NA, 10_0);
        bool         IsAliasable() const MTLPP_AVAILABLE(NA, 10_0);

        void SetLabel(const ns::String& label);

        PurgeableState SetPurgeableState(PurgeableState state);
        void MakeAliasable() const MTLPP_AVAILABLE(NA, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}
