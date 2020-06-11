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
 * @Date: 2020-06-04 18:06:00
 * @LastEditTime: 2020-06-04 20:03:53
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include "defines.hpp"
#include "depth_stencil.hpp"
#include "device.hpp"

namespace mtlpp
{
    enum class SamplerMinMagFilter
    {
        Nearest = 0,
        Linear  = 1,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerMipFilter
    {
        NotMipmapped = 0,
        Nearest      = 1,
        Linear       = 2,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerAddressMode
    {
        ClampToEdge                                   = 0,
        MirrorClampToEdge  MTLPP_AVAILABLE_MAC(10_11) = 1,
        Repeat                                        = 2,
        MirrorRepeat                                  = 3,
        ClampToZero                                   = 4,
        ClampToBorderColor MTLPP_AVAILABLE_MAC(10_12) = 5,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class SamplerBorderColor
    {
        TransparentBlack = 0,  // {0,0,0,0}
        OpaqueBlack = 1,       // {0,0,0,1}
        OpaqueWhite = 2,       // {1,1,1,1}
    };

    class SamplerDescriptor : public ns::Object
    {
    public:
        SamplerDescriptor();
        SamplerDescriptor(const ns::Handle& handle, bool retain = true) 
            : ns::Object(handle, retain) { }

        SamplerMinMagFilter GetMinFilter() const;
        SamplerMinMagFilter GetMagFilter() const;
        SamplerMipFilter    GetMipFilter() const;
        uint32_t            GetMaxAnisotropy() const;
        SamplerAddressMode  GetSAddressMode() const;
        SamplerAddressMode  GetTAddressMode() const;
        SamplerAddressMode  GetRAddressMode() const;
        SamplerBorderColor  GetBorderColor() const MTLPP_AVAILABLE_MAC(10_12);
        bool                IsNormalizedCoordinates() const;
        float               GetLodMinClamp() const;
        float               GetLodMaxClamp() const;
        CompareFunction     GetCompareFunction() const MTLPP_AVAILABLE(10_11, 9_0);
        ns::String          GetLabel() const;

        void SetMinFilter(SamplerMinMagFilter minFilter);
        void SetMagFilter(SamplerMinMagFilter magFilter);
        void SetMipFilter(SamplerMipFilter mipFilter);
        void SetMaxAnisotropy(uint32_t maxAnisotropy);
        void SetSAddressMode(SamplerAddressMode sAddressMode);
        void SetTAddressMode(SamplerAddressMode tAddressMode);
        void SetRAddressMode(SamplerAddressMode rAddressMode);
        void SetBorderColor(SamplerBorderColor borderColor) MTLPP_AVAILABLE_MAC(10_12);
        void SetNormalizedCoordinates(bool normalizedCoordinates);
        void SetLodMinClamp(float lodMinClamp);
        void SetLodMaxClamp(float lodMaxClamp);
        void SetCompareFunction(CompareFunction compareFunction) MTLPP_AVAILABLE(10_11, 9_0);
        void SetLabel(const ns::String& label);
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class SamplerState : public ns::Object
    {
    public:
        SamplerState() { }
        SamplerState(const ns::Handle& handle, bool retain = true) 
            : ns::Object(handle, retain) { }

        ns::String GetLabel() const;
        Device     GetDevice() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

