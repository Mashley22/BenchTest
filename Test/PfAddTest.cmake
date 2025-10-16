# Define a global property to hold all target paths
include_guard(GLOBAL)
define_property(GLOBAL PROPERTY PF_TEST_PATHS BRIEF_DOCS "Collected target output paths")

function(pf_add_test)
    # First argument is the target name
    set(target_name ${ARGV0})
    # Call the real add_executable
    add_executable(${ARGV})

    set_target_properties(${target_name} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/)
    # Get the output location of the executable
    get_target_property(output_location ${target_name} RUNTIME_OUTPUT_DIRECTORY)

    # If not set, use the default build dir (for RUNTIME output)
    if(NOT output_location)
        set(output_location "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    endif()

    if(NOT output_location)
        set(output_location "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    # Append the full path to the executable
    set(target_path "${output_location}/${target_name}${CMAKE_EXECUTABLE_SUFFIX}")
    get_property(existing_paths GLOBAL PROPERTY PF_TEST_PATHS)
    list(APPEND existing_paths "${target_path}")
    set_property(GLOBAL PROPERTY PF_TEST_PATHS "${existing_paths}")
endfunction()

# Function to write target paths to file after config
function(write_all_test_paths)
  get_property(all_paths GLOBAL PROPERTY PF_TEST_PATHS)
  set(output_file "${CMAKE_SOURCE_DIR}/PfTestLists.txt")

    file(WRITE "${output_file}" "")
    foreach(path IN LISTS all_paths)
        file(APPEND "${output_file}" "${path}\n")
    endforeach()

    message(STATUS "Wrote tests list to: ${output_file}")
endfunction()
