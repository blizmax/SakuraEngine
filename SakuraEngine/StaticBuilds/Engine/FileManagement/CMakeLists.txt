add_library(FileManagement 
src/FileMetaGenerator.cpp

)

target_link_libraries(
    FileManagement
    CoreModule yaml-cpp)