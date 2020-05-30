

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