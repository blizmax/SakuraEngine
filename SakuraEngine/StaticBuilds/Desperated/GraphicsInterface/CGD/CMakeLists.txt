include_directories( ${PROJECT_SOURCE_DIR}/Graphicsinterface/CGD_Direct3D12)
include_directories( ${PROJECT_SOURCE_DIR}/Graphicsinterface/Vulkan)
include_directories( ${PROJECT_SOURCE_DIR}/Graphicsinterface/GraphicsCommon)

add_library(CGD 
CGD.cpp 
../GraphicsCommon/CGD.h)

if(APPLE)
target_link_libraries(CGD CGD_Vulkan CGDMetal)
else()
target_link_libraries(CGD CGD_Vulkan)
endif()

