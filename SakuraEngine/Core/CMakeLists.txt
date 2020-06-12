add_library(CoreModule SHARED CoreModule.cpp Core.cpp Core.h EngineUtils/EngineUtil_All.cpp)
target_link_libraries(CoreModule 
    PUBLIC 
    fmt::fmt EASTL EABase crossguid)

engine_plugin_bash(${CMAKE_CURRENT_SOURCE_DIR})
reflection_target(CoreModule)
