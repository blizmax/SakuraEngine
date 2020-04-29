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
 * @LastEditTime: 2020-04-30 01:06:16
 */
#pragma once
#include "../../GraphicsCommon/CommandObjects/CommandContext.h"
#include "../mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    struct SpecifiedEncoder
    {
        ~SpecifiedEncoder()
        {
            next.reset();
            // !Warning: to keep the order of encoders' destructiion,
            // please add extra works below next's reset.
        }
        void SpwanNext(ECommandType cmdType)
        {
            
        }
        std::unique_ptr<mtlpp::CommandEncoder> encoder;
        ECommandType cmdType;
        std::unique_ptr<SpecifiedEncoder> next;
    };

    using CommandBuffersMtl = mtlpp::CommandBuffer;
    class CommandContextMtl : simplements CommandContext
    {
    public:
        virtual void Begin() override final;

        virtual void End() override final;

        virtual void BeginRenderPass(
            GraphicsPipeline* gp, const RenderTargetSet& rts) override final;

        virtual void EndRenderPass() override final;

        virtual void BeginComputePass(ComputePipeline* gp) override final;

        virtual void DispatchCompute(uint32 groupCountX, 
            uint32 groupCountY, uint32 groupCountZ) override final;

        virtual void Draw(uint32 vertexCount, uint32 instanceCount,
            uint32 firstVertex, uint32 firstInstance) override final;
        
        virtual void DrawIndexed(const uint32 indicesCount,
            const uint32 instanceCount) override final;

        virtual void BindVertexBuffer(const GpuBuffer& vb) override final;

        virtual void BindIndexBuffer(const GpuBuffer& ib,
            const IndexBufferStride stride = IndexBufferStride::IndexBufferUINT32) override final;
        
        virtual void BindRootParameters(const PipelineBindPoint bindPoint,
            const RootParameter** arguments, uint32 argumentNum) final override;

    private:
        std::unique_ptr<SpecifiedEncoder> encoderHeader;
        CommandBuffersMtl commandBuffers;
        SpecifiedEncoder* cursor = nullptr;
    };

}