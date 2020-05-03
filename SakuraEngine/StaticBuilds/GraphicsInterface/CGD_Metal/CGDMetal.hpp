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
 * @Date: 2020-04-28 23:05:58
 * @LastEditTime: 2020-05-03 12:50:59
 */
#pragma once
#include "../GraphicsCommon/CGD.h"
#include "mtlpp/mtlpp.hpp"

namespace Sakura::Graphics::Mtl
{
    class CommandQueueMtl;
    class CommandBufferMtl;
    class GraphicsPipelineMtl;
    class SwapChainMtl;
}

namespace Sakura::Graphics::Mtl
{
    struct CGDEntityMtl
    {
        ~CGDEntityMtl();
        // MTL device
        mtlpp::Device device;
        CommandQueueMtl* graphicsQueue;
        CommandQueueMtl* computeQueue;
        CommandQueueMtl* blitQueue;
    };

    class CGDMtl final : public CGD
    {
        DECLARE_LOGGER("CGDMetal")
        friend class SwapChainMtl;
        friend class GraphicsPipelineMtl;
    public:
        virtual void Initialize(CGDInfo info) override final;
        virtual void InitializeDevice(void* mainSurface) override final;

        // mainSurface: NSWindow*
        virtual SwapChain* CreateSwapChain(
            const int width, const int height, void* mainSurface) override final;
       
        virtual void Present(SwapChain* chain) override final;
        virtual void Destroy() override final;
        
        virtual CommandBuffer* CreateCommandBuffer(const CommandQueue& queue,
            ECommandType type, bool bTransiant = true) const override final;
        virtual CommandQueue* GetGraphicsQueue() const override final;
        virtual CommandQueue* GetComputeQueue() const override final;
        virtual CommandQueue* GetCopyQueue() const override final;
        
        virtual Shader* CreateShader(
            const char* data, std::size_t dataSize) override final;
        virtual const char* CompileShader(const char*, std::size_t) final override;
        
        [[nodiscard]] virtual RenderPass* CreateRenderPass(
            const RenderPassCreateInfo& info) const final override;

        [[nodiscard]] virtual GraphicsPipeline* CreateGraphicsPipeline(
            const GraphicsPipelineCreateInfo& info,
            const RenderPass& progress) const final override;

        [[nodiscard]] virtual ComputePipeline* CreateComputePipeline(
            const ComputePipelineCreateInfo& info) const final override;
        
        virtual CommandBuffer* AllocateCommandBuffer(
            const CommandQueue& queue, ECommandType type, bool bTransiant = true) final override;
    
        virtual void FreeCommandBuffer(CommandBuffer* context) final override;
        virtual void FreeAllCommandBuffers(ECommandType typeToDestroy) final override;

        [[nodiscard]] virtual ResourceView* ViewIntoResource(
            const GpuResource&, const ResourceViewCreateInfo&) const final override;

        [[nodiscard]] virtual ResourceView* ViewIntoTexture(
            const GpuTexture&, const Format, const ImageAspectFlags,
            uint32 mipLevels = 1, uint32 baseMip = 0,
            uint32 layerCount = 1, uint32 baseArrayLayer = 0) const final override;
        
        [[nodiscard]] virtual CommandQueue* AllocQueue(CommandQueueTypes type) const final override;

        [[nodiscard]] virtual GpuBuffer* CreateGpuResource(
            const BufferCreateInfo&) const final override;

        [[nodiscard]] virtual GpuTexture* CreateGpuResource(
            const TextureCreateInfo&) const final override;

        virtual void Wait(Fence* toWait, uint64 until) const final override;
        virtual void WaitIdle() const final override;
        [[nodiscard]] virtual Fence* AllocFence(void) final override;

        [[nodiscard]] virtual RootSignature* CreateRootSignature(
            const RootSignatureCreateInfo& sigInfo) const final override;

        virtual const TargetGraphicsinterface GetBackEndAPI(void)
            const final override
        {
            return TargetGraphicsinterface::CGD_TARGET_METAL;
        }

        [[nodiscard]] virtual Sampler* CreateSampler(
            const SamplerCreateInfo&) const final override;
        
        virtual const Format FindDepthFormat(void) const final override;

    private:
        CGDEntityMtl entity;
    };
}