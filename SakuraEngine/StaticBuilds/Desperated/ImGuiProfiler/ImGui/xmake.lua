target("SImGui")
    set_kind("static")
    add_packages("vcpkg::SDL2", "vcpkg::freetype")
    add_files("SImGuiAll.cpp")