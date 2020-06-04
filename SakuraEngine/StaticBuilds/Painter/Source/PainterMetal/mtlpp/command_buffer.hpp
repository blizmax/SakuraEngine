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
 * @Date: 2020-06-04 18:06:00
 * @LastEditTime: 2020-06-04 18:40:58
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include "defines.hpp"
#include "ns.hpp"

namespace mtlpp
{
    class Device;
    class CommandQueue;
    class BlitCommandEncoder;
    class RenderCommandEncoder;
    class ParallelRenderCommandEncoder;
    class ComputeCommandEncoder;
    class CommandQueue;
    class Drawable;
    class RenderPassDescriptor;

    enum class CommandBufferStatus
    {
        NotEnqueued = 0,
        Enqueued    = 1,
        Committed   = 2,
        Scheduled   = 3,
        Completed   = 4,
        Error       = 5,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    enum class CommandBufferError
    {
        None                                      = 0,
        Internal                                  = 1,
        Timeout                                   = 2,
        PageFault                                 = 3,
        Blacklisted                               = 4,
        NotPermitted                              = 7,
        OutOfMemory                               = 8,
        InvalidResource                           = 9,
        Memoryless      MTLPP_AVAILABLE_IOS(10_0) = 10,
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class CommandBuffer : public ns::Object
    {
    public:
        CommandBuffer() { }
        CommandBuffer(const ns::Handle& handle, bool retain = true) : ns::Object(handle, retain) { }

        Device              GetDevice() const;
        CommandQueue        GetCommandQueue() const;
        bool                GetRetainedReferences() const;
        ns::String          GetLabel() const;
        CommandBufferStatus GetStatus() const;
        ns::Error           GetError() const;
        double              GetKernelStartTime() const MTLPP_AVAILABLE_IOS(10_3);
        double              GetKernelEndTime() const MTLPP_AVAILABLE_IOS(10_3);
        double              GetGpuStartTime() const MTLPP_AVAILABLE_IOS(10_3);
        double              GetGpuEndTime() const MTLPP_AVAILABLE_IOS(10_3);

        void SetLabel(const ns::String& label);

        void Enqueue();
        void Commit();
        void AddScheduledHandler(std::function<void(const CommandBuffer&)> handler);
        void AddCompletedHandler(std::function<void(const CommandBuffer&)> handler);
        void Present(const Drawable& drawable);
        void PresentAtTime(const Drawable& drawable, double presentationTime);
        void PresentAfterMinimumDuration(const Drawable& drawable, double duration) MTLPP_AVAILABLE_IOS(10_3);
        void WaitUntilScheduled();
        void WaitUntilCompleted();
        BlitCommandEncoder BlitCommandEncoder();
        RenderCommandEncoder RenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor);
        ComputeCommandEncoder ComputeCommandEncoder();
        ParallelRenderCommandEncoder ParallelRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor);
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}
