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
 * @Date: 2020-03-06 16:47:38
 * @LastEditTime: 2020-05-05 15:50:48
 */
#pragma once
#include "Core/CoreMinimal/sinterface.h"
#include "Core/CoreMinimal/SDefination.h"
#include "Core/Containers/SString.h"
#include "../ResourceObjects/Shader.h"
#include "Format.h"
#include <vector>
#include "Flags.h"

using namespace Sakura;

namespace Sakura::Graphics
{
    sinterface RootSignature;
}

namespace Sakura::Graphics
{
    struct InputAssemblyStateCreateInfo
    {
        PrimitiveTopology topo = PrimitiveTopology::TriangleList;
        bool primitiveRestartEnable = false;
    };

    struct VertexInputBindingDescription
    {
        uint32 binding;
        uint32 stride;
        VertexInputRate inputRate;
    };

    struct VertexInputAttributeDescription
    {
        uint32 location;
        uint32 binding;
        Format format;
        uint32 offset;
    };

    struct VertexInputStateCreateInfo 
    {
        std::vector<VertexInputBindingDescription> vertexBindingDescriptions;
        std::vector<VertexInputAttributeDescription> vertexAttributeDescriptions;
    };

    struct ViewportStateCreateInfo
    {
        std::vector<Viewport> vps;
        std::vector <Rect2D> scissors;
    };
    
    struct DepthStencilStateCreateInfo
    {
        bool depthTestEnable = true;
        bool depthWriteEnable = true;
        CompareOp depthCompareOp = CompareOp::CompareOpLess;
        bool depthBoundsTestEnable = false;
        bool stencilTestEnable = false;
        float minDepthBounds = 0.f;
        float maxDepthBounds;
    };

    struct ShaderFunction
    {
        ShaderFunction(ShaderStageFlags _stage,
            Shader* _shader, const std::string& _entry)
            : stage(_stage), shader(_shader), entry(_entry)
        {
            funcHandle = shader->GetFunction(_entry);
        }
        ShaderFunction()
        {
            
        }
        auto GetStage() const 
        {
            return stage;
        }
        auto GetShader() const
        {
            return shader;
        }
        const std::string& GetEntry() const
        {
            return entry;
        }
        const void* GetPlatformFunction()
        {
            return funcHandle;
        }
    protected:
        ShaderStageFlags stage;
        Shader* shader = nullptr;
        std::string entry;
        // For metal, this is called MTLFunction in MTLLibrary
        // For vulkan, this handle keeps as nullptr
        // For Direct3D12, this handle keeps as nullptr
        const void* funcHandle = nullptr;
    };

    struct RasterizationStateCreateInfo
    {
        bool depthClampEnable = false;
        CullModes cullMode = CullModes::CullModeNone;
        PolygonMode polygonMode = PolygonMode::PolygonFill;
        FrontFace frontFace = FrontFace::FrontFaceCounterClockWise;
        bool depthBiasEnable = false;
        float lineWidth = 1.f;
        float depthBiasConstantFactor = 0.f;
        float depthBiasClamp = 0.f;
        float depthBiasSlopeFactor = 0.f;
    };

    struct MultisampleStateCreateInfo
    {
        bool sampleShadingEnable = false;
        SampleCountFlag rasterizationSamples 
            = SampleCountFlag::SampleCount_1Bit; 
        float minSampleShading = 1.f;
        bool alphaToCoverageEnable = false;
        bool alphaToOneEnable = false;
    };

    struct ColorBlendAttachmentState
    {
        ColorComoponents colorWriteMask =
            ColorComponentR | ColorComponentG |
            ColorComponentB | ColorComponentA;  
        bool blendEnable = false;
        BlendFactor srcColorBlendFactor = BlendFactor::BlendFactorOne;
        BlendFactor dstColorBlendFactor = BlendFactor::BlendFactorZero;
        BlendOp colorBlendOp = BlendOp::BlendOpAdd;
        BlendFactor srcAlphaBlendFactor = BlendFactor::BlendFactorOne;
        BlendFactor dstAlphaBlendFactor = BlendFactor::BlendFactorZero;
        BlendOp alphaBlendOp = BlendOp::BlendOpAdd;
    };
    inline static const ColorBlendAttachmentState defaultAttachment = {};

    struct ColorBlendStateCreateInfo
    {
        bool logicOpEnable = false;
        LogicOp logicOp = LogicOp::LogicOpCopy;
        std::vector<ColorBlendAttachmentState> colorBlendAttachment = {defaultAttachment};
        float blendConstants[4] = {0.f, 0.f, 0.f, 0.f};
    };

    struct DynamicStateCreateInfo
    {
        const DynamicState* dynamicStates;
        uint32_t dynamicStateCount;
    };

    struct PushConstantRange
    {

    };

    /**
     * @description: fill this structure to Create PSO Object.
     * @author: SaeruHikari
     */
    struct GraphicsPipelineCreateInfo
    {
        InputAssemblyStateCreateInfo inputassembly;
        VertexInputStateCreateInfo vertexInputInfo;
        ViewportStateCreateInfo viewportStateCreateInfo;
        DepthStencilStateCreateInfo depthStencilCreateInfo;
        RasterizationStateCreateInfo rasterizationStateCreateInfo;
        MultisampleStateCreateInfo multisampleStateCreateInfo;
        DynamicStateCreateInfo dynamicStateCreateInfo;
        ColorBlendStateCreateInfo colorBlendStateCreateInfo;
		const RootSignature* rootSignature = nullptr;

        template<typename _ShaderFunction>
        sinline void PushShaderStage(_ShaderFunction&& shaderStage)
        {
            shaderStages.push_back(shaderStage);
        }

        template<typename _ShaderFunction, typename... Ts>
        sinline void PushShaderStage(
            _ShaderFunction&& shaderStage, Ts&&... shaderStages)
        {
            PushShaderStage(shaderStage);
            PushShaderStage(shaderStages...);
        }

        sinline void AddViewport(uint32_t width, uint32_t height)
        {   
			Viewport vp = {};
			vp.height = (float)height; vp.width = (float)width;
            viewportStateCreateInfo.vps.push_back(vp);
        }

        sinline void AddScissor(const Extent2D scissorExtent,
            const Offset2D offset2D)
        {
			Rect2D scissor = {};
            scissor.extent = scissorExtent;
            scissor.offset = offset2D;
            viewportStateCreateInfo.scissors.push_back(scissor);
        }

		sinline void AddScissor(const Extent2D scissorExtent)
		{
			Rect2D scissor = {};
			scissor.extent = scissorExtent;
			viewportStateCreateInfo.scissors.push_back(scissor);
		}

        sinline void AddScissor(const Rect2D scissor)
        {
            viewportStateCreateInfo.scissors.push_back(scissor);
        }

        template<typename _VertexInputAttributeDescription>
        sinline void AddVertexAttribute(
            _VertexInputAttributeDescription&& attribute)
        {
            vertexInputInfo.vertexAttributeDescriptions.push_back(attribute);
            return;
        }

		template<typename _VertexInputAttributeDescription, typename... Ts>
		sinline void AddVertexAttribute(
            _VertexInputAttributeDescription&& attribute, Ts&&... attris)
		{
            AddVertexAttribute(attribute);
            AddVertexAttribute(attris...);
		}

		template<std::size_t n>
		sinline void AddVertexAttributes(
			const std::array<VertexInputAttributeDescription, n>& bindings)
		{
			for (auto i = 0; i < n; i++)
			{
				AddVertexAttribute(bindings[i]);
			}
		}

        template<typename _VertexInputBindingDescription>
        sinline void AddVertexBinding(_VertexInputBindingDescription&& binding)
        {
            vertexInputInfo.vertexBindingDescriptions.push_back(binding);
        }

		template<typename _VertexInputBindingDescription, typename... Ts>
		sinline void AddVertexBinding(
            _VertexInputBindingDescription&& binding, Ts&&... bindings)
		{
            AddVertexBinding(binding);
            AddVertexBinding(bindings...);
		}

		template<typename _VertexInputBindingDescription, int n>
		sinline void AddVertexBinding(
			std::array<_VertexInputBindingDescription, n> bindings)
		{
			for (auto i = 0; i < n; i++)
			{
                AddVertexBinding(bindings[i]);
			}
		}
		std::vector<ShaderFunction> shaderStages;
    };
}
