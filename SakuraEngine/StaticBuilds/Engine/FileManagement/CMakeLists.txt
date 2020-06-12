add_library(FileManagement 
src/FileMetaGenerator.cpp
src/FileMetaManager.cpp

)

target_link_libraries(
    FileManagement
    CoreModule yaml-cpp)