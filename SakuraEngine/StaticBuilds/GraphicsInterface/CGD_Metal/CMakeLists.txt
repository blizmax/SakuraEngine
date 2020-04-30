set(PLATFORM_SOURCES
    CGDMetal.hpp
    CGDMetal.cpp
    CommandObjects/CommandBufferMtl.h
    CommandObjects/CommandBufferMtl.cpp
    CommandObjects/CommandQueueMtl.h
    CommandObjects/CommandQueueMtl.cpp
    ResourceObjects/ShaderMtl.h
    ResourceObjects/ShaderMtl.cpp
    mtlpp/mtlpp.hpp
    mtlpp/mtlpp.mm
)

set(PLATFORM_LIBRARIES
    "-framework Metal"
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