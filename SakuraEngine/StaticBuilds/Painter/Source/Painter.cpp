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
 * @Date: 2020-05-27 12:36:03
 * @LastEditTime: 2020-05-28 18:36:55
 */ 
#include "Fence.h"
#include "Painter.h"
#include "Shader.h"
#include "GPUResource.h"
#include "CommandBuffer.h"

using namespace Sakura::Graphics;

Fence* Fence::Create(Painter& painter)
{
    return painter.CreateFence();
}

Shader* Shader::Create(Painter& painter,
    const char* data, const std::size_t dataSize, const Shader::MacroTable& tbl)
{
    return painter.CreateShader(data, dataSize);
}

GPUBuffer* GPUBuffer::Create(Painter& painter,
    const BufferUsage usage, const GPUResource::ResourceOptions options, 
    std::uint32_t length, const void* pointer)
{
    return painter.CreateBuffer(usage, options, length, pointer);
}

RenderCommandBuffer* RenderCommandBuffer::Create(Painter& painter)
{
    return painter.CreateRenderCommandBuffer();
}