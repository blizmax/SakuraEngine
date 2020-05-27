#pragma once
#include "SakuraEngine/Core/Core.h"

namespace Sakura::Graphics
{
    struct Painter;
}

namespace Sakura::Graphics
{
    struct DefaultBackEndNames
    {
        static constexpr const eastl::string_view Metal = "Metal";
        static constexpr const eastl::string_view Direct3D12 = "Direct3D12";
        static constexpr const eastl::string_view Vulkan = "Vulkan";
    };

    struct Extension
    {
        static bool EnableIf(Painter* painter)
        {
            return false;
        }
        inline static constexpr std::string_view name = "Null";
    };
}