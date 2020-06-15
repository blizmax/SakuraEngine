add_library(FileManagement 
SHARED
src/FileMetaGenerator.cpp
src/FileMetaManager.cpp
src/VirtualFileSystem.cpp
src/VirtualFileSystemLocal.cpp
)

target_link_libraries(
    FileManagement
    CoreModule yaml-cpp
)

set(FileManagementBuildTest ON)
if(FileManagementBuildTest)
    add_executable(FileManagementTest test/FileManagementTest.cpp)
    target_link_libraries(FileManagementTest FileManagement)
endif()