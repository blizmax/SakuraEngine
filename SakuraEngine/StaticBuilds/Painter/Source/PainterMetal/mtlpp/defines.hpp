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
 * @Date: 2020-05-27 01:40:41
 * @LastEditTime: 2020-06-04 13:51:06
 */ 
/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */

#pragma once

#include <stdint.h>
#include <assert.h>
#include <functional>

#ifndef __has_feature
#   define __has_feature(x) 0
#endif

#ifndef MTLPP_CONFIG_RVALUE_REFERENCES
#   define MTLPP_CONFIG_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#endif

#ifndef MTLPP_CONFIG_VALIDATE
#   define MTLPP_CONFIG_VALIDATE 1
#endif

#ifndef MTLPP_CONFIG_USE_AVAILABILITY
#   define MTLPP_CONFIG_USE_AVAILABILITY 0
#endif

#if MTLPP_CONFIG_USE_AVAILABILITY
#   if __has_feature(attribute_availability_with_version_underscores) || (__has_feature(attribute_availability_with_message) && __clang__ && __clang_major__ >= 7)
#       include <CoreFoundation/CFAvailability.h>
#       define MTLPP_AVAILABLE(mac, ios)                            CF_AVAILABLE(mac, ios)
#       define MTLPP_AVAILABLE_MAC(mac)                             CF_AVAILABLE_MAC(mac)
#       define MTLPP_AVAILABLE_IOS(ios)                             CF_AVAILABLE_IOS(ios)
#       define MTLPP_AVAILABLE_TVOS(tvos)
#       define MTLPP_DEPRECATED(macIntro, macDep, iosIntro, iosDep) CF_DEPRECATED(macIntro, macDep, iosIntro, iosDep)
#       define MTLPP_DEPRECATED_MAC(macIntro, macDep)               CF_DEPRECATED_MAC(macIntro, macDep)
#       define MTLPP_DEPRECATED_IOS(iosIntro, iosDep)               CF_DEPRECATED_IOS(iosIntro, iosDep)
#   endif
#endif

#ifndef MTLPP_AVAILABLE
#   define MTLPP_AVAILABLE(mac, ios)
#   define MTLPP_AVAILABLE_MAC(mac)
#   define MTLPP_AVAILABLE_IOS(ios)
#   define MTLPP_AVAILABLE_TVOS(tvos)
#   define MTLPP_DEPRECATED(macIntro, macDep, iosIntro, iosDep)
#   define MTLPP_DEPRECATED_MAC(macIntro, macDep)
#   define MTLPP_DEPRECATED_IOS(iosIntro, iosDep)
#endif

#ifndef __DARWIN_ALIAS_STARTING_MAC___MAC_10_11
#   define __DARWIN_ALIAS_STARTING_MAC___MAC_10_11(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_MAC___MAC_10_12
#   define __DARWIN_ALIAS_STARTING_MAC___MAC_10_12(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_8_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_8_0(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_9_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_9_0(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_0
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_0(x)
#endif
#ifndef __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_3
#   define __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_10_3(x)
#endif

#define MTLPP_IS_AVAILABLE_MAC(mac)  (0 __DARWIN_ALIAS_STARTING_MAC___MAC_##mac( || 1 ))
#define MTLPP_IS_AVAILABLE_IOS(ios)  (0 __DARWIN_ALIAS_STARTING_IPHONE___IPHONE_##ios( || 1 ))
#define MTLPP_IS_AVAILABLE(mac, ios) (MTLPP_IS_AVAILABLE_MAC(mac) || MTLPP_IS_AVAILABLE_IOS(ios))

