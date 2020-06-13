add_library(FileManagement 
SHARED
src/FileMetaGenerator.cpp
src/FileMetaManager.cpp
src/VirtualFileSystem.cpp
)

target_link_libraries(
    FileManagement
    CoreModule yaml-cpp
)