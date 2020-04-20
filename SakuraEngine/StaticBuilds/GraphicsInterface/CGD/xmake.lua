target("CGD")
    set_kind("static")
    add_deps("Core", "CGD_Vulkan")
    add_files("CGD.cpp")