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
 * @Date: 2020-05-03 00:03:51
 * @LastEditTime: 2020-05-03 12:53:18
 */
#pragma once
#include "../mtlpp/mtlpp.hpp"
#include "../../GraphicsCommon/Flags/Flags.h"

#define FORMAT_MAPPER_MTL() \
    MTL_FORMAT_MAPPING(UNKNOWN, Invalid);\
    MTL_FORMAT_MAPPING(A8_UNORM, A8Unorm)\
    MTL_FORMAT_MAPPING(R8_UNORM, R8Unorm)\
    MTL_FORMAT_MAPPING(R8_SRGB, R8Unorm_sRGB)\
    MTL_FORMAT_MAPPING(R8_SNORM, R8Snorm)\
    MTL_FORMAT_MAPPING(R8_UINT, R8Uint)\
    MTL_FORMAT_MAPPING(R8_SINT, R8Sint)\
    MTL_FORMAT_MAPPING(R16_UNORM, R16Unorm)\
    MTL_FORMAT_MAPPING(R16_SNORM, R16Snorm)\
    MTL_FORMAT_MAPPING(R16_UINT, R16Uint)\
    MTL_FORMAT_MAPPING(R16_SINT, R16Sint)\
    MTL_FORMAT_MAPPING(R16_SFLOAT, R16Float)\
    MTL_FORMAT_MAPPING(R8G8_UNORM, RG8Unorm)\
    MTL_FORMAT_MAPPING(R8G8_SRGB, RG8Unorm_sRGB)\
    MTL_FORMAT_MAPPING(R8G8_SNORM, RG8Snorm)\
    MTL_FORMAT_MAPPING(R8G8_UINT, RG8Uint)\
    MTL_FORMAT_MAPPING(R8G8_SINT, RG8Sint)\
    MTL_FORMAT_MAPPING(B5G6R5_UNORM_PACK16, B5G6R5Unorm)\
    MTL_FORMAT_MAPPING(A1B5G5R5_UNORM_PACK16, A1BGR5Unorm)\
    MTL_FORMAT_MAPPING(A4B4G4R4_UNORM_PACK16, ABGR4Unorm)\
    MTL_FORMAT_MAPPING(B5G5R5A1_UNORM_PACK16, BGR5A1Unorm)\
    MTL_FORMAT_MAPPING(R32_UINT, R32Uint)\
    MTL_FORMAT_MAPPING(R32_SINT, R32Sint)\
    MTL_FORMAT_MAPPING(R32_SFLOAT, R32Float)\
    MTL_FORMAT_MAPPING(R16G16_UNORM, RG16Unorm)\
    MTL_FORMAT_MAPPING(R16G16_SNORM, RG16Snorm)\
    MTL_FORMAT_MAPPING(R16G16_UINT, RG16Uint)\
    MTL_FORMAT_MAPPING(R16G16_SINT, RG16Sint)\
    MTL_FORMAT_MAPPING(R16G16_SFLOAT, RG16Float)\
    MTL_FORMAT_MAPPING(R8G8B8A8_UNORM, RGBA8Unorm)\
    MTL_FORMAT_MAPPING(R8G8B8A8_SRGB, RGBA8Unorm_sRGB)\
    MTL_FORMAT_MAPPING(R8G8B8A8_SNORM, RGBA8Snorm)\
    MTL_FORMAT_MAPPING(R8G8B8A8_UINT, RGBA8Uint)\
    MTL_FORMAT_MAPPING(R8G8B8A8_SINT, RGBA8Sint)\
    MTL_FORMAT_MAPPING(B8G8R8A8_UNORM, BGRA8Unorm)\
    MTL_FORMAT_MAPPING(B8G8R8A8_SRGB, BGRA8Unorm_sRGB)\
    MTL_FORMAT_MAPPING(R10G10B10A2_UNORM_PACK32, RGB10A2Unorm)\
    MTL_FORMAT_MAPPING(R10G10B10A2_UINT_PACK32, RGB10A2Uint)\
    MTL_FORMAT_MAPPING(S_R11G11B10_UFLOAT_PACK32, RG11B10Float)\
    MTL_FORMAT_MAPPING(S_R9G9B9E5_UFLOAT_PACK32, RGB9E5Float)\
    MTL_FORMAT_MAPPING(R32G32_UINT, RG32Uint)\
    MTL_FORMAT_MAPPING(R32G32_SINT, RG32Sint)\
    MTL_FORMAT_MAPPING(R32G32_SFLOAT, RG32Float)\
    MTL_FORMAT_MAPPING(R16G16B16A16_UNORM, RGBA16Unorm)\
    MTL_FORMAT_MAPPING(R16G16B16A16_SNORM, RGBA16Snorm)\
    MTL_FORMAT_MAPPING(R16G16B16A16_UINT, RGBA16Uint)\
    MTL_FORMAT_MAPPING(R16G16B16A16_SINT, RGBA16Sint)\
    MTL_FORMAT_MAPPING(R16G16B16A16_SFLOAT, RGBA16Float)\
    MTL_FORMAT_MAPPING(R32G32B32A32_UINT, RGBA32Uint)\
    MTL_FORMAT_MAPPING(R32G32B32A32_SINT, RGBA32Sint)\
    MTL_FORMAT_MAPPING(R32G32B32A32_SFLOAT, RGBA32Float)\
    MTL_FORMAT_MAPPING(BC1_RGBA_UNORM_BLOCK, BC1_RGBA)\
    MTL_FORMAT_MAPPING(BC1_RGBA_SRGB_BLOCK, BC1_RGBA_sRGB)\
    MTL_FORMAT_MAPPING(BC2_UNORM_BLOCK, BC2_RGBA)\
    MTL_FORMAT_MAPPING(BC2_SRGB_BLOCK, BC2_RGBA_sRGB)\
    MTL_FORMAT_MAPPING(BC3_UNORM_BLOCK, BC3_RGBA)\
    MTL_FORMAT_MAPPING(BC3_SRGB_BLOCK, BC3_RGBA_sRGB)\
    MTL_FORMAT_MAPPING(BC4_UNORM_BLOCK, BC4_RUnorm)\
    MTL_FORMAT_MAPPING(BC4_SNORM_BLOCK, BC4_RSnorm)\
    MTL_FORMAT_MAPPING(BC5_UNORM_BLOCK, BC5_RGUnorm)\
    MTL_FORMAT_MAPPING(BC5_SNORM_BLOCK, BC5_RGSnorm)\
    MTL_FORMAT_MAPPING(BC6H_SFLOAT_BLOCK, BC6H_RGBFloat)\
    MTL_FORMAT_MAPPING(BC6H_UFLOAT_BLOCK, BC6H_RGBUfloat)\
    MTL_FORMAT_MAPPING(BC7_UNORM_BLOCK, BC7_RGBAUnorm)\
    MTL_FORMAT_MAPPING(BC7_SRGB_BLOCK, BC7_RGBAUnorm_sRGB)\
    MTL_FORMAT_MAPPING(PVRTC1_2BPP_UNORM_BLOCK_IMG, PVRTC_RGB_2BPP)\
    MTL_FORMAT_MAPPING(EAC_R11_UNORM_BLOCK, EAC_R11Unorm)\
    MTL_FORMAT_MAPPING(EAC_R11_SNORM_BLOCK, EAC_R11Snorm)\
    MTL_FORMAT_MAPPING(EAC_R11G11_UNORM_BLOCK, EAC_RG11Unorm)\
    MTL_FORMAT_MAPPING(EAC_R11G11_SNORM_BLOCK, EAC_RG11Snorm)\
    MTL_FORMAT_MAPPING(ETC2_R8G8B8_UNORM_BLOCK, ETC2_RGB8)\
    MTL_FORMAT_MAPPING(ETC2_R8G8B8_SRGB_BLOCK, ETC2_RGB8_sRGB)\
    MTL_FORMAT_MAPPING(ETC2_R8G8B8A1_UNORM_BLOCK, ETC2_RGB8A1)\
    MTL_FORMAT_MAPPING(ETC2_R8G8B8A1_SRGB_BLOCK, ETC2_RGB8A1_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_4x4_SRGB_BLOCK, ASTC_4x4_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_5x4_SRGB_BLOCK, ASTC_5x4_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_5x5_SRGB_BLOCK, ASTC_5x5_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_6x5_SRGB_BLOCK, ASTC_6x5_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_6x6_SRGB_BLOCK, ASTC_6x6_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_8x5_SRGB_BLOCK, ASTC_8x5_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_8x6_SRGB_BLOCK, ASTC_8x6_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_8x8_SRGB_BLOCK, ASTC_8x8_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_10x5_SRGB_BLOCK, ASTC_10x5_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_10x6_SRGB_BLOCK, ASTC_10x6_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_10x8_SRGB_BLOCK, ASTC_10x8_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_10x10_SRGB_BLOCK, ASTC_10x10_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_12x10_SRGB_BLOCK, ASTC_12x10_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_12x12_SRGB_BLOCK, ASTC_12x12_sRGB)\
    MTL_FORMAT_MAPPING(ASTC_4x4_UNORM_BLOCK, ASTC_4x4_LDR)\
    MTL_FORMAT_MAPPING(ASTC_5x4_UNORM_BLOCK, ASTC_5x4_LDR)\
    MTL_FORMAT_MAPPING(ASTC_5x5_UNORM_BLOCK, ASTC_5x5_LDR)\
    MTL_FORMAT_MAPPING(ASTC_6x5_UNORM_BLOCK, ASTC_6x5_LDR)\
    MTL_FORMAT_MAPPING(ASTC_6x6_UNORM_BLOCK, ASTC_6x6_LDR)\
    MTL_FORMAT_MAPPING(ASTC_8x5_UNORM_BLOCK, ASTC_8x5_LDR)\
    MTL_FORMAT_MAPPING(ASTC_8x6_UNORM_BLOCK, ASTC_8x6_LDR)\
    MTL_FORMAT_MAPPING(ASTC_8x8_UNORM_BLOCK, ASTC_8x8_LDR)\
    MTL_FORMAT_MAPPING(ASTC_10x5_UNORM_BLOCK, ASTC_10x5_LDR)\
    MTL_FORMAT_MAPPING(ASTC_10x6_UNORM_BLOCK, ASTC_10x6_LDR)\
    MTL_FORMAT_MAPPING(ASTC_10x8_UNORM_BLOCK, ASTC_10x8_LDR)\
    MTL_FORMAT_MAPPING(ASTC_10x10_UNORM_BLOCK, ASTC_10x10_LDR)\
    MTL_FORMAT_MAPPING(ASTC_12x10_UNORM_BLOCK, ASTC_12x10_LDR)\
    MTL_FORMAT_MAPPING(ASTC_12x12_UNORM_BLOCK, ASTC_12x12_LDR)\
    MTL_FORMAT_MAPPING(G8B8_G8R8_422_UNORM, GBGR422)\
    MTL_FORMAT_MAPPING(B8G8_R8G8_422_UNORM, BGRG422)\
    MTL_FORMAT_MAPPING(D16_UNORM, Depth16Unorm)\
    MTL_FORMAT_MAPPING(D32_SFLOAT, Depth32Float)\
    MTL_FORMAT_MAPPING(S8_UINT, Stencil8)\
    MTL_FORMAT_MAPPING(D24_UNORM_S8_UINT, Depth24Unorm_Stencil8)\
    MTL_FORMAT_MAPPING(D32_SFLOAT_S8_UINT, Depth32Float_Stencil8)\
    MTL_FORMAT_MAPPING(X24_TYPELESS_G8_UINT_PACK32, X24_Stencil8)\

//VK_NON_DEF

#define MTL_FORMAT_MAPPING(format, mtlformat) \
{case Format::format: \
return mtlpp::PixelFormat::mtlformat;}

#define MTL_NON_DEF(format)\
{case Format::format: \
std::string val##format = "Vulkan Format not supported: "; \
std::string fmt##format = #format; \
Sakura::log::warn(val##format + fmt##format); \
return mtlpp::PixelFormat::Invalid;}

using namespace Sakura::Graphics;

namespace Sakura::Graphics::Mtl
{
    static mtlpp::PixelFormat Transfer(const Sakura::Graphics::Format format)
    {
        switch (format)
        {
            FORMAT_MAPPER_MTL()
        default:
            return mtlpp::PixelFormat::Invalid;
        }
    }
}

#undef MTL_FORMAT_MAPPING
#undef MTL_NON_DEF
#define MTL_FORMAT_MAPPING(format, mtlformat) \
case mtlpp::PixelFormat::mtlformat:\
return Format::format; 
#define MTL_NON_DEF(format) 

namespace Sakura::Graphics::Mtl
{
    static Sakura::Graphics::Format Transfer(const mtlpp::PixelFormat format)
    {
        switch (format)
        {
            FORMAT_MAPPER_MTL()
        default:
            return Sakura::Graphics::Format::UNKNOWN;
        }
    }
}


#define BLEND_FACTOR_CASE(factor, mtlppf)\
case Sakura::Graphics::BlendFactor::factor:\
    return mtlpp::BlendFactor::mtlppf;

namespace Sakura::Graphics::Mtl
{
    inline mtlpp::BlendFactor Transfer(Sakura::Graphics::BlendFactor factor)
    {
        switch (factor)
        {
        BLEND_FACTOR_CASE(BlendFactorZero, Zero);
        BLEND_FACTOR_CASE(BlendFactorOne, One);
        BLEND_FACTOR_CASE(BlendFactorSrcColor, SourceColor);
        BLEND_FACTOR_CASE(BlendFactorOneMinusSrcColor, SourceColor);
        BLEND_FACTOR_CASE(BlendFactorSrcAlpha, SourceAlpha);
        BLEND_FACTOR_CASE(BlendFactorOneMinusSrcAlpha, OneMinusSourceAlpha);
        BLEND_FACTOR_CASE(BlendFactorDstColor, DestinationColor);
        BLEND_FACTOR_CASE(BlendFactorOneMinusDstColor, OneMinusDestinationColor);
        BLEND_FACTOR_CASE(BlendFactorDstAlpha, DestinationAlpha);
        BLEND_FACTOR_CASE(BlendFactorOneMinusDstAlpha, OneMinusDestinationAlpha);
        BLEND_FACTOR_CASE(BlendFactorSrcAlphaSaturate, SourceAlphaSaturated);
        BLEND_FACTOR_CASE(BlendFactorConstantColor, BlendColor);
        BLEND_FACTOR_CASE(BlendFactorOneMinusConstantColor, OneMinusBlendColor);
        BLEND_FACTOR_CASE(BlendFactorConstantAlpha, BlendAlpha);
        BLEND_FACTOR_CASE(BlendFactorOneMinusConstantAlpha, OneMinusBlendAlpha);
        BLEND_FACTOR_CASE(BlendFactorSrc1Color, Source1Color);
        BLEND_FACTOR_CASE(BlendFactorOneMinusSrc1Color, OneMinusSource1Color);
        BLEND_FACTOR_CASE(BlendFactorSrc1Alpha, Source1Alpha);
        BLEND_FACTOR_CASE(BlendFactorOneMinusSrc1Alpha, OneMinusSource1Alpha);
        default:
            CGDMtl::error("Metal do not support the blend factor!");
        }
    }

    inline mtlpp::BlendOperation Transfer(Sakura::Graphics::BlendOp op)
    {
        if(op > 4)
            CGDMtl::error("Metal do not support the blend operation!");
        return (mtlpp::BlendOperation)op;
    }

    inline mtlpp::LoadAction Transfer(Sakura::Graphics::AttachmentLoadOp loadOp)
    {
        switch (loadOp)
        {
        case AttachmentLoadOpLoad:
            return mtlpp::LoadAction::Load;
        case AttachmentLoadOpClear:
            return mtlpp::LoadAction::Clear;
        case AttachmentLoadOpDontCare:
            return mtlpp::LoadAction::DontCare;
        default:
            CGDMtl::error("Metal do not support the load operation!");
            break;
        }
    }

    inline mtlpp::StoreAction Transfer(Sakura::Graphics::AttachmentStoreOp storeOp)
    {
        switch (storeOp)
        {
        case AttachmentStoreOpDontCare:
            return mtlpp::StoreAction::DontCare;
        case AttachmentStoreOpStore:
            return mtlpp::StoreAction::Store;
        default:
            CGDMtl::error("Metal do not support the load operation!");
            break;
        }
    }
}