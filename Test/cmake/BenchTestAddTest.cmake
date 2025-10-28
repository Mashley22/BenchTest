include_guard(GLOBAL)

set(THIS_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

function(benchtest_add_test target_name sources)
    list(REMOVE_AT sources 0)

    list(APPEND sources ${THIS_DIR}/../src/main.cpp)

    add_executable(${target_name} ${sources})

    set_target_properties(${target_name} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/)

    get_target_property(output_location ${target_name} RUNTIME_OUTPUT_DIRECTORY)

    target_link_libraries(${target_name}
      PUBLIC
        BenchTest_Test)

    if(NOT output_location)
        set(output_location "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    endif()

    if(NOT output_location)
        set(output_location "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    set(target_path "${output_location}/${target_name}${CMAKE_EXECUTABLE_SUFFIX}")
    add_test(${target_name} ${target_path} ${ARGN})
endfunction()
