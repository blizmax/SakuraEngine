file (
    GLOB_RECURSE
    mtlppSrc
    mtlpp/*.cpp
    mtlpp/*.h
    mtlpp/*.hpp
    mtlpp/*.mm
    *.mm
    *.h
    *.cpp
    *.hpp
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
set_source_files_properties(
    ${PLATFORM_SOURCES}
    PROPERTIES
    COMPILE_FLAGS -fobjc-weak
)

include_directories(../../Include/)

add_library(PainterMetal STATIC 
${mtlppSrc}
)

target_link_libraries(PainterMetal Core ${PLATFORM_LIBRARIES})