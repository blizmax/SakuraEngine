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
 * @Date: 2020-05-03 14:03:28
 * @LastEditTime: 2020-05-04 00:49:33
 */
#pragma once
#include "../../GraphicsCommon/ResourceObjects/Resource.h"
#include "../mtlpp/mtlpp.hpp"
namespace Sakura::Graphics::Mtl
{
    class CGDMtl;
}

namespace Sakura::Graphics::Mtl
{
    struct GpuResourceMtlImage final : public GpuTexture
    {
        friend class CGDMtl;
        friend struct ResourceViewMtlImage;
        virtual ~GpuResourceMtlImage() override final;
        virtual void UpdateValue(
            std::function<void(void*)> func) final override;
        virtual void Map(void** data) override final;
        virtual void Unmap() override final;
    protected:
        GpuResourceMtlImage(const CGDMtl& _cgd, Extent2D _extent);
        const CGDMtl& cgd;
    };

    struct GpuResourceMtlBuffer final : public GpuBuffer
    {
        friend class CGDMtl;
        virtual ~GpuResourceMtlBuffer() override final;
        virtual void UpdateValue(
            std::function<void(void*)> func) final override;
        // !!! BAD PERFORMANCE
        virtual void Map(void** data) override final;
        virtual void Unmap() override final;
    protected:
        void** mapped = nullptr;
        mtlpp::Buffer buffer;
        GpuResourceMtlBuffer(const CGDMtl& _cgd, const BufferCreateInfo& info);
        const CGDMtl& cgd;
    };
}