add_library(SImGui STATIC
SImGuiAll.cpp
)

target_link_libraries(SImGui PUBLIC freetype)