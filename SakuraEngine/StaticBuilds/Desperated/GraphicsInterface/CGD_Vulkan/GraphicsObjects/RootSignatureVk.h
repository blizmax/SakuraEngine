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
 * @Date: 2020-03-18 09:13:31
 * @LastEditTime: 2020-04-18 02:27:29
 */
#pragma once
#include <vector>
#ifdef SAKURA_TARGET_PLATFORM_OSX
#include <boost/container/pmr/string.hpp>
#include <boost/container/pmr/vector.hpp>
#include <boost/container/pmr/map.hpp>
namespace Sakura::SPA
{
    namespace pmr
    {
        using boost::container::string;
        using boost::container::vector;
        using boost::container::map;
    }
}
#else
#include <memory_resource>
#endif
#include "../../GraphicsCommon/GraphicsObjects/RootSignature.h"
#include "vulkan/vulkan.h"
#include "SakuraEngine/Core/EngineUtils/log.h"

namespace Sakura::Graphics::Vk
{
    class RootArgumentVk;
}

namespace Sakura::Graphics::Vk
{
    class RootSignatureVk final : simplements Sakura::Graphics::RootSignature
    {
        friend class CGDVk;
    public:
        virtual ~RootSignatureVk() final override;
        VkDescriptorSetLayout descriptorSetLayout[RootArgumentSetCount + 1];
        VkDescriptorPool pool = VK_NULL_HANDLE;
        [[nodiscard]] virtual RootArgument* CreateArgument(
            const RootArgumentSet targetSet) const override final;
    protected:
        std::vector<VkSampler> staticSamplers;
        VkDescriptorSet staticSamplerSet;
        RootSignatureVk(const CGDVk& _cgd, const RootSignatureCreateInfo& info);
        const CGDVk& cgd;
    };

    class RootArgumentVk final : simplements Sakura::Graphics::RootArgument
    {
        friend class CGDVk;
        friend class RootSignatureVk;
        friend class CommandBufferComputeVk;
        friend class CommandBufferGraphicsVk;
    public:
        VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
        virtual ~RootArgumentVk() override final;
        virtual const SignatureSlotType GetType(void) const override final;
        virtual void UpdateArgument(const RootArgumentAttachment* attachments,
            std::uint32_t attachmentCount) override final;
        virtual const size_t GetSlotNum(void) const override final;
    protected:
		RootArgumentVk(const CGDVk& _cgd, const RootSignatureVk*,
			const RootArgumentSet targetSet,
            const VkDescriptorSetLayout& layout, VkDescriptorPool pool);
        const RootSignatureVk* rootSig;
        uint32_t slotNum = 0;
        const RootArgumentSet targetSet;
        const VkDescriptorSet* staticSamplers;
        SignatureSlotType type;
        const CGDVk& cgd; 
    };

    inline static const VkDescriptorType Transfer(const SignatureSlotType in)
    {
        if(in != AccelerationStructureNv)
            return ((VkDescriptorType)in);
        else 
        {
            switch (in)
            {
            case SignatureSlotType::AccelerationStructureNv:
                return VkDescriptorType::VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;            
            default:
                Sakura::log::error("Vulkan: Failed to transfer SlotType to VkDescriptorType!");
            }
        }
        return VkDescriptorType::VK_DESCRIPTOR_TYPE_END_RANGE;
    }
}