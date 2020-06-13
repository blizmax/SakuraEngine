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
 * @Date: 2020-05-27 20:31:41
 * @LastEditTime: 2020-06-13 13:49:25
 */ 
#pragma once
#include "../../Include/Painter.h"
#include "../../Include/CommandQueue.h"
#include "mtlpp/device.hpp"
#include "mtlpp/command_queue.hpp"

namespace Sakura::Graphics
{
    struct RenderCommandBuffer;
}

namespace Sakura::Graphics::Metal
{
    struct CommandQueueMetal final : public CommandQueue
    {
        mtlpp::CommandQueue queue;
    };

    struct PainterMetal final : public Painter
    {
        friend class Painter;
        DECLARE_LOGGER("PainterMetal")
    public:
        virtual ~PainterMetal() = default;
        virtual const Sakura::sstring_view GetBackEndName() const override 
        {
            return Sakura::Graphics::DefaultBackEndNames::Metal;
        } 
        // Implementations
        [[nodiscard]] virtual Fence* CreateFence() override;
        [[nodiscard]] virtual RenderPass* CreateRenderPass(
            const RenderPassDescriptor& desc) override;
        [[nodiscard]] virtual Shader* CreateShaderBinaryCode(
            const char* data, const std::size_t dataSize,
            const Shader::MacroTable& macroTable = _Shader::nullTable) override;
        [[nodiscard]] virtual RenderCommandBuffer* CreateRenderCommandBuffer() override;
        [[nodiscard]] virtual GPUBuffer* CreateBuffer( 
            const GPUBuffer::BufferUsage usage, 
            const GPUResource::ResourceOptions options, 
            std::uint32_t length, const void* pointer = nullptr) override;
        [[nodiscard]] virtual RenderPipeline* CreateRenderPipeline(
            const RenderPipelineDescripor& desc) override;
    protected:
        PainterMetal(bool bEnableDebugLayer) 
            :Painter(bEnableDebugLayer)
        {
            device = mtlpp::Device::CreateSystemDefaultDevice();
            queue.queue = device.NewCommandQueue();
            if(device.GetPtr() == nullptr)
                PainterMetal::error("Failed to create Metal Device!");
        }
    public:
        mtlpp::Device device;
        /**
         * @description: Graphics Queue.
         * @author: SaeruHikari
         */
        CommandQueueMetal queue;
    };

}