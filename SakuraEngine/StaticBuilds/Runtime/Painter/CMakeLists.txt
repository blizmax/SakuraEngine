

project(Painter 
VERSION ${EngineVersion}
LANGUAGES CXX
)

set(SAKURA_SUPPORT_SDL2 TRUE)

# Add Metal Support
if(APPLE)
add_subdirectory(Source/PainterMetal)
set(BackeEndAPIs ${BackeEndAPIs} PainterMetal)
endif()
include_directories(Include/)

# Check SDL2 support and link
set(PainterSouce 
Source/Painter.cpp 
Include/Painter.h
)
if(SAKURA_SUPPORT_SDL2)
if(APPLE)
set(PainterSouce 
${PainterSouce}
Source/SDLSupport.mm
)
endif(APPLE)
endif()

add_library(Painter STATIC 
${PainterSouce}
)
target_link_libraries(Painter ${BackeEndAPIs})


# add ShaderTranslator API
add_library(ShaderTranslator SHARED 
Source/ShaderTranslator.cpp
Include/ShaderTranslator/ShaderTranslator.h
)
#find libdxcompiler
find_library(libdxcompiler 
dxcompiler 
${ENGINE_TOOLS_DIR}/DirectXShaderCompiler/)
#link dxcompiler
target_link_libraries(ShaderTranslator PUBLIC
CoreModule
${libdxcompiler})

#spirv
set(libspirv_cross 
spirv-cross-c 
spirv-cross-core
spirv-cross-cpp
spirv-cross-glsl
spirv-cross-hlsl
spirv-cross-msl
spirv-cross-reflect
spirv-cross-util)
message(STATUS ${libspirv_cross})
#link
target_link_libraries(ShaderTranslator PUBLIC ${libspirv_cross})
