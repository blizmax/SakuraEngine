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
 * @Date: 2020-05-02 18:44:12
 * @LastEditTime: 2020-05-02 23:59:53
 */
#pragma once
#include "../../GraphicsCommon/GraphicsObjects/RenderPass.h"
#include "../mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    class CGDMtl;
}

namespace Sakura::Graphics::Mtl
{
    class RenderPassMtl final : simplements RenderPass
    {
        friend class CGDMtl;
        friend class GraphicsPipelineMtl;
        friend class CommandBufferMtl;
    public:
        virtual ~RenderPassMtl() final override;
        mtlpp::RenderPipelineDescriptor renderPipelineDesc;
    protected:
        RenderPassMtl(const RenderPassCreateInfo& info, const CGDMtl& _cgd);
        const CGDMtl& cgd;
    };
}