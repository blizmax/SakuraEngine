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
 * @Date: 2020-05-28 22:43:31
 * @LastEditTime: 2020-05-29 20:13:11
 */ 
#pragma once
#include <iostream>

namespace Sakura::Graphics
{
    struct Painter;
}
struct SDL_Window;

namespace Sakura::Graphics
{
    struct Drawable
    {

    };
    
    struct SwapChain
    {
        friend struct Painter;

        /**
         * @description: Drawable is a handle that stands for the backbuffer index.
         * @return: Drawable Handle of the back-buffer.
         * @author: SaeruHikari
         */
        virtual const Drawable& GetDrawable() const = 0;

        /**
         * @description: Get Frame Count of the SwapChain.
         * When tripleBufferring is on this returns 3, else returns 2.
         * @return: Maximum Frame Count
         * @author: SaeruHikari
         */
        virtual std::uint32_t GetFrameCount() const = 0;
        //virtual RenderPassDescriptor GetDefaultRenderPassDescriptor() const = 0;
    protected:
        SwapChain(Painter& painter, const std::uint32_t frameCount){}
    };
}