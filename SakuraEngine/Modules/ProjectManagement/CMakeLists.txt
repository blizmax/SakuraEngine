add_library(ProjectManagement 
SHARED
src/ProjectManager.cpp
)

target_link_libraries(ProjectManagement CoreModule FileManagement)