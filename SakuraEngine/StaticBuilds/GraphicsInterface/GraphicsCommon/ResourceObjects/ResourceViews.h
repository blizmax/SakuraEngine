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
 * @Date: 2020-03-05 17:35:59
 * @LastEditTime: 2020-05-08 12:03:59
 */
#pragma once
#include "Core/CoreMinimal/sinterface.h"
#include "Core/CoreMinimal/SDefination.h"
#include "../Flags/CommonFeatures.h"
#include "../Flags/Format.h"
#include "../Flags/GraphicsPipelineStates.h"
#include "Resource.h"

namespace Sakura::Graphics
{
    sinterface CGD;
    sinterface GpuResource;
}

struct VkImageViewCreateInfo;

namespace Sakura::Graphics
{
    inline static bool isImageView(const ResourceViewType type)
    {
        return type <= ImageViewCubeArray;
    }

	struct TextureSubresourceRange
	{
		ImageAspectFlags aspectMask = ImageAspectFlag::ImageAspectColor;
		uint16 baseMipLevel = 0;
		uint16 mipLevels = 1;
		uint16 baseArrayLayer = 0;
		uint16 layerCount = 1;
	};

    const TextureSubresourceRange plainTextureSubresourceRange = 
    {
        ImageAspectFlag::ImageAspectColor,
        0, 1, 0, 1
    };

    struct ResourceViewCreateInfo
    {
        struct Buffer
        {
               
        };
        Format format;
        ResourceViewType viewType;
        union View
        {
            TextureSubresourceRange texture2D;
            Buffer buffer;
        } view;
    };
    
    sinterface ResourceView
    {
        virtual ~ResourceView(){}
        const Format GetFormat(void) const {return format;}
        const ResourceViewType GetViewType(void) const  
        {
            return viewType;
        }
    protected:
        ResourceView(const ResourceViewType vt, const Format fmt)
            :viewType(vt), format(fmt){}
    protected:
        Format format;
        ResourceViewType viewType;
    };
}