shared_module("EditorModule")
    add_files("EditorModule.cpp")
    add_deps("SPA", "ImGuiProfiler", "CGD", "EngineUtils")
    add_packages("vcpkg::glm", "vcpkg::SDL2")

target("Editor")
    set_kind("binary")
    add_files("Execute/Win32Execute.cpp")
    add_deps("SPA", "CoreModule", "EditorModule")