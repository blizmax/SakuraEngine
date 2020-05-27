cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(Painter 
VERSION ${EngineVersion}
LANGUAGES CXX
)

if(APPLE)
add_subdirectory(Source/PainterMetal)
set(BackeEndAPIs ${BackeEndAPIs} PainterMetal)
endif()
include_directories(Include/)

add_library(Painter STATIC 
Source/Painter.cpp 
Include/Painter.h)

target_link_libraries(Painter ${BackeEndAPIs})