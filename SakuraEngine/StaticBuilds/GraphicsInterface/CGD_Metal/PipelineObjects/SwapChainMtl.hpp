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
 * @Date: 2020-05-02 02:23:18
 * @LastEditTime: 2020-05-02 12:33:54
 */
#pragma once
#include "../../GraphicsCommon/GraphicsObjects/SwapChain.h"
#import "SakuraEngine/Core/Containers/SVector.h"
#include "../mtlpp/mtlpp.hpp"
#import <Cocoa/Cocoa.h>

namespace Sakura::Graphics::Mtl
{
    class CGDMtl;
    class CommandBufferGraphicsMtl;
}

namespace Sakura::Graphics::Mtl
{
    // Pass NSWindow and create this chaos thing.
    class SwapChainMtl final : simplements Sakura::Graphics::SwapChain
    {
        friend class CGDMtl;
        SwapChainMtl(const int width,
            const int height, const CGDMtl&, void* _window);
    public:
        class MtlView : public ns::Object
        {
        public:
            MtlView() { }
            MtlView(const ns::Handle& handle);
        };
        virtual Extent2D GetExtent() const final override;
        virtual const GpuTexture& GetDrawable() const final override;
        virtual const ResourceView& GetDrawableView() const final override;
        mtlpp::Drawable GetMtlDrawable() const;
        mtlpp::RenderPassDescriptor GetRenderPassDescriptor() const;

        const CGDMtl& cgd;
        MtlView m_view;
        NSWindow* window = nullptr;
        mutable Sakura::SVector<GpuTexture*> textures;
        mutable Sakura::SVector<ResourceView*> drawableViews;
        uint8 frameIndex = 0;
        uint8 frameCount = 0;
    };
}