cmake_minimum_required(VERSION 3.11)

project(Sakura VERSION 0.1.0)
#execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/SPA/anyToheader.py meta .json ${CMAKE_SOURCE_DIR}/SakuraEngine 
#WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/SPA)
#execute_process(COMMAND python3 ${CMAKE_SOURCE_DIR}/SPA/ModuleCollector.py meta  ${CMAKE_SOURCE_DIR}/SakuraEngine 
#WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/SPA)

add_definitions(-D "SAKURA_CONSOLE_INOUT")
add_definitions(-D "SAKURA_DEBUG_EDITOR")
add_definitions(-D "SAKURA_DEBUG_GAME")


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}
)
include_directories(
    ../Extern/include
)
include_directories(
    ../
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_subdirectory(Core)
add_subdirectory(StaticBuilds)
add_subdirectory(Modules)
add_subdirectory(Editor)
#add_subdirectory(Framework)

include(CPack)