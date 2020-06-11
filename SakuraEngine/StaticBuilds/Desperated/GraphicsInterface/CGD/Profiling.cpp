/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-11 00:02:45
 * @LastEditors  : SaeruHikari
 * @LastEditTime : 2020-02-11 10:20:25
 */
#include "../GraphicsCommon/CommandObjects/Profiling.h"
#include "../GraphicsCommon/CommandObjects/CommandBuffer.h"
#include "Core/EngineUtils/ConsoleDesk.h"

namespace Sakura::Graphics
{
    void Profiling::BeginBlock(const sstring& ID,
        const CommandBuffer& context)
    {
        #ifdef SAKURA_GRAPHICS_PROFILING
        {
        
        };
        #else
        {};
        #endif
    }

    void Profiling::EndBlock(const sstring& ID,
        const CommandBuffer& context)
    {
        #ifdef SAKURA_GRAPHICS_PROFILING
        {
        
        };
        #else
        {};
        #endif
    }
}
