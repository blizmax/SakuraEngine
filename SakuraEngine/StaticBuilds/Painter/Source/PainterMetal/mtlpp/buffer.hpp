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
 * @LastEditTime: 2020-06-04 18:50:48
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include "defines.hpp"
#include "pixel_format.hpp"
#include "resource.hpp"

namespace mtlpp
{
    class Texture;
    class TextureDescriptor;

    class Buffer : public Resource
    {
    public:
        Buffer() { }
        Buffer(const ns::Handle& handle, bool retain = true) 
            : Resource(handle, retain) { }

        uint32_t GetLength() const;
        void*    GetContents();
        void     DidModify(const ns::Range& range) MTLPP_AVAILABLE_MAC(10_11);
        Texture  NewTexture(const TextureDescriptor& descriptor, uint32_t offset, uint32_t bytesPerRow) MTLPP_AVAILABLE_IOS(8_0);
        void     AddDebugMarker(const ns::String& marker, const ns::Range& range) MTLPP_AVAILABLE(10_12, 10_0);
        void     RemoveAllDebugMarkers() MTLPP_AVAILABLE(10_12, 10_0);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}
