/*
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-02-11 00:41:20
 * @LastEditors  : SaeruHikari
 * @LastEditTime : 2020-02-12 12:31:10
 */
#pragma once
#include "Core/CoreMinimal/sinterface.h"
#include "Core/CoreMinimal/SDefination.h"

namespace Sakura::Graphics
{
    sinterface CommandBuffer;
}    

namespace Sakura::Graphics::GpuTimeManager
{
    void Initialize(uint32 MaxNumTimers = 4096);
    void Shutdown();

    // Reserve a unique timer index
    uint32 NewTimer(void);

    /**
     * @description: Start a gpu timer with timer index 
     * @param {CommandBuffer& context, uint32 timerIdx} 
     * @return: void
     * @author: SaeruHikari
     */
    void StartTimer(CommandBuffer& context, uint32 timerIdx);
    /**
     * @description: Stop a gpu timer with timer index 
     * @param {CommandBuffer& context, uint32 timerIdx} 
     * @return: void
     * @author: SaeruHikari
     */
    void StopTimer(CommandBuffer& context, uint32 timerIdx);

    /**
     * @description: Bookend all calls to GetTime() with
     * Begin/End which correspond to Map/Unmap.  
     * This needs to happen either at the very start or very end of a frame.
     * @param {void} 
     * @return: void
     * @author: SaeruHikari
     */
    void BeginReadBack(void);

    /**
     * @description: Bookend all calls to GetTime() with
     * Begin/End which correspond to Map/Unmap.  
     * This needs to happen either at the very start or very end of a frame.
     * @param {void} 
     * @return: void
     * @author: SaeruHikari
     */
    void EndReadBack(void);

    // Returns the time in milliseconds between start and stop queries
    float GetTime(uint32 timerIndex);
}