#Core Dispatcher of the Engine
add_library(EditorModule SHARED EditorModule.cpp)

target_link_libraries(EditorModule 
SPA Painter SDL2::SDL2 CoreModule ShaderTranslator)

add_executable(Editor Execute/Execute.cpp)

target_link_libraries(Editor SPA CoreModule)

engine_plugin_bash(${CMAKE_CURRENT_SOURCE_DIR})
reflection_target(EditorModule)
