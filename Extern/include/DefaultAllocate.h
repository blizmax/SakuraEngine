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
 * @Date: 2020-06-08 22:26:33
 * @LastEditTime: 2020-06-12 14:21:08
 */ 
#pragma once
// SakuraEngine intends to support more malloc mesures
// and switch freely on runtime.
//
// But now I find too few proper libs for game dev.
// 1. mimalloc (perform extremely well on windows).
// 2. tbb-malloc (with a full thread-building-block support,
// but far too slow when allocating for big blocks).
// 3. jemalloc & tcmalloc (popular solution)
// 4. dlmalloc (single-thread)
// 
// So after prifiling I decided to malloc in statically-specified mesure.
#ifdef SAKURA_TARGET_PLATFORM_WIN
// on windows we use mimalloc.
#include <mimalloc.h>
#include <mimalloc-ovrride.h>
#include <mimalloc-new-delete.h>
#elif defined(SAKURA_TARGET_PLATFORM_OSX)
// on osx we use system default mesure.
#else
// linux and other platforms have no spec-support now.
#endif

inline void* operator new[](size_t size, const char* pName, int flags,
        unsigned debugFlags, const char* file, int line)
{
    (void)file;
    (void)line;
    (void)pName;
    (void)flags;
    (void)debugFlags;
    // Currently we use simple malloc for EASTL-containters' alloc
    // Mem-Pooling is a good optimize because games use single-context normally.
    return malloc(size);
}  

inline void* operator new[](size_t size, size_t alignment,
        size_t alignmentOffset, const char* pName, int flags,
        unsigned debugFlags, const char* file, int line)
{
    (void)file;
    (void)line;
    (void)alignment;
    (void)alignmentOffset;
    (void)pName;
    (void)flags;
    (void)debugFlags;
    // Currently we use simple malloc for EASTL-containters' alloc
    // Mem-Pooling is a good optimize because games use single-context normally.
    return malloc(size);
}