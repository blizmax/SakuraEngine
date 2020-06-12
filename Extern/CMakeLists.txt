add_subdirectory(include)
add_subdirectory(mimalloc)
add_subdirectory(crossguid)

target_compile_options(crossguid PRIVATE "-Wno-unused-function")