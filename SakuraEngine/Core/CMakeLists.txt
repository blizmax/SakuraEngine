add_subdirectory(EngineUtils)

add_library(Core Core.cpp Core.h)
add_library(CoreModule SHARED CoreModule.cpp)
target_link_libraries(Core PUBLIC EngineUtils fmt::fmt SImGui)
target_link_libraries(CoreModule Core)

engine_plugin_bash(${CMAKE_CURRENT_SOURCE_DIR})
reflection_target(Core)