target("CGD_Vulkan")
    set_kind("static")
    add_packages("Vulkan")
    add_deps("Core")
    add_files("CGDVk_All.cpp")