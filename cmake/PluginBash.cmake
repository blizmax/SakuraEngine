function(engine_plugin_bash arg)
    execute_process(COMMAND lua BuildTools/ModuleInfoGen.lua meta ${ARGV0} ./SakuraEngine
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endfunction()

function(reflection_target arg)
get_target_property(TargetIncludes ${ARGV0} INCLUDE_DIRECTORIES)
    #message(STATUS "DIR: ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")
    foreach(dir ${TargetIncludes})
        #message(STATUS "DIR: ${dir}")
    endforeach()
    execute_process(COMMAND BuildTools/SReflCodeGen 
    
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endfunction()