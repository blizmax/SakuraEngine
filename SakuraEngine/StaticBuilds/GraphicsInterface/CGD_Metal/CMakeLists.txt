set(PLATFORM_SOURCES
    CGDMetal.hh
    CGDMetal.mm
    CommandObjects/CommandContextMtl.hh
    CommandObjects/CommandContextMtl.mm
    
)

set(PLATFORM_LIBRARIES
    "-framework Metal"
)

# CLANG_ENABLE_OBJC_WEAK = YES
set_source_files_properties(
    ${PLATFORM_SOURCES}
    PROPERTIES
    COMPILE_FLAGS -fobjc-weak
)
set(SOURCES ${PLATFORM_SOURCES}

)

add_library(CGDMetal STATIC
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(CGDMetal Core)