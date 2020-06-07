#https://github.com/KhronosGroup/SPIRV-Cross
set(TARGET SPIRV-Cross)

include(${CMAKE_SOURCE_DIR}/cmake/SakuraModules.cmake)
include(ExternalProject)

get_platform_dir()

add_library(${TARGET} STATIC
    SPIRVCross.cpp
)

set(BINARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/binaries/${PLATFORM_DIR})

if(WIN32)
    get_target_arch(WIN_ARCH)
    set(BINARIES_DIR ${BINARIES_DIR}-${WIN_ARCH})
endif()

if(WIN32 OR APPLE)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${BINARIES_DIR}.zip
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
    file(GLOB_RECURSE SPIRV_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/binaries/bin/*)
    file(COPY ${SPIRV_FILES}
         DESTINATION ${ENGINE_TOOLS_DIR}/SPIRV-Cross/
         FOLLOW_SYMLINK_CHAIN)
endif()

