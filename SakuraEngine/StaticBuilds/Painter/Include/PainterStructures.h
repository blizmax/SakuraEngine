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
 * @Date: 2020-05-28 17:32:48
 * @LastEditTime: 2020-06-01 01:26:59
 */ 
#pragma once
#include "SakuraEngine/Core/Containers/Containers.h"
#include <cstdint>

namespace Sakura::Graphics
{
    struct GPUTexture;
    struct Shader;
    struct ShaderFunction;
}

namespace Sakura::Graphics
{
    enum class PixelFormat
    {

    };
    enum class VertexFormat
    {

    };
    
    enum class BlendFactor
    {
        Zero                                                = 0,
        One                                                 = 1,
        SourceColor                                         = 2,
        OneMinusSourceColor                                 = 3,
        SourceAlpha                                         = 4,
        OneMinusSourceAlpha                                 = 5,
        DestinationColor                                    = 6,
        OneMinusDestinationColor                            = 7,
        DestinationAlpha                                    = 8,
        OneMinusDestinationAlpha                            = 9,
        SourceAlphaSaturated                                = 10,
        BlendColor                                          = 11,
        OneMinusBlendColor                                  = 12,
        BlendAlpha                                          = 13,
        OneMinusBlendAlpha                                  = 14,
        Source1Color                                        = 15,
        OneMinusSource1Color                                = 16,
        Source1Alpha                                        = 17,
        OneMinusSource1Alpha                                = 18,
    };

    enum class BlendOperation
    {
        Add             = 0,
        Subtract        = 1,
        ReverseSubtract = 2,
        Min             = 3,
        Max             = 4,
    };

    enum class ColorWriteMask
    {
        None  = 0,
        Red   = 0x1 << 3,
        Green = 0x1 << 2,
        Blue  = 0x1 << 1,
        Alpha = 0x1 << 0,
        All   = 0xf
    };

    struct Extent2D
    {
        std::uint32_t width;
        std::uint32_t height;
    };
    
    struct Extent3D
    {
        std::uint32_t width;
        std::uint32_t length;
        std::uint32_t height;
    };

    enum class LoadAction
    {
        DontCare = 0,
        Load     = 1,
        Clear    = 2,
    };

    enum class StoreAction
    {
        DontCare = 0,
        Store = 1,
        //MultisampleResolve = 2, ?
        //StoreAndMultisampleResolve = 3, ?
        //Unknown = 4, ??
    };

    struct RenderPassAttachmentDescriptor
    {
        LoadAction loadAction = LoadAction::Clear;
        StoreAction storeAction = StoreAction::Store;
        GPUTexture* texture = nullptr;
        bool isValid() const
        {
            return texture != nullptr;
        }
    };

    struct Color
    {
        double Red;
        double Green;
        double Blue;
        double Alpha;
    };

    struct RenderPassColorAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
        Color clearColor;
    };

    struct RenderPassDepthAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
        double clearDepth;
    };

    struct RenderPassStencilAttachmentDescriptor : public RenderPassAttachmentDescriptor
    {
        uint32_t clearStencil;
    };

    struct RenderPassDescriptor
    {
        Sakura::SVector<RenderPassColorAttachmentDescriptor> colorAttachments;
        RenderPassDepthAttachmentDescriptor depthAttachment;
        RenderPassStencilAttachmentDescriptor stencilAttachment;
    };



    enum class PrimitiveTopology
    {
        Unspecified = 0,
        Point       = 1,
        Line        = 2,
        Triangle    = 3,
    };

    struct RenderPipelineColorAttachmentDescriptor 
    {
        bool blendingEnabled = false;
        PixelFormat format;
        BlendFactor srcRGBBlendFactor;
        BlendFactor dstRGBBlendFactor;
        BlendOperation rgbBlendOp;
        BlendFactor srcAlphaBlendFactor;
        BlendFactor dstAlphaBlendFactor;
        BlendOperation alphaBlendOp;
        ColorWriteMask colorWriteMask;
    };

    struct VertexLayout
    {
        enum class VertexStepFunction
        {
            Constant                                          = 0,
            PerVertex                                         = 1,
            PerInstance                                       = 2,
            //PerPatch                                          = 3, ?
            //PerPatchControlPoint                              = 4, ?
        };
        struct VertexAttribute
        {
            VertexFormat format;
            uint32_t offset;
        };
        uint32_t stride;
        VertexStepFunction stepFunction;
        eastl::vector<VertexAttribute> attributes;
    };

    struct RenderPipelineDescripor
    {
        Sakura::SVector<RenderPipelineColorAttachmentDescriptor> colorAttachments;
        PixelFormat depthFormat;
        PixelFormat stencilFormat;
        Sakura::SVector<ShaderFunction> shaderFunctions;
        PrimitiveTopology topology = PrimitiveTopology::Triangle;
        VertexLayout vertexLayout;
    };
}