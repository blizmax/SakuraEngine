#Core Dispatcher of the Engine
add_library(EditorModule SHARED EditorModule.cpp)

target_link_libraries(EditorModule SPA Painter SDL2::SDL2 Core)

add_executable(Editor Execute/Execute.cpp)

target_link_libraries(Editor SPA Core)

engine_plugin_bash(${CMAKE_CURRENT_SOURCE_DIR})
reflection_target(EditorModule)
