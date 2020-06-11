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
 * @Description: 
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-03-02 18:44:11
 * @LastEditTime: 2020-04-30 21:35:22
 */
#pragma once
#include "SakuraEngine/Core/CoreMinimal/CoreMinimal.h"

namespace Sakura::Graphics
{
    sinterface CommandBuffer;
    sinterface Fence;
}

namespace Sakura::Graphics
{
    enum CommandQueueTypes
    {
        ECommandQueueGraphics = 1,
        ECommandQueueCompute = 2,
        ECommandQueueCopy = 4,
        ECommandQueueTypeCount = 3
    };

    sinterface CommandQueue
    {
        CommandQueue(CommandQueueTypes _type)
            :type(_type)
        {
            
        }
        virtual void Submit(CommandBuffer* CommandBuffer) = 0;
        virtual void Submit(CommandBuffer* CommandBuffer,
            Fence* fence, uint64 until, uint64 to) = 0;
        virtual void Submit(Fence* fence, uint64 completedValue) = 0;
        virtual void Wait(Fence* fence, uint64 until) = 0;
        virtual void WaitIdle() = 0;
        CommandQueueTypes GetType() const
        {
            return type;
        }
    protected:
        CommandQueue() = default;
        CommandQueueTypes type;
    };
}