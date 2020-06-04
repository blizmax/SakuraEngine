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
 * @LastEditTime: 2020-06-04 19:05:15
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
    class Drawable : public ns::Object
    {
    public:
        Drawable() { }
        Drawable(const ns::Handle& handle, bool retain = true) 
            : ns::Object(handle, retain) { }

        double   GetPresentedTime() const MTLPP_AVAILABLE_IOS(10_3);
        uint64_t GetDrawableID() const MTLPP_AVAILABLE_IOS(10_3);

        void Present();
        void PresentAtTime(double presentationTime);
        void PresentAfterMinimumDuration(double duration) MTLPP_AVAILABLE_IOS(10_3);
        void AddPresentedHandler(std::function<void(const Drawable&)> handler) MTLPP_AVAILABLE_IOS(10_3);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}

