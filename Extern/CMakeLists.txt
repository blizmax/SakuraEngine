add_subdirectory(include)
set(MI_BUILD_TESTS OFF)
set(CROSSGUID_TESTS OFF)
add_subdirectory(mimalloc)
add_subdirectory(crossguid)

target_compile_options(crossguid PRIVATE "-Wno-unused-function")