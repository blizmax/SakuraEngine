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
 * @Date: 2020-04-29 01:38:54
 * @LastEditTime: 2020-05-01 23:57:17
 */
#pragma once
#include "../CGDMetal.hpp"
#include "../../GraphicsCommon/CommandObjects/CommandBuffer.h"
#include "../mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    class CommandQueueMtl;
    class CGDMtl;
}

namespace Sakura::Graphics::Mtl
{
    struct CommandBufferEntityMtl 
    {
        CommandBufferEntityMtl(
            const CGDEntityMtl& _entity, CommandQueueMtl& queue);
        mtlpp::CommandBuffer commandBuffer;
        const CGDEntityMtl& entity;
    };

    class CommandBufferGraphicsMtl final
        : public CommandBufferEntityMtl, simplements CommandBufferGraphics
    {
        friend class CommandQueueMtl;
        friend class CGDMtl;
        CommandBufferGraphicsMtl(
            const CGDEntityMtl& entity, CommandQueueMtl& queue);
    public:
        virtual void Begin() final override;
        virtual void End() final override;
        virtual void Reset() final override;
        virtual void ResourceBarrier(GpuTexture& toTransition,
            const ImageLayout oldLayout, const ImageLayout newLayout,
            const TextureSubresourceRange& = plainTextureSubresourceRange) final override;
        virtual void BeginRenderPass(
		    GraphicsPipeline* gp, const RenderTargetSet& rts) final override;
        virtual void EndRenderPass() final override;
        virtual void Draw(uint32 vertexCount, uint32 instanceCount,
			uint32 firstVertex, uint32 firstInstance) final override;
        virtual void DrawIndexed(const uint32_t indicesCount,
			const uint32_t instanceCount) final override;
        virtual void BindVertexBuffer(const GpuBuffer& vb) final override;
        virtual void BindIndexBuffer(const GpuBuffer& ib,
			const IndexBufferStride stride = IndexBufferStride::IndexBufferUINT32) final override;
        virtual void BindRootArguments(const PipelineBindPoint bindPoint,
			const RootArgument** arguments, uint32_t argumentNum) final override;
        mtlpp::RenderCommandEncoder encoder;
    };
}