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
 * @LastEditTime: 2020-06-05 01:42:31
 */ 
#pragma once
#include <stdint.h>

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
    enum class IndexType
    {
        UINT16 = 0,
        UINT32 = 1,
    };
    
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
        /**
         * @description: Create a render command buffer.
         * @param {Painter&} painter reference. 
         * @return: RenderCommandBuffer allocated
         * @author: SaeruHikari
         */
        [[nodiscard]] static RenderCommandBuffer* Create(Painter&);

        /**
         * @description: Begins a render pass.
         * You must BeginRenderPass before any valid command encoding,
         * Use RenderPass::Create() or painter->CreateRenderPass() to create one.
         * @param {const RenderPass&} render pass to begin.
         * @author: SaeruHikari
         */
        virtual void BeginRenderPass(const RenderPass& pass) = 0;

        /**
         * @description: Ends encoding of a render pass.
         * A valid encoded render command buffer should starts with BeginRenderPass
         * and ends with EndRenderPass.
         * @author: SaeruHikari
         */
        virtual void EndRenderPass() = 0;
        
        /**
         * @description: Set render pipeline (state) for next draws.
         * Mensions that render pipeline contains descriptions and resources needed
         * to start a GPU Drawing Pipeline Cycle.
         * Descriptions: color/depth/stencil attachment format, etc.
         * Resources: shaders and shader entries, etc.
         * @param {const RenderPipeline&} render pipeline to set.
         * @author: SaeruHikari
         */
        virtual void SetRenderPipeline(const RenderPipeline&) = 0;

        /**
         * @description: Sets the vertex buffer for next draw(s).
         * Buffer setted need to be marked with bitflag Usage::VertexBuffer.
         * OtherWise the backends may throw incorrect-buffer-usage errors.
         * @param {const Buffer&} vertexBuffer to set. 
         * @author: SaeruHikari
         */
        virtual void SetVertexBuffer(const GPUBuffer&) = 0;

        /**
         * @description: Draw indexed.
         * Index Buffer setted need to be marked with bitflag Usage::IndexBuffer.
         * OtherWise the backends may throw incorrect-buffer-usage errors.
         * @param {const Buffer&} indexBuffer to set.
         * @author: SaeruHikari
         */
        virtual void DrawIndexed(
            uint32_t indexCount, IndexType indexType,
            const GPUBuffer& indexBuffer, uint32_t indexBufferOffset) = 0;

        /**
         * @description: simply draws vertices provided with last setted vertex buffer.
         * @param {uint32_t vertexStart} Start index of vertices to draw.
         * @param {uint32_t vertexCount} Count of vertices to draw 
         * @author: SaeruHikari
         */
        virtual void Draw(uint32_t vertexStart, uint32_t vertexCount) = 0;
    protected:
        RenderCommandBuffer() = default;
    };
}