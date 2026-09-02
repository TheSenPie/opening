cmake_minimum_required(VERSION 4.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Opening)

add_executable("${PROJECT_NAME}" src/main.cpp)

# Conan
execute_process(
    COMMAND "conan" "install"
    "${CMAKE_CURRENT_LIST_DIR}"
    "-of=${CMAKE_CURRENT_BINARY_DIR}/conan"
    "-b=missing"
    "-s:b=build_type=${CMAKE_BUILD_TYPE}"
    "-s:h=build_type=${CMAKE_BUILD_TYPE}"
    "-pr:b=${CMAKE_CURRENT_LIST_DIR}/cmake/platform/conan/${PLATFORM}.profile"
    "-pr:h=${CMAKE_CURRENT_LIST_DIR}/cmake/platform/conan/${PLATFORM}.profile"
    OUTPUT_VARIABLE CONAN_OUTPUT
)

set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_BINARY_DIR}/conan")

find_package(glfw3 REQUIRED CONFIG)

# Link
target_link_libraries("${PROJECT_NAME}" PRIVATE glfw)
