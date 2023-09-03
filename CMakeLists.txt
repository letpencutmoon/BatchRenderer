cmake_minimum_required(VERSION 3.2)

project(BatchRenderer)

set(CMAKE_CXX_STANDARD 17)
include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_library(BatchRenderer BatchRenderer.cpp)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

target_link_libraries(BatchRenderer PUBLIC glfw)
target_link_libraries(BatchRenderer PUBLIC ${OPENGL_LIBRARIES} GLEW::GLEW)

target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src/vender")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src/vender/stb_image")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/tests")

target_sources(BatchRenderer PUBLIC ${SRC_FILES} ${TESTS_FILES})

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
