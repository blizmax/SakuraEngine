includes("ImGui")

target("ImGuiProfiler")
    set_kind("static")
    add_packages("SImGui")
    add_includedirs("ImGui")
    add_files("ImGuiVulkanSDL.cpp")