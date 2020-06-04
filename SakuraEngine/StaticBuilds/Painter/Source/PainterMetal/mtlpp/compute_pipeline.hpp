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
 * @LastEditTime: 2020-06-04 19:31:41
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include "defines.hpp"
#include "device.hpp"
#include "argument.hpp"
#include "stage_input_output_descriptor.hpp"

namespace mtlpp
{
    class ComputePipelineReflection : public ns::Object
    {
    public:
        ComputePipelineReflection();
        ComputePipelineReflection(const ns::Handle& handle, bool retain = true)
            : ns::Object(handle, retain) { }

        ns::Array<Argument> GetArguments() const;
    }
    MTLPP_AVAILABLE(10_11, 9_0);

    class ComputePipelineDescriptor : public ns::Object
    {
    public:
        ComputePipelineDescriptor();
        ComputePipelineDescriptor(const ns::Handle& handle, bool retain = true) 
            : ns::Object(handle, retain) { }

        ns::String                 GetLabel() const;
        Function                   GetComputeFunction() const;
        bool                       GetThreadGroupSizeIsMultipleOfThreadExecutionWidth() const;
        StageInputOutputDescriptor GetStageInputDescriptor() const MTLPP_AVAILABLE(10_12, 10_0);

        void SetLabel(const ns::String& label);
        void SetComputeFunction(const Function& function);
        void SetThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool value);
        void SetStageInputDescriptor(const StageInputOutputDescriptor& stageInputDescriptor) const MTLPP_AVAILABLE(10_12, 10_0);

        void Reset();
    }
    MTLPP_AVAILABLE(10_11, 8_0);

    class ComputePipelineState : public ns::Object
    {
    public:
        ComputePipelineState() { }
        ComputePipelineState(const ns::Handle& handle, bool retain = true)
            : ns::Object(handle, retain) { }

        Device   GetDevice() const;
        uint32_t GetMaxTotalThreadsPerThreadgroup() const;
        uint32_t GetThreadExecutionWidth() const;
    }
    MTLPP_AVAILABLE(10_11, 8_0);
}
