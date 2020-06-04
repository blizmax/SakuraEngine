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
 * @Date: 2020-05-28 00:38:26
 * @LastEditTime: 2020-06-04 02:36:59
 */ 
#pragma once

namespace Sakura::Graphics
{
    struct Fence;
    struct Painter;
    struct Drawable;
    struct RenderPass;
    struct RenderPipeline;
    struct GPUBuffer;
}

namespace Sakura::Graphics
{
    struct CommandBuffer
    {
        CommandBuffer() = default;
        virtual ~CommandBuffer() = default;

    public:
        /**
         * @description: Signal a Fence.
         * @param {Fence&} reference of the fence to be signaled
         * @author: SaeruHikari
         */
        virtual void Signal(Fence& fence) = 0;

        /**
         * @description: Wait for a Fence.
         * @param {Fence&} reference of the fence to wait
         * @author: SaeruHikari
         */
        virtual void Wait(Fence& fence) = 0;

        virtual void WaitUntilCompleted() = 0;

        /**
         * @description: Commit command buffer to the queue.
         * @author: SaeruHikari
         */
        virtual void Commit() = 0;

        /**
         * @description: Present the drawable to screen.
         * @param {const Drawable&} Drawable Handle to present.
         * @author: SaeruHikari
         */
        virtual void Present(const Drawable& drawable) = 0;
    };

    struct RenderCommandBuffer : public CommandBuffer
    {
        virtual ~RenderCommandBuffer() = default;
        static RenderCommandBuffer* Create(Painter&);
        virtual void BeginRenderPass(const RenderPass& pass) = 0;
        virtual void EndRenderPass() = 0;
        virtual void SetRenderPipeline(const RenderPipeline&) = 0;
        virtual void SetVertexBuffer(const GPUBuffer&) = 0;
    protected:
        RenderCommandBuffer() = default;
    };
}