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
 * @Date: 2020-05-28 17:26:41
 * @LastEditTime: 2020-06-02 02:02:52
 */ 
#pragma once
#include "PainterStructures.h"

namespace Sakura::Graphics
{
    struct Painter;
}

namespace Sakura::Graphics
{
    struct GPUResource
    {
        enum class ResourceOptions
        {
            Upload,
            Query,
            Default
        };
        virtual ~GPUResource() = default;
    };

    struct GPUTexture : public GPUResource
    {
        enum class TextureType
        {
            Texture1D = 0,
            Texture1DArray = 1,
            Texture2D = 2,
            Texture2DArray = 3,
            Texture2DMultisample = 4,
            TextureCube = 5,
            TextureCubeArray = 6,
            Texture3D = 7,
            Count
        };
        enum class TextureUsage
        {
            Unknown         = 0x0000,
            ShaderRead      = 0x0001,
            ShaderWrite     = 0x0002,
            RenderTarget    = 0x0004,
            PixelFormatView = 0x0010,
        };
        GPUTexture(const GPUTexture::TextureType texType) 
            :type(texType), GPUResource(){}
        virtual ~GPUTexture() = default;
        virtual Extent2D GetExtent() const = 0;
        const GPUTexture::TextureType type;
    };

    struct GPUBuffer : public GPUResource
    {
        enum class BufferUsage
        {
            IndexBuffer,
            VertexBuffer,
            UniformBuffer,
            RayTracingAccelerateStructure
        };
        [[nodiscard]] static GPUBuffer* Create(Painter& painter,
            const BufferUsage usage, const ResourceOptions options, 
            std::uint32_t length, const void* pointer = nullptr);
        virtual ~GPUBuffer() = default;
        GPUBuffer(const BufferUsage bufUsage)
            :usage(bufUsage){}
        virtual std::uint32_t GetSize() const = 0;
        const BufferUsage usage;
    };

    struct GPUSampler : public GPUResource
    {
        virtual ~GPUSampler() = default;
    };
}