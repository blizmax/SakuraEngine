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
 * @Date: 2020-03-16 17:22:38
 * @LastEditTime: 2020-03-21 21:42:52
 */
#pragma once
#include "SakuraEngine/StaticBuilds/ImGuiProfiler/ImGui/imgui.h"
#include "SakuraEngine/StaticBuilds/ImGuiProfiler/ImGui/imgui_impl_sdl.h"
#include "SakuraEngine/StaticBuilds/ImGuiProfiler/ImGui/imgui_impl_vulkan.h"
#include "vulkan/vulkan.h"
#include <memory>
#include <map>
extern "C"
{
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_surface.h"
	#include "SDL2/SDL_vulkan.h"
	#undef main
}

namespace Sakura::Graphics
{
    struct SwapChain;
    struct ResourceView;
}

namespace Sakura::Graphics::Im::Vk
{
    struct VkDevicePack
    {
        VkInstance instance;
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        uint32_t graphicsQueueFamily;
        uint32_t minImageCount;
        VkQueue graphicsQueue;
        VkAllocationCallbacks* allocator;
        VkPipelineCache pipelineCache = VK_NULL_HANDLE;
    };
    [[nodiscard]] ImGui_ImplVulkanH_Window* CreateImGuiWindowVk(
        const VkDevicePack& devices, VkSurfaceKHR surface, int width, int height);
    
    void ImGuiRenderVk(const VkDevicePack& devices, ImGui_ImplVulkanH_Window* wd);

    void ImGuiPresentVk(const VkDevicePack& devices, ImGui_ImplVulkanH_Window* wd);

    void check_vk_result(VkResult err);

    VkRenderPass ImGuiCreateRenderPass(const VkDevicePack& devices, VkFormat fmt);
    std::map<const ResourceView*, VkFramebuffer>
        ImGuiCreateFrameBuffer(const VkDevicePack& devices,
        SwapChain* swapChain, VkRenderPass renderPass);
}