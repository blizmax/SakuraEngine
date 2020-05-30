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
 * @Date: 2020-05-28 23:07:52
 * @LastEditTime: 2020-05-29 21:06:13
 */ 
#pragma once
#include "../../Include/SwapChain.h"
#include "mtlpp/drawable.hpp"
#include "PainterMetal.h"

namespace Sakura::Graphics::Metal
{
    struct DrawableMetal final : public Drawable
    {
        mtlpp::Drawable drawable;
    };
    
    struct SwapChainMetal final : public SwapChain
    {
        friend struct PainterMetal;
    public:
        virtual std::uint32_t GetFrameCount() const override;
        virtual const Drawable& GetDrawable() const override;
    public:
        template<typename... Args>
        static SwapChain* Create(Painter& painter,
            const std::uint32_t frameCount, Args... args) 
        {
            return new SwapChainMetal(painter, frameCount, args...);
        }
        class NSWindowH : public ns::Object
        {
        public:
            NSWindowH() { }
            NSWindowH(const ns::Handle& handle) : ns::Object(handle) { }
        };
        class MtlView : public ns::Object
        {
        public:
            MtlView() { }
            MtlView(const ns::Handle& handle) : ns::Object(handle) { }
        };
    protected:
        SwapChainMetal(
            Painter& painter, const std::uint32_t frameCount, 
            SwapChainMetal::NSWindowH val);

        MtlView m_view;
        mutable DrawableMetal currentDrawable;
    };
}