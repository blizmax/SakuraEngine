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
 * @Date: 2020-05-02 18:09:18
 * @LastEditTime: 2020-05-06 22:02:06
 */
#include "GraphicsPipelineMtl.h"
#include "../ResourceObjects/ShaderMtl.h"
#include "RenderPassMtl.h"
#include "../CGDMetal.hpp"
#include "../Flags/FormatMtl.hpp"

using namespace Sakura::Graphics::Mtl;

GraphicsPipelineMtl::GraphicsPipelineMtl(const GraphicsPipelineCreateInfo& info,
    const RenderPassMtl& prog, const CGDMtl& _cgd)
    :cgd(_cgd), pass(prog)
{
    mtlpp::RenderPipelineDescriptor renderPipelineDesc;
    for(auto i = 0u; i < info.shaderStages.size(); i++)
    {   
        ShaderMtl* shaderMtl = (ShaderMtl*)info.shaderStages[i].GetShader();
        mtlpp::Function function 
            = shaderMtl->shaderFunctions[info.shaderStages[i].GetEntry()];
        switch (info.shaderStages[i].GetStage())
        {
        case ShaderStageFlags::VertexStage:
            renderPipelineDesc.SetVertexFunction(function);
            break;
        case ShaderStageFlags::PixelStage:
            renderPipelineDesc.SetFragmentFunction(function);
            break;
        default:
            CGDMtl::error("CGDMtl: Shader stage not supported in metal!");
            break;
        }
    }
    for(std::size_t i = 0u; i < prog.rpassCreateInfo.colorAttachments.size(); i++)
    {
        std::size_t index = prog.rpassCreateInfo.colorAttachments[i].attachment;
        auto&& attachment = prog.rpassCreateInfo.attachments[index];
        renderPipelineDesc.GetColorAttachments()[i].SetPixelFormat(
            Transfer(attachment.format));
        // Enable color blending
        auto&& attachInfo = info.colorBlendStateCreateInfo.colorBlendAttachment[i];
        renderPipelineDesc.GetColorAttachments(
            )[i].SetBlendingEnabled(attachInfo.blendEnable);
        renderPipelineDesc.GetColorAttachments()[i].SetDestinationRgbBlendFactor(
            Transfer(attachInfo.dstColorBlendFactor));
        renderPipelineDesc.GetColorAttachments()[i].SetSourceRgbBlendFactor(
            Transfer(attachInfo.srcColorBlendFactor));
        renderPipelineDesc.GetColorAttachments()[i].SetSourceAlphaBlendFactor(
            Transfer(attachInfo.srcAlphaBlendFactor));
        renderPipelineDesc.GetColorAttachments()[i].SetDestinationAlphaBlendFactor(
            Transfer(attachInfo.dstAlphaBlendFactor));
        mtlpp::ColorWriteMask mask = 0;
        for(size_t bit = 0; bit < 4; bit++)
        {
            int val = attachInfo.colorWriteMask >> bit;
            val = val & 1;
            val = val << (3 - bit);
            mask = mask | val;
        }
        renderPipelineDesc.GetColorAttachments()[i].SetWriteMask(mask);
        renderPipelineDesc.GetColorAttachments()[i].SetAlphaBlendOperation(
            Transfer(attachInfo.alphaBlendOp));
        renderPipelineDesc.GetColorAttachments()[i].SetRgbBlendOperation(
            Transfer(attachInfo.colorBlendOp));

        // Attachment Operations
        prog.renderPassDesc.GetColorAttachments()[i].SetLoadAction(
            Transfer(attachment.loadOp));
        prog.renderPassDesc.GetColorAttachments()[i].SetStoreAction(
            Transfer(attachment.storeOp));
    }
    renderPipelineState
        = cgd.entity.device.NewRenderPipelineState(renderPipelineDesc, nullptr);
}

GraphicsPipelineMtl::~GraphicsPipelineMtl()
{
    
}