cmake_minimum_required(VERSION 3.10)

#features
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

#/home/saeruhikari/OpenLib/vcpkg/vcpkg install --triplet x64-linux eigen3 boost gtest spdlog glfw3 SDL2 fmt xxHash SDL2[vulkan]
set(VCPKG_PKGS SDL2 freetype 
tinyobjloader tinyobjloader[double]
fmt entt 
SDL2[vulkan] vulkan-memory-allocator)

set(SAKURA_UNITY_BUILD on)

if(WIN32)
execute_process(COMMAND 
$ENV{VCPKG_ROOT}/vcpkg install --triplet x64-windows ${VCPKG_PKGS})
elseif(UNIX)
  if(APPLE)
    #execute_process(COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-osx ${VCPKG_PKGS} --recurse)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES ANDROID)
  else(APPLE)
    execute_process(COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-linux ${VCPKG_PKGS})
  endif(APPLE)
endif(WIN32)

message(STATUS $ENV{VCPKG_ROOT})
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
message(STATUS "TOOL CHAIN: ${CMAKE_TOOLCHAIN_FILE}")

project(Sakura)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Engine/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Engine/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Engine/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Engine/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Engine/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Engine/bin)
set(ENGINE_DIR ${CMAKE_BINARY_DIR}/Engine) 
set(ENGINE_LIB_DIR ${CMAKE_BINARY_DIR}/Engine/lib) 
set(ENGINE_BINARY_DIR ${CMAKE_BINARY_DIR}/Engine/bin) 
set(ENGINE_TOOLS_DIR ${CMAKE_BINARY_DIR}/Engine/Tools) 
link_directories(${ENGINE_LIB_DIR})
link_directories(${ENGINE_BINARY_DIR})
link_directories(${ENGINE_TOOLS_DIR})


find_package(freetype CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
#find_package(glfw3 CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(EASTL CONFIG REQUIRED)
find_package(EABase CONFIG REQUIRED)
if(APPLE)
# Do not find VK if APPLE
else(APPLE)
find_package(Vulkan REQUIRED VERSION 1.2.131.2) 
if(Vulkan_FOUND)
include_directories(${Vulkan_INCLUDE_DIRS})
endif()
endif(APPLE)

set(CMAKE_DEBUG_POSTFIX d)

if(MSVC)     
    foreach(var 
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
      )
      if(${var} MATCHES "/MT")
        string(REGEX REPLACE "/MT" "/MD" ${var} "${${var}}")
      endif()
    endforeach()    
endif(MSVC)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
add_definitions(-D_DEBUG)
endif ()

if(MSVC)
    #add_definitions(-D "SAKURA_COMPILER_MSVC")
    message(STATUS "MSVC Compiler cl.exe")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /await /D _CRT_SECURE_NO_WARNINGS -DNOMINMAX") #Multi Thread Build Enable
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    #add_definitions(-D "SAKURA_COMPILER_CLANG")
    message(STATUS "Use CLANG Compiler Clang")
    add_definitions(-msse4.2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -std=c++20 -stdlib=libc++ -m64 -fPIC -march=native -O3 -pthread ${VAR_CONFIG_FLAGS}")
else()
    #add_definitions(-D "SAKURA_COMPILER_GCC")
    message(STATUS "Use GCC Compiler gcc")
    add_definitions(-msse4.2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -m64 -fPIC -march=native -O3 -pthread -lpthread ${VAR_CONFIG_FLAGS}")
    message(STATUS "${VAR_CONFIG_FLAGS}")
endif(MSVC)

ADD_DEFINITIONS(-DMACRO)
if(UNIX)
    add_definitions(-D "SAKURA_TARGET_PLATFORM_UNIX")
    if(APPLE)
        add_definitions(-D "SAKURA_TARGET_PLATFORM_OSX")
        set(OS_MACOS 1)
    elseif(${CMAKE_SYSTEM_NAME}  MATCHES ANDROID)
        add_definitions(-D "SAKURA_TARGET_PLATFORM_ANDROID")
        set(OS_ANDROID 1)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES Emscripten)
        add_definitions(-D "SAKURA_TARGET_PLATFORM_EMSCRIPTEN")
        set(WA 1)   #Web
        set(OS_WEBASSEMBLY 1)
    else(APPLE)
        add_definitions(-D "SAKURA_TARGET_PLATFORM_LINUX")
        set(OS_LINUX 1)
    endif(APPLE)
elseif(WIN32)
    add_definitions(-D "SAKURA_TARGET_PLATFORM_WIN")
    message(STATUS "Platform WIN32")
    set(OS_WINDOWS 1)
endif(UNIX)

include(cmake/PluginBash.cmake)

include_directories(Extern/include/)
include_directories(Extern/include/DirectXMath/Inc/)
include_directories(Extern/mimalloc/include/)


add_subdirectory(Extern)
add_subdirectory(SPA)
add_subdirectory(SakuraEngine)



