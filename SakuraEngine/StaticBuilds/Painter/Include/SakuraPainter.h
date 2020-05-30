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
 * @Date: 2020-05-27 20:33:10
 * @LastEditTime: 2020-05-29 19:15:14
 */ 
#pragma once
#include "../Source/PainterMetal/PainterMetal.h"
#include "../Source/PainterMetal/SwapChainMetal.hpp"
#include "CommandBuffer.h"
#include "CommandQueue.h"

namespace Sakura::Graphics
{
    struct AsyncComputeExtension : public Extension
    {
        struct QueueSet : public Extension::Data
        {
            eastl::unique_ptr<CommandQueue> computeQueue;
            eastl::unique_ptr<CommandQueue> blitQueue;
        };
        AsyncComputeExtension() = default;
        inline static const eastl::vector<eastl::string_view> supportedBackEnds = {
            "Metal",
            "Direct3D12",
            "Vulkan",
        };
        static bool EnableIf(Painter* painter)
        {
            if(eastl::find(
                supportedBackEnds.begin(),
                supportedBackEnds.end(), painter->GetBackEndName())
                    != supportedBackEnds.end())
                return true;
            else return false;
        }
        static QueueSet& GetQueueSet(Painter& painter)
        {
            if(painter.GetDataRef<AsyncComputeExtension>().ptr == nullptr)
            {
                painter.GetDataRef<AsyncComputeExtension>().ptr
                    = new QueueSet();
            }
            return *((QueueSet*)painter.GetDataRef<AsyncComputeExtension>().ptr);
        }
        static CommandQueue& GetComputeQueue(Painter& painter)
        {
            if(GetQueueSet(painter).computeQueue.get() != nullptr)
                return *GetQueueSet(painter).computeQueue.get();
            else 
                assert(0 && "AsyncComputeExtension: No Valide Compute Queue!");
        }
        static CommandQueue& GetBlitQueue(Painter& painter)
        {
            if(GetQueueSet(painter).blitQueue.get() != nullptr)
                return *GetQueueSet(painter).blitQueue.get();
            else 
                assert(0 && "AsyncComputeExtension: No Valide Blit Queue!");
        }
        inline static constexpr const char* name = "AsyncComputeExtension";
    };
}