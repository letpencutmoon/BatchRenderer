cmake_minimum_required(VERSION 3.2)

project(BatchRenderer)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(BatchRenderer BatchRenderer.cpp)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

target_link_libraries(BatchRenderer PUBLIC glfw)
target_link_libraries(BatchRenderer PUBLIC ${OPENGL_LIBRARIES} GLEW::GLEW)

target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src/vender")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src/vender/stb_image")
target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/src/tests")

target_sources(BatchRenderer PRIVATE ${SRC_FILES})


# target_include_directories(BatchRenderer PUBLIC "usr/include")
# target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/Dependencies/glfw/include")
# target_include_directories(BatchRenderer PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)/Dependencies/glew/include")