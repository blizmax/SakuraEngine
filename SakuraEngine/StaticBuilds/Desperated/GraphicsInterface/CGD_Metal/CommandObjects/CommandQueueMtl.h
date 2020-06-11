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
 * @Date: 2020-04-29 22:41:04
 * @LastEditTime: 2020-04-30 00:48:16
 */
#pragma once
#include "../mtlpp/mtlpp.hpp"
#include "../../GraphicsCommon/CommandObjects/CommandQueue.h"


namespace Sakura::Graphics::Mtl
{
    class CommandQueueMtl final : public CommandQueue
    {
    public:
        CommandQueueMtl(mtlpp::CommandQueue _queue, CommandQueueTypes _type);
        virtual void Submit(CommandBuffer* CommandBuffer) override final;
        virtual void Submit(CommandBuffer* CommandBuffer,
            Fence* fence, uint64 until, uint64 to) override final;
        virtual void Submit(Fence* fence, uint64 completedValue) override final;
        virtual void Wait(Fence* fence, uint64 until) override final;
        virtual void WaitIdle() override final;
        mtlpp::CommandQueue queue;
    };
}