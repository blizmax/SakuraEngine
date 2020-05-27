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
 * @LastEditTime: 2020-05-28 01:53:18
 */ 
#pragma once
#include "../../Include/Painter.h"
#include "mtlpp/device.hpp"

namespace Sakura::Graphics::Metal
{
    struct PainterMetal final : public Painter
    {
        friend class Painter;
        DECLARE_LOGGER("PainterMetal")
    public:
        inline static constexpr eastl::string_view GetBackEndName()
        {
            return Sakura::Graphics::DefaultBackEndNames::Metal;
        } 

        // Implementations
        [[nodiscard]] virtual Fence* CreateFence() override;
        [[nodiscard]] virtual RenderPass* CreateRenderPass(
            const RenderPassDesc& desc) override;
        [[nodiscard]] virtual Shader* CreateShader(
            const char* data, const std::size_t dataSize,
            const Shader::MacroTable& macroTable = _Shader::nullTable) override;
            
    protected:
        PainterMetal(bool bEnableDebugLayer) 
            :Painter(bEnableDebugLayer)
        {
            device = mtlpp::Device::CreateSystemDefaultDevice();
            if(device.GetPtr() == nullptr)
                PainterMetal::error("Failed to create Metal Device!");
        }
    public:
        mtlpp::Device device;
    };

}