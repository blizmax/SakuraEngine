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
 * @Date: 2020-03-05 01:29:37
 * @LastEditTime: 2020-04-18 02:17:37
 */
#pragma once
#include "../../GraphicsCommon/GraphicsObjects/SwapChain.h"
#include "../../GraphicsCommon/ResourceObjects/Resource.h"
#include "../Flags/FormatVk.h"

namespace Sakura::Graphics
{
    struct Extent2D;
}

namespace Sakura::Graphics::Vk
{
    class CGDVk;
}

namespace Sakura::Graphics::Vk
{
    struct SwapChainVk final : public Sakura::Graphics::SwapChain
    {
        friend class CGDVk;
        SwapChainVk(const VkSwapchainKHR _chain, 
            const CGDVk& _device,const uint32 _chainCount);
        
        virtual ~SwapChainVk() override final;
        virtual Extent2D GetExtent() const override final;
        virtual const GpuTexture& GetDrawable() const override final;
        virtual const ResourceView& GetDrawableView() const override final;
        inline VkFormat GetVkPixelFormat()
        {
            return Transfer(swapChainImageFormat);
        }
        const GpuTexture& GetSwapChainImage(std::size_t frameIndex) const
        {
            return *swapChainImages[frameIndex];
        }
        const ResourceView& GetChainImageView(std::size_t frameIndex) const
        {
            return *resourceViews[frameIndex].get();
        }
        inline uint32 GetCurrentFrame() const
        {
            return currentFrame;
        }
        inline uint32 GetLastFrame() const
        {
            return lastFrame;
        }

        VkSwapchainKHR swapChain;
        VkExtent2D swapChainExtent;
        //
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderCompleteSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;

        uint32 lastFrame;
        uint32 currentFrame = 0;
        std::vector<GpuTexture*> swapChainImages;
        std::vector<std::unique_ptr<ResourceView>> resourceViews;

        uint32_t nextPresent = 0;
        uint32_t currentPresent = 0;
    };
}
