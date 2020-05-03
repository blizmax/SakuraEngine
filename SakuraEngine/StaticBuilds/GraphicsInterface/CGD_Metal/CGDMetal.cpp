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
 * @Date: 2020-04-28 23:06:28
 * @LastEditTime: 2020-05-02 19:17:18
 */
#include "CGDMetal.hpp"
#include <iostream>
#include "CommandObjects/CommandQueueMtl.h"
#include "CommandObjects/CommandBufferMtl.h"
#include "ResourceObjects/ShaderMtl.h"
#include "PipelineObjects/SwapChainMtl.hpp"
#include "PipelineObjects/RenderPassMtl.h"

using namespace Sakura::Graphics::Mtl;
using namespace Sakura::Graphics;

CGDEntityMtl::~CGDEntityMtl()
{
    delete graphicsQueue;
    delete computeQueue;
    delete blitQueue;
}

void CGDMtl::Initialize(CGDInfo info)
{
    CGDMtl::debug_info("CGDMtl: Create Device");
    entity.device = mtlpp::Device::CreateSystemDefaultDevice();
    if(!entity.device.Validate())
    {
        CGDMtl::debug_error("CGDMtl: Create Metal Default Device Failed!");
    }
}

void CGDMtl::InitializeDevice(void* mainSurface)
{
    entity.graphicsQueue = new CommandQueueMtl(
        entity.device.NewCommandQueue(), CommandQueueTypes::ECommandQueueGraphics);
    entity.computeQueue = new CommandQueueMtl(
        entity.device.NewCommandQueue(), CommandQueueTypes::ECommandQueueCompute);
    entity.blitQueue = new CommandQueueMtl(
        entity.device.NewCommandQueue(), CommandQueueTypes::ECommandQueueCopy);
}

SwapChain* CGDMtl::CreateSwapChain(const int width, const int height, void* mainSurface)
{
    SwapChain* result = new SwapChainMtl(width, height, *this, mainSurface);
    return result;
}

Shader* CGDMtl::CreateShader(const char* data, std::size_t dataSize)
{
    mtlpp::Library library 
        = entity.device.NewLibrary(data, mtlpp::CompileOptions(), nullptr);
    if(!library.Validate())
    {
        CGDMtl::debug_error("CGDMtl: Create Metal Shader Failed!");
    }
    return new ShaderMtl(library);
}

CommandQueue* CGDMtl::GetGraphicsQueue() const
{
    return entity.graphicsQueue;
}

CommandQueue* CGDMtl::GetComputeQueue() const
{
    return entity.computeQueue;
}

CommandQueue* CGDMtl::GetCopyQueue() const
{
    return entity.blitQueue;
}

const char* Sakura::Graphics::Mtl::CGDMtl::CompileShader(const char* src, std::size_t)
{
    return src;
}

Sakura::Graphics::RenderPass* Sakura::Graphics::Mtl::CGDMtl::CreateRenderPass(const RenderPassCreateInfo& info) const
{
    RenderPassMtl* result = new RenderPassMtl(info, *this);
    return result;
}

Sakura::Graphics::GraphicsPipeline* Sakura::Graphics::Mtl::CGDMtl::CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& info, const RenderPass& progress) const
{
    return nullptr;
}

Sakura::Graphics::ComputePipeline* Sakura::Graphics::Mtl::CGDMtl::CreateComputePipeline(const ComputePipelineCreateInfo& info) const
{
    return nullptr;
}

Sakura::Graphics::CommandBuffer* Sakura::Graphics::Mtl::CGDMtl::AllocateCommandBuffer(const CommandQueue& queue, ECommandType type, bool bTransiant /*= true*/)
{
    return nullptr;
}

void Sakura::Graphics::Mtl::CGDMtl::FreeCommandBuffer(CommandBuffer* context)
{
    return;
}

void Sakura::Graphics::Mtl::CGDMtl::FreeAllCommandBuffers(ECommandType typeToDestroy)
{

}

Sakura::Graphics::ResourceView* Sakura::Graphics::Mtl::CGDMtl::ViewIntoResource(const GpuResource&, const ResourceViewCreateInfo&) const
{
    return nullptr;
}

Sakura::Graphics::ResourceView* Sakura::Graphics::Mtl::CGDMtl::ViewIntoTexture(const GpuTexture&, const Format, const ImageAspectFlags, uint32 mipLevels /*= 1*/, uint32 baseMip /*= 0*/, uint32 layerCount /*= 1*/, uint32 baseArrayLayer /*= 0*/) const
{
    return nullptr;
}

Sakura::Graphics::CommandQueue* Sakura::Graphics::Mtl::CGDMtl::AllocQueue(CommandQueueTypes type) const
{
    return nullptr;
}

Sakura::Graphics::GpuBuffer* Sakura::Graphics::Mtl::CGDMtl::CreateGpuResource(const BufferCreateInfo&) const
{
    return nullptr;
}

Sakura::Graphics::GpuTexture* Sakura::Graphics::Mtl::CGDMtl::CreateGpuResource(const TextureCreateInfo&) const
{
    return nullptr;
}

void Sakura::Graphics::Mtl::CGDMtl::Wait(Fence* toWait, uint64 until) const
{

}

void Sakura::Graphics::Mtl::CGDMtl::WaitIdle() const
{

}

Sakura::Graphics::Fence* Sakura::Graphics::Mtl::CGDMtl::AllocFence(void)
{
    return nullptr;
}

Sakura::Graphics::RootSignature* Sakura::Graphics::Mtl::CGDMtl::CreateRootSignature(const RootSignatureCreateInfo& sigInfo) const
{
    return nullptr;
}

Sakura::Graphics::Sampler* Sakura::Graphics::Mtl::CGDMtl::CreateSampler(const SamplerCreateInfo&) const
{
    return nullptr;
}

const Sakura::Graphics::Format Sakura::Graphics::Mtl::CGDMtl::FindDepthFormat(void) const
{
    return Sakura::Graphics::Format::D32_SFLOAT;
}

void Sakura::Graphics::Mtl::CGDMtl::Present(SwapChain* chain)
{
    auto mtlChain = (SwapChainMtl*)chain;
    CommandBufferGraphicsMtl* presentCommandBuffer 
        = (CommandBufferGraphicsMtl*)CreateCommandBuffer(
            *GetGraphicsQueue(), ECommandType::ECommandBufferGraphics);
    presentCommandBuffer->commandBuffer.Present(mtlChain->GetDrawable());
    presentCommandBuffer->commandBuffer.Commit();
    presentCommandBuffer->commandBuffer.WaitUntilCompleted();
    delete presentCommandBuffer;
    return;
}

void Sakura::Graphics::Mtl::CGDMtl::Destroy()
{

}
