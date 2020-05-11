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
 * @Date: 2020-05-03 14:03:37
 * @LastEditTime: 2020-05-08 12:09:56
 */
#include "GpuResourceMtl.h"
#include "../CGDMetal.hpp"

using namespace Sakura::Graphics::Mtl;

GpuResourceMtlTexture::~GpuResourceMtlTexture()
{

}

const Sakura::Graphics::ResourceView* GpuResourceMtlTexture::GetDefaultView() const
{
    return this;
}

Sakura::Graphics::ResourceView* GpuResourceMtlTexture::GetDefaultView()
{
    return this;
}

GpuResourceMtlTexture::GpuResourceMtlTexture(const CGDMtl& _cgd,
    const mtlpp::Texture& tex, Extent2D _extent)
    :cgd(_cgd), texture(tex), GpuTexture(_extent),
    ResourceView(ResourceViewType::ImageView2D)
{
    
}

void GpuResourceMtlTexture::Map(void** data)
{
    
}

void GpuResourceMtlTexture::Unmap()
{
    
}

void GpuResourceMtlTexture::UpdateValue(std::function<void(void*)> func)
{
    //func(buffer.GetContents());
}

GpuResourceMtlBuffer::~GpuResourceMtlBuffer()
{
    
}

GpuResourceMtlBuffer::GpuResourceMtlBuffer(const CGDMtl& _cgd,
    const BufferCreateInfo& info)
    :cgd(_cgd), usages(info.usage), GpuBuffer({(uint32)info.size, 1})
{
    auto options = mtlpp::ResourceOptions::HazardTrackingModeUntracked | 0;
    if(info.cpuAccess != CPUAccessFlags::None)
        options |= mtlpp::ResourceOptions::StorageModeShared;
    else
    {
        options |= mtlpp::ResourceOptions::StorageModePrivate;
        if(info.cpuAccess & CPUAccessFlags::Read)
            options |= mtlpp::ResourceOptions::CpuCacheModeWriteCombined;
        else
            options |= mtlpp::ResourceOptions::CpuCacheModeDefaultCache;
    }
    buffer = _cgd.entity.device.NewBuffer(info.size, options);
}

void GpuResourceMtlBuffer::Map(void** data)
{
    memcpy(data, buffer.GetContents(), buffer.GetLength());
    mapped = data;
}

void GpuResourceMtlBuffer::Unmap()
{
    memcpy(buffer.GetContents(), mapped, buffer.GetLength());
}

void GpuResourceMtlBuffer::UpdateValue(std::function<void(void*)> func)
{
    func(buffer.GetContents());
}

ResourceViewMtlImage::ResourceViewMtlImage(
    const CGDMtl& _cgd, const GpuResource& res,
    const ResourceViewCreateInfo& info)
    :cgd(_cgd), ResourceView(info.viewType)
{

}

ResourceViewMtlImage::ResourceViewMtlImage(const CGDMtl& _cgd,
    const mtlpp::Texture& tex, const ResourceViewCreateInfo& info)
    :cgd(_cgd), ResourceView(info.viewType), texture(tex)
{

}