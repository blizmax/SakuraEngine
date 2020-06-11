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
 * @Date: 2020-05-28 02:32:38
 * @LastEditTime: 2020-06-05 01:43:07
 */ 
#pragma once
#include "../../Include/CommandBuffer.h"
#include "mtlpp/command_buffer.hpp"
#include "mtlpp/render_command_encoder.hpp"

namespace Sakura::Graphics::Metal
{
    struct CommandQueueMetal;
}

namespace Sakura::Graphics::Metal
{
    struct RenderCommandBufferMetal final : public RenderCommandBuffer
    {
        friend class PainterMetal;
        ~RenderCommandBufferMetal() = default;
        virtual void Signal(Fence& fence) override;
        virtual void Wait(Fence& fence) override;
        virtual void Commit() override;
        virtual void Present(const Drawable& drawable) override;
        virtual void WaitUntilCompleted() override;
    
        // Render CommandBuffer interfaces
        virtual void BeginRenderPass(const RenderPass& pass) override;
        virtual void EndRenderPass() override;
        virtual void SetRenderPipeline(const RenderPipeline& pipeline) override;
        virtual void SetVertexBuffer(const GPUBuffer& vertexBuffer) override;
        virtual void DrawIndexed(
            uint32_t indexCount, IndexType indexType,
            const GPUBuffer& indexBuffer, uint32_t indexBufferOffset) override;
        virtual void Draw(uint32_t vertexStart, uint32_t vertexCount) override;

        mtlpp::CommandBuffer commandBuffer;
        mtlpp::RenderCommandEncoder encoder;
    protected:
        RenderCommandBufferMetal(mtlpp::CommandQueue& MetalQueue);
        mtlpp::PrimitiveType next_draw_prim;
    };
}