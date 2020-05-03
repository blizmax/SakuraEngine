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
 * @Date: 2020-05-02 18:09:00
 * @LastEditTime: 2020-05-03 12:53:49
 */
#pragma once
#include "../../GraphicsCommon/GraphicsObjects/GraphicsPipeline.h"
#include "../mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    class CGDMtl;
    class RenderPassMtl;
}

namespace Sakura::Graphics::Mtl
{
    class GraphicsPipelineMtl final : simplements GraphicsPipeline
    {
        friend class CGDMtl;
        friend class RenderPassMtl;
    public:
        virtual ~GraphicsPipelineMtl() override final;
    protected:
        GraphicsPipelineMtl(const GraphicsPipelineCreateInfo& info,
            const RenderPassMtl& prog, const CGDMtl& cgd);
    protected:
        mtlpp::RenderPipelineState renderPipelineState;
        const RenderPassMtl& pass;
        const CGDMtl& cgd;
    };
}