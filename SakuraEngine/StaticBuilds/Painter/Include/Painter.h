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
 * @Date: 2020-05-27 12:35:56
 * @LastEditTime: 2020-06-01 01:03:04
 */ 
#pragma once
#include "Extension.h"
#include "Shader.h"
#include "GPUResource.h"
#include "RenderPipeline.h"

namespace Sakura::Graphics
{
    struct Fence;
    struct RenderPass;
    struct RenderPassDesc;
    struct RenderCommandBuffer;
    struct SwapChain;
}

namespace Sakura::Graphics
{
    struct Painter 
    {
    public:
        // Interfaces

        /**
         * @description: Create a fence.
         * @return: Fence created.
         * @author: SaeruHikari
         */
        [[nodiscard]] virtual Fence* CreateFence() = 0;

        /**
         * @description: To Begin a RenderTask, Render Pass is necessary.
         * Returns a pointer of created renderpass, which needs to be managed by users.
         * @param {const RenderPassDesc&} Description of a render pass.
         * @return: Render Pass pointer
         * @author: SaeruHikari
         */    
        [[nodiscard]] virtual RenderPass* CreateRenderPass(
            const RenderPassDesc& desc) = 0;

        /**
         * @description: Create a shader with source code.
         * @param {const char*} source code or binary code of shader.
         * @param {std::size_t} dataSize shader code.
         * @return: Shader pointer
         * @author: SaeruHikari
         */   
        [[nodiscard]] virtual Shader* CreateShader(
            const char* data, const std::size_t dataSize,
            const Shader::MacroTable& macroTable = _Shader::nullTable) = 0;

        /**
         * @description: 
         * @param {const GPUResource::ResourceOptions} CPU Access(or optiions) of this buffer
         * @param {std::uint32_t} length of the buffer.
         * @param {const void*} pointer of init data.
         * @return: Pointer of resource created.
         * @author: SaeruHikari
         */
        [[nodiscard]] virtual GPUBuffer* CreateBuffer(
            const GPUBuffer::BufferUsage usage, 
            const GPUResource::ResourceOptions options, 
            std::uint32_t length, const void* pointer) = 0;

        /**
         * @description: Create a command buffer that is used to encode render commands.
         * @return: Render Command Buffer Pointer.
         * @author: SaeruHikari
         */
        [[nodiscard]] virtual RenderCommandBuffer* CreateRenderCommandBuffer() = 0;


        /**
         * @description: Create a render pipeline state.
         * @return: PSO Object Pointer.
         * @author: SaeruHikari
         */
        [[nodiscard]] virtual RenderPipeline* CreateRenderPipeline(const RenderPipelineDescripor desc) = 0;

        /**
         * @description: Returns the backend name of this painter.
         * @return: BackEnd Name
         * @author: SaeruHikari
         */
        virtual const eastl::string_view GetBackEndName() const = 0;

    public:
        template<typename PainterClass, typename... Args>
        [[nodiscard]] static PainterClass* Create(Args... args)
        {
            return new PainterClass(eastl::move(args)...);
        }
    protected:
        Painter(bool bEnableDebugLayer)
        {
            
        }
        virtual ~Painter()
        {
            for(auto iter = extensionsData.begin(); iter != extensionsData.end(); iter++)
            {
                delete iter->second.ptr;
            }
        }
        // Check and Add Extensions
    public:
        template<typename ExtensionType, typename std::enable_if<
            !std::is_base_of<Extension, ExtensionType>::value 
        >::type * = nullptr>
        inline bool Support()
        {
            return false;
        }
        template<typename ExtensionType, typename std::enable_if<
            std::is_base_of<Extension, ExtensionType>::value 
        >::type * = nullptr>
        inline bool Support()
        {
            return std::decay_t<ExtensionType>::EnableIf(this);
        }
        using ExtensionsMap
            = eastl::unordered_map<eastl::string, eastl::unique_ptr<Extension>>;
        using ExtensionsDataMap 
            = eastl::unordered_map<eastl::string, Extension::DataSlot>;
        template<typename ExtensionType, typename... Args>
        inline ExtensionType* EnableExtension(Args... args)
        {
            if(!Support<ExtensionType>())
                return nullptr;
            if(extensions.find(std::decay_t<ExtensionType>::name) == extensions.end())
            {
                Extension::DataSlot dt;
                extensionsData[std::decay_t<ExtensionType>::name] = dt;
                extensions[std::decay_t<ExtensionType>::name] =
                    eastl::make_unique<std::decay_t<ExtensionType>>(eastl::move(args)...);
            }
            return static_cast<ExtensionType*>(
                    extensions[std::decay_t<ExtensionType>::name].get());
        }
        template<typename ExtensionType>
        inline ExtensionType* FindActivatedExtension()
        {
            if(Support<ExtensionType>() && 
               extensions.find(std::decay_t<ExtensionType>::name) != extensions.end())
            {
                return static_cast<ExtensionType*>(
                    extensions[std::decay_t<ExtensionType>::name].get());
            }
            return nullptr;
        }
        inline Extension* FindActivatedExtension(const eastl::string& name)
        {
            if(extensions.find(name) != extensions.end())
            {
                return extensions[name].get();
            }
            return nullptr;
        }
        template<typename ExtensionType>
        inline Extension::DataSlot& GetDataRef()
        {
            return extensionsData[std::decay_t<ExtensionType>::name];
        }
        ExtensionsMap extensions;
        ExtensionsDataMap extensionsData;
    };
}