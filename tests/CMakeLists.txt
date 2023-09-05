macro(add_executable_test target path)
    add_executable(${target} ${path} ${ARGN})
    add_test(NAME ${target} COMMAND ${target})
endmacro()

# only useful in same dir level
function(add_executable_test_by_filename filename)
    get_filename_component(target ${filename} NAME_WLE)
    set(result ${target} PARENT_SCOPE)
    add_executable_test(${target} ${filename} ${ARGN})
endfunction()

file(GLOB TEST_FILES
        "${PROJECT_SOURCE_DIR}/tests/*_test.cpp"
        )

file(GLOB_RECURSE TESTS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


foreach (test_file ${TEST_FILES})
        add_executable_test_by_filename(${test_file})
        target_link_libraries(${result} PRIVATE BatchRenderer)
        target_sources(${result} PRIVATE ${TESTS_FILES})
endforeach ()