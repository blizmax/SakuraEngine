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
 * @LastEditTime: 2020-06-02 01:25:10
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
    enum class Format
    {
        UNKNOWN,
        R64G64B64A64_UINT,
        R64G64B64A64_SINT,
        R64G64B64A64_SFLOAT,
        
        R64G64B64_UINT,
        R64G64B64_SINT,
        R64G64B64_SFLOAT,

        R32G32B32A32_TYPELESS,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,
        R32G32B32A32_SFLOAT,

        R64G64_UINT,
        R64G64_SINT,
        R64G64_SFLOAT,

        R32G32B32_TYPELESS,
        R32G32B32_UINT,
        R32G32B32_SINT,
        R32G32B32_SFLOAT,

        R16G16B16A16_TYPELESS,
        R16G16B16A16_UNORM,
        R16G16B16A16_SNORM,
        R16G16B16A16_USCALED,
        R16G16B16A16_SSCALED,
        R16G16B16A16_UINT,
        R16G16B16A16_SINT,
        R16G16B16A16_SFLOAT,
        
        R32G32_TYPELESS,
        R32G32_UINT,
        R32G32_SINT,
        R32G32_SFLOAT,
        
        R64_UINT,
        R64_SINT,
        R64_SFLOAT,

        R16G16B16_UNORM,
        R16G16B16_SNORM,
        R16G16B16_USCALED,
        R16G16B16_SSCALED,
        R16G16B16_UINT,
        R16G16B16_SINT,
        R16G16B16_SFLOAT,

        R10G10B10A2_TYPELESS_PACK32,
        R10G10B10A2_UNORM_PACK32,
        R10G10B10A2_SNORM_PACK32,
        R10G10B10A2_USCALED_PACK32,
        R10G10B10A2_SSCALED_PACK32,
        R10G10B10A2_UINT_PACK32,
        R10G10B10A2_SINT_PACK32,

        R10G10B10_XR_BIAS_A2_UNORM_PACK32,

        B10G10R10A2_UNORM_PACK32,
        B10G10R10A2_SNORM_PACK32,
        B10G10R10A2_USCALED_PACK32,
        B10G10R10A2_SSCALED_PACK32,
        B10G10R10A2_UINT_PACK32,
        B10G10R10A2_SINT_PACK32,
        
        A2B10G10R10_UNORM_PACK32,
        A2B10G10R10_SNORM_PACK32,
        A2B10G10R10_USCALED_PACK32,
        A2B10G10R10_SSCALED_PACK32,
        A2B10G10R10_UINT_PACK32,
        A2B10G10R10_SINT_PACK32,

        R9G9B9E5_UFLOAT_PACK32,

        R8G8B8A8_TYPELESS,
        R8G8B8A8_UNORM,
        R8G8B8A8_UNORM_PACK32,
        R8G8B8A8_SNORM,
        R8G8B8A8_SNORM_PACK32,
        R8G8B8A8_USCALED,
        R8G8B8A8_USCALED_PACK32,
        R8G8B8A8_SSCALED,
        R8G8B8A8_SSCALED_PACK32,
        R8G8B8A8_UINT,
        R8G8B8A8_UINT_PACK32,
        R8G8B8A8_SINT,
        R8G8B8A8_SINT_PACK32,
        R8G8B8A8_SRGB,
        R8G8B8A8_SRGB_PACK32,
        
        B8G8R8A8_TYPELESS,
        B8G8R8A8_UNORM,
        B8G8R8A8_SNORM,
        B8G8R8A8_USCALED,
        B8G8R8A8_SSCALED,
        B8G8R8A8_UINT,
        B8G8R8A8_SINT,
        B8G8R8A8_SRGB,

        R11G11B10_UFLOAT_PACK32,
        
        B8G8R8X8_TYPELESS,
        B8G8R8X8_UNORM,
        B8G8R8X8_SRGB,

        R16G16_TYPELESS,
        R16G16_UNORM,
        R16G16_SNORM,
        R16G16_USCALED,
        R16G16_SSCALED,
        R16G16_UINT,
        R16G16_SINT,
        R16G16_SFLOAT,
        
        R32_TYPELESS,
        R32_UINT,
        R32_SINT,
        R32_SFLOAT,
        R8G8B8_UNORM,
        R8G8B8_SNORM,
        R8G8B8_USCALED,
        R8G8B8_SSCALED,
        R8G8B8_UINT,
        R8G8B8_SINT,
        R8G8B8_SRGB,
        
        B8G8R8_UNORM,
        B8G8R8_SNORM,
        B8G8R8_USCALED,
        B8G8R8_SSCALED,
        B8G8R8_UINT,
        B8G8R8_SINT,
        B8G8R8_SRGB,

        B5G5R5A1_UNORM_PACK16,
        A1B5G5R5_UNORM_PACK16,
        A1R5G5B5_UNORM_PACK16,
        A4B4G4R4_UNORM_PACK16,
        A4R4G4B4_UNORM_PACK16,
        
        R5G6B5_UNORM_PACK16,
        B5G6R5_UNORM_PACK16,

        R8G8_TYPELESS,
        R8G8_UNORM,
        R8G8_SNORM,
        R8G8_USCALED,
        R8G8_SSCALED,
        R8G8_UINT,
        R8G8_SINT,
        R8G8_SRGB,

        R16_TYPELESS,
        R16_UNORM,
        R16_SNORM,
        R16_USCALED,
        R16_SSCALED,
        R16_UINT,
        R16_SINT,
        R16_SFLOAT,

        G4R4_UNORM_PACK8,
        R4G4_UNORM_PACK8,

        R8_TYPELESS,
        R8_UNORM,
        R8_SNORM,
        R8_USCALED,
        R8_SSCALED,
        R8_UINT,
        R8_SINT,
        R8_SRGB,
        
        A8_UNORM,
        R1_UNORM,
        R32G8X24_TYPELESS_2PACK32,
        
        R32_SFLOAT_X8X24_TYPELESS_2PACK32,
        X32_TYPELESS_G8X24_UINT_2PACK32,
        
        D32_SFLOAT_S8_UINT,
        R24G8_TYPELESS_PACK32,
        D24_UNORM_S8_UINT,
        R24_UNORM_X8_TYPELESS_PACK32,
        X24_TYPELESS_G8_UINT_PACK32,
        D24_UNORM_X8_TYPELESS_PACK32,
        D32_SFLOAT,

        D16_UNORM_S8_UINT,
        D16_UNORM,

        S8_UINT,
        
        BC1_TYPELESS_BLOCK,
        BC1_RGBA_UNORM_BLOCK,
        BC1_RGBA_SRGB_BLOCK,
        BC1_UNORM_BLOCK,
        BC1_SRGB_BLOCK,

        BC2_TYPELESS_BLOCK,
        BC2_UNORM_BLOCK,
        BC2_SRGB_BLOCK,

        BC3_TYPELESS_BLOCK,
        BC3_UNORM_BLOCK,
        BC3_SRGB_BLOCK,

        BC4_TYPELESS_BLOCK,
        BC4_UNORM_BLOCK,
        BC4_SNORM_BLOCK,

        BC5_TYPELESS_BLOCK,
        BC5_UNORM_BLOCK,
        BC5_SNORM_BLOCK,

        BC6H_TYPELESS_BLOCK,
        BC6H_UFLOAT_BLOCK,
        BC6H_SFLOAT_BLOCK,

        BC7_TYPELESS_BLOCK,
        BC7_UNORM_BLOCK,
        BC7_SRGB_BLOCK,
        
        ETC2_R8G8B8A8_UNORM_BLOCK,
        ETC2_R8G8B8A8_SRGB_BLOCK,
        ETC2_R8G8B8A1_UNORM_BLOCK,
        ETC2_R8G8B8A1_SRGB_BLOCK,

        ETC2_R8G8B8_UNORM_BLOCK,
        ETC2_R8G8B8_SRGB_BLOCK,
        
        EAC_R11G11_UNORM_BLOCK,
        EAC_R11G11_SNORM_BLOCK,
        EAC_R11_UNORM_BLOCK,
        EAC_R11_SNORM_BLOCK,

        ASTC_4x4_UNORM_BLOCK,
        ASTC_4x4_SRGB_BLOCK,
        ASTC_4x4_SFLOAT_BLOCK_EXT,

        ASTC_5x4_UNORM_BLOCK,
        ASTC_5x4_SRGB_BLOCK,
        ASTC_5x4_SFLOAT_BLOCK_EXT,

        ASTC_5x5_UNORM_BLOCK,
        ASTC_5x5_SRGB_BLOCK,
        ASTC_5x5_SFLOAT_BLOCK_EXT,

        ASTC_6x5_UNORM_BLOCK,
        ASTC_6x5_SRGB_BLOCK,
        ASTC_6x5_SFLOAT_BLOCK_EXT,

        ASTC_6x6_UNORM_BLOCK,
        ASTC_6x6_SRGB_BLOCK,
        ASTC_6x6_SFLOAT_BLOCK_EXT,
        
        ASTC_8x5_UNORM_BLOCK,
        ASTC_8x5_SRGB_BLOCK,
        ASTC_8x5_SFLOAT_BLOCK_EXT,

        ASTC_8x6_UNORM_BLOCK,
        ASTC_8x6_SRGB_BLOCK,
        ASTC_8x6_SFLOAT_BLOCK_EXT,

        ASTC_8x8_UNORM_BLOCK,
        ASTC_8x8_SRGB_BLOCK,
        ASTC_8x8_SFLOAT_BLOCK_EXT,

        ASTC_10x5_UNORM_BLOCK,
        ASTC_10x5_SRGB_BLOCK,
        ASTC_10x5_SFLOAT_BLOCK_EXT,

        ASTC_10x6_UNORM_BLOCK,
        ASTC_10x6_SRGB_BLOCK,
        ASTC_10x6_SFLOAT_BLOCK_EXT,

        ASTC_10x8_UNORM_BLOCK,
        ASTC_10x8_SRGB_BLOCK,
        ASTC_10x8_SFLOAT_BLOCK_EXT,

        ASTC_10x10_UNORM_BLOCK,
        ASTC_10x10_SRGB_BLOCK,
        ASTC_10x10_SFLOAT_BLOCK_EXT,

        ASTC_12x10_UNORM_BLOCK,
        ASTC_12x10_SRGB_BLOCK,
        ASTC_12x10_SFLOAT_BLOCK_EXT,

        ASTC_12x12_UNORM_BLOCK,
        ASTC_12x12_SRGB_BLOCK,
        ASTC_12x12_SFLOAT_BLOCK_EXT,

        R12X4G12X4B12X4A12X4_UNORM_4PACK16,
        R10X6G10X6B10X6A10X6_UNORM_4PACK16,
        R12X4G12X4_UNORM_2PACK16,
        R10X6G10X6_UNORM_2PACK16,
        R12X4_UNORM_PACK16,
        R10X6_UNORM_PACK16,
        R8G8_B8G8_UNORM,
        G16B16_G16R16_422_UNORM,
        G12X4B12X4_G12X4R12X4_422_UNORM_4PACK16,
        G10X6B10X6_G10X6R10X6_422_UNORM_4PACK16,
        G8B8_G8R8_422_UNORM,
        G8R8_G8B8_UNORM,
        B16G16_R16G16_422_UNORM,
        B12X4G12X4_R12X4G12X4_422_UNORM_4PACK16,
        B10X6G10X6_R10X6G10X6_422_UNORM_4PACK16,
        B8G8_R8G8_422_UNORM,

        G16_B16_R16_3PLANE_444_UNORM,
        G16_B16_R16_3PLANE_422_UNORM,
        // ----------------------
        G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
        G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
        G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
        G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
        G16_B16_R16_3PLANE_420_UNORM,
        G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
        G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
        G8_B8_R8_3PLANE_444_UNORM,
        G8_B8_R8_3PLANE_422_UNORM,
        G8_B8_R8_3PLANE_420_UNORM,
        G16_B16R16_2PLANE_422_UNORM,
        G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
        G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
        G16_B16R16_2PLANE_420_UNORM,
        G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
        G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
        G8_B8R8_2PLANE_422_UNORM,
        G8_B8R8_2PLANE_420_UNORM,
        PVRTC1_4BPP_UNORM_BLOCK_IMG,
        PVRTC1_4BPP_SRGB_BLOCK_IMG,
        PVRTC1_2BPP_UNORM_BLOCK_IMG,
        PVRTC1_2BPP_SRGB_BLOCK_IMG,
        PVRTC2_4BPP_UNORM_BLOCK_IMG,
        PVRTC2_4BPP_SRGB_BLOCK_IMG,
        PVRTC2_2BPP_UNORM_BLOCK_IMG,
        PVRTC2_2BPP_SRGB_BLOCK_IMG,
        //--------------------------------------------------------------
        // common formats (dxgi and vulkan)
        S_R32G32B32A32_UINT = R32G32B32A32_UINT,
        S_R32G32B32A32_SINT = R32G32B32A32_SINT,
        S_R32G32B32A32_SFLOAT = R32G32B32A32_SFLOAT,
        S_R32G32B32_UINT = R32G32B32_UINT,
        S_R32G32B32_SINT = R32G32B32_SINT,
        S_R32G32B32_SFLOAT = R32G32B32_SFLOAT,
        S_R16G16B16A16_UNORM = R16G16B16A16_UNORM,
        S_R16G16B16A16_SNORM = R16G16B16A16_SNORM,
        S_R16G16B16A16_UINT = R16G16B16A16_UINT,
        S_R16G16B16A16_SINT = R16G16B16A16_SINT,
        S_R16G16B16A16_SFLOAT = R16G16B16A16_SFLOAT,
        S_R32G32_UINT = R32G32_UINT,
        S_R32G32_SINT = R32G32_SINT,
        S_R32G32_SFLOAT = R32G32_SFLOAT,
        S_R10G10B10A2_UNORM_PACK32 = R10G10B10A2_UNORM_PACK32,
        S_R10G10B10A2_UINT_PACK32 = R10G10B10A2_UINT_PACK32,
        S_R9G9B9E5_UFLOAT_PACK32 = R9G9B9E5_UFLOAT_PACK32,
        S_R8G8B8A8_UNORM = R8G8B8A8_UNORM,
        S_R8G8B8A8_SNORM = R8G8B8A8_SNORM,
        S_R8G8B8A8_UINT = R8G8B8A8_UINT,
        S_R8G8B8A8_SINT = R8G8B8A8_SINT,
        S_R8G8B8A8_SRGB = R8G8B8A8_SRGB,
        S_B8G8R8A8_UNORM = B8G8R8A8_UNORM,
        S_B8G8R8A8_SRGB = B8G8R8A8_SRGB,
        S_R11G11B10_UFLOAT_PACK32 = R11G11B10_UFLOAT_PACK32,
        S_R16G16_UNORM = R16G16_UNORM,
        S_R16G16_SNORM = R16G16_SNORM,
        S_R16G16_UINT = R16G16_UINT,
        S_R16G16_SINT = R16G16_SINT,
        S_R16G16_SFLOAT = R16G16_SFLOAT,
        S_R32_UINT = R32_UINT,
        S_R32_SINT = R32_SINT,
        S_R32_SFLOAT = R32_SFLOAT,
        S_B5G5R5A1_UNORM_PACK16 = B5G5R5A1_UNORM_PACK16,
        S_B5G6R5_UNORM_PACK16 = B5G6R5_UNORM_PACK16,
        S_R8G8_UNORM = R8G8_UNORM,
        S_R8G8_SNORM = R8G8_SNORM,
        S_R8G8_UINT = R8G8_UINT,
        S_R8G8_SINT = R8G8_SINT,
        S_R16_UNORM = R16_UNORM,
        S_R16_SNORM = R16_SNORM,
        S_R16_UINT = R16_UINT,
        S_R16_SINT = R16_SINT,
        S_R16_SFLOAT = R16_SFLOAT,
        S_R8_UNORM = R8_UNORM,
        S_R8_SNORM = R8_SNORM,
        S_R8_UINT = R8_UINT,
        S_R8_SINT = R8_SINT,
        S_D32_SFLOAT_S8_UINT = D32_SFLOAT_S8_UINT,
        S_D24_UNORM_S8_UINT = D24_UNORM_S8_UINT,
        S_D32_SFLOAT = D32_SFLOAT,
        S_D16_UNORM = D16_UNORM,
        S_BC1_UNORM_BLOCK = BC1_UNORM_BLOCK,
        S_BC1_SRGB_BLOCK = BC1_SRGB_BLOCK,
        S_BC2_UNORM_BLOCK = BC2_UNORM_BLOCK,
        S_BC2_SRGB_BLOCK = BC2_SRGB_BLOCK,
        S_BC3_UNORM_BLOCK = BC3_UNORM_BLOCK,
        S_BC3_SRGB_BLOCK = BC3_SRGB_BLOCK,
        S_BC4_UNORM_BLOCK = BC4_UNORM_BLOCK,
        S_BC4_SNORM_BLOCK = BC4_SNORM_BLOCK,
        S_BC5_UNORM_BLOCK = BC5_UNORM_BLOCK,
        S_BC5_SNORM_BLOCK = BC5_SNORM_BLOCK,
        S_BC6H_UFLOAT_BLOCK = BC6H_UFLOAT_BLOCK,
        S_BC6H_SFLOAT_BLOCK = BC6H_SFLOAT_BLOCK,
        S_BC7_UNORM_BLOCK = BC7_UNORM_BLOCK,
        S_BC7_SRGB_BLOCK = BC7_SRGB_BLOCK,
    };
    using VertexFormat = Format;
    using PixelFormat = Format;
    
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

    enum ColorWriteMasks
    {
        None  = 0,
        Red   = 0x1 << 3,
        Green = 0x1 << 2,
        Blue  = 0x1 << 1,
        Alpha = 0x1 << 0,
        All   = 0xf
    };
    using ColorWriteMask = uint32_t;

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