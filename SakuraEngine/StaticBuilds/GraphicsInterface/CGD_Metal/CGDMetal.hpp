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
 * @Date: 2020-04-28 23:05:58
 * @LastEditTime: 2020-04-30 00:55:41
 */
#pragma once
#include "../GraphicsCommon/CGD.h"
#include "CommandObjects/CommandQueueMtl.h"
#include "mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    class CommandQueueMtl;
    class CommandContextMtl;
}

namespace Sakura::Graphics::Mtl
{
    struct CGDEntityMtl
    {
        // MTL device
        mtlpp::Device device;
        std::unique_ptr<CommandQueueMtl> graphicsQueue;
        std::unique_ptr<CommandQueueMtl> computeQueue;
        std::unique_ptr<CommandQueueMtl> blitQueue;
    };

    class CGDMtl 
    {
        DECLARE_LOGGER("CGDMetal")
    public:
        void Initialize(CGDInfo info);
        void InitializeDevice(void* mainSurface);
        CommandContext* CreateContext(const CommandQueue& queue,
            bool bTransiant = true) const;

    private:
        CGDEntityMtl entity;
    };
}