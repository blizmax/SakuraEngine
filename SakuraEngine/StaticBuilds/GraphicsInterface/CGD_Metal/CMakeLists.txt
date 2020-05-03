set(PLATFORM_SOURCES
    CGDMetal.hpp
    CGDMetal.cpp
    CGDMetal.mm
    AppleWindow.hpp
    AppleWindow.mm

    CommandObjects/CommandBufferMtl.h
    CommandObjects/CommandBufferMtl.cpp
    CommandObjects/CommandQueueMtl.h
    CommandObjects/CommandQueueMtl.cpp

    ResourceObjects/ShaderMtl.h
    ResourceObjects/ShaderMtl.cpp
    ResourceObjects/GpuResourceMtl.cpp
    ResourceObjects/GpuResourceMtl.h

    PipelineObjects/SwapChainMtl.hpp
    PipelineObjects/SwapChainMtl.mm
    PipelineObjects/GraphicsPipelineMtl.h
    PipelineObjects/GraphicsPipelineMtl.cpp
    PipelineObjects/RenderPassMtl.h
    PipelineObjects/RenderPassMtl.cpp

    mtlpp/mtlpp.hpp
    mtlpp/mtlpp.mm
)

set(PLATFORM_LIBRARIES
    "-framework Metal"
    "-framework Cocoa"
    "-framework MetalKit"
    "-framework CoreFoundation"
    "-fobjc-link-runtime"
)
set(CMAKE_C_FLAGS "-x objective-c")
set(CMAKE_CXX_FLAGS "-x objective-c++")

# CLANG_ENABLE_OBJC_WEAK = YES
set_source_files_properties(
    ${PLATFORM_SOURCES}
    PROPERTIES
    COMPILE_FLAGS -fobjc-weak
)
set(SOURCES ${PLATFORM_SOURCES}

)
set(LIBRARIES ${PLATFORM_LIBRARIES}
)

add_library(CGDMetal STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(CGDMetal Core ${PLATFORM_LIBRARIES})