add_library(Core STATIC Core.cpp Core.h EngineUtils/EngineUtil_All.cpp)
add_library(CoreModule SHARED CoreModule.cpp)
target_link_libraries(Core PUBLIC fmt::fmt EASTL EABase)
target_link_libraries(CoreModule Core)

engine_plugin_bash(${CMAKE_CURRENT_SOURCE_DIR})
reflection_target(Core)