/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-05 23:50:30
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-04-30 23:34:59
 */
#pragma once
#include <mutex>
#include <vector>
#include <memory>
#include <queue>
#include "Core/Containers/SString.h"
#include "Core/CoreMinimal/sinterface.h"
#include "Core/CoreMinimal/SDefination.h"
#include "Core/CoreMinimal/SAssert.h"
#include "../GraphicsObjects/RenderPass.h"
#include "../ResourceObjects/ResourceViews.h"

namespace Sakura::Graphics
{
    sinterface CommandQueue;
    sinterface CommandBuffer;
    sinterface GraphicsPipeline;
    sinterface ComputePipeline;
    sinterface GpuTexture;
    sinterface GpuResource;
    sinterface RootArgument;
    sinterface GpuBuffer;
	struct RenderTargetSet;
    struct BufferImageCopy;
}

namespace Sakura::Graphics
{
    using ImageAspectFlags = std::uint32_t;
    enum ECommandType   
    {
        ECommandBufferGraphics = 1,
        ECommandBufferCompute = 2,
        ECommandBufferCopy = 4,
        ECommandBufferIndirect = 8,
        ECommandBufferCount = 4
    };

    sinterface CommandBuffer
    {
        friend sinterface CGD;
    public:
        virtual ~CommandBuffer() = default;

        /**
         * @description: Resets the encoding, close the cmdlist/buffer
         * @author: SaeruHikari
         */
        virtual void Reset() = 0;

        virtual void ResourceBarrier(GpuTexture& toTransition,
            const ImageLayout oldLayout, const ImageLayout newLayout,
            const TextureSubresourceRange& = plainTextureSubresourceRange) = 0;

        virtual ECommandType GetCommandBufferType(void) = 0;
        bool bOpen = false;
    protected:
        sstring m_ID;
    };

    sinterface CommandBufferGraphics : simplements CommandBuffer
    {
        /**
         * @description: Ends the render pass
         * @author: SaeruHikari
         */
        virtual void EndRenderPass() = 0;
        
        /**
         * @description: Begins a render pass
         * @author: SaeruHikari
        */
	    virtual void BeginRenderPass(
		    GraphicsPipeline* gp, const RenderTargetSet& rts) = 0;

		virtual void Draw(uint32 vertexCount, uint32 instanceCount,
			uint32 firstVertex, uint32 firstInstance) = 0;

		virtual void DrawIndexed(const uint32_t indicesCount,
			const uint32_t instanceCount) = 0;

		virtual void BindVertexBuffer(const GpuBuffer& vb) = 0;

		virtual void BindIndexBuffer(const GpuBuffer& ib,
			const IndexBufferStride stride = IndexBufferStride::IndexBufferUINT32) = 0;

		virtual void BindRootArguments(const PipelineBindPoint bindPoint,
			const RootArgument** arguments, uint32_t argumentNum) = 0;

        virtual ECommandType GetCommandBufferType(void) final override
        {
            return ECommandType::ECommandBufferGraphics;
        }
    };

    sinterface CommandBufferCompute : simplements CommandBuffer
    {
        /**
         * @description: Ends the encoding, close the cmdlist/buffer
         * @author: SaeruHikari
         */
        virtual void End() = 0;

        /**
         * @description: Begins the encoding, open the cmdlist/buffer
         * @author: SaeruHikari
         */
        virtual void Begin() = 0;

		virtual void BeginComputePass(ComputePipeline* gp) = 0;
        
	    virtual void BindRootArguments(const PipelineBindPoint bindPoint,
		    const RootArgument** arguments, uint32_t argumentNum) = 0;

		virtual void DispatchCompute(uint32 groupCountX,
			uint32 groupCountY, uint32 groupCountZ) = 0;

		virtual void GenerateMipmaps(GpuTexture& texture, Format format,
			uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels) = 0;

		virtual ECommandType GetCommandBufferType(void) final override
		{
			return ECommandType::ECommandBufferCompute;
		}
    };

    sinterface CommandBufferCopy : simplements CommandBuffer
    {
        /**
         * @description: Ends the encoding, close the cmdlist/buffer
         * @author: SaeruHikari
         */
        virtual void End() = 0;

        /**
         * @description: Begins the encoding, open the cmdlist/buffer
         * @author: SaeruHikari
         */
        virtual void Begin() = 0;

		virtual void CopyResource(GpuBuffer& src, GpuBuffer& dst,
			const uint64_t srcOffset = 0,
			const uint64_t dstOffset = 0, const uint64_t size = 0) = 0;

		virtual void CopyResource(GpuBuffer& src, GpuTexture& dst,
			const uint32_t imageWidth, const uint32_t imageHeight,
			const ImageAspectFlags aspectFlags, const uint64_t srcOffset = 0) = 0;

		virtual void CopyResource(GpuBuffer& src, GpuTexture& dst,
			const BufferImageCopy& info) = 0;

		virtual void GenerateMipmaps(GpuTexture& texture, Format format,
			uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels) = 0;

		virtual ECommandType GetCommandBufferType(void) final override
		{
			return ECommandType::ECommandBufferCopy;
		}
    };
}