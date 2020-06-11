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
 * @Date: 2020-03-03 10:39:51
 * @LastEditTime: 2020-04-30 00:07:24
 */
#pragma once
#include "../../GraphicsCommon/CommandObjects/CommandQueue.h"
#include "SakuraEngine/Core/CoreMinimal/CoreMinimal.h"
#include <vulkan/vulkan.h>

namespace Sakura::Graphics::Vk
{
    class CGDVk;
}

namespace Sakura::Graphics::Vk
{
    class CommandQueueVk : simplements CommandQueue
    {
        friend class CGDVk;
        friend class CommandQueueVk;
        friend class CommandBufferVk;
        friend struct FenceVk;
    protected:
        CommandQueueVk(const CGDVk& _cgd,
            std::uint32_t queueFramilyIndex, CommandQueueTypes type);
    public:
        virtual void Submit(CommandBuffer* CommandBuffer) override final;
        virtual void Submit(CommandBuffer* CommandBuffer,
            Fence* fence, uint64 until, uint64 to) override final;
        virtual void Submit(Fence* fence, uint64 completedValue) override final;
        virtual void Wait(Fence* fence, uint64 until) override final;
        virtual void WaitIdle() override final;
        VkQueue vkQueue = VK_NULL_HANDLE;
        std::uint32_t queueFramilyIndex = 0;
        const CGDVk& cgd;
    };
}