cmake_minimum_required(VERSION 4.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Opening)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# nicegraf
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/nicegraf SYSTEM)

set(IsMacOS ON)
if(IsIOS OR IsMacOS)
    set(NGF_BACKEND "MTL")
    if(IsMacOS)
        set(PLATFORM "macos")
    elseif(IsIOS)
        set(PLATFORM "ios")
    endif()
else()
    if(IsWindows)
        set(PLATFORM "windows")
    elseif(IsLinux)
        set(PLATFORM "linux")
    endif()

    if(NOT NGF_BACKEND)
        set(NGF_BACKEND "VK")
    else()
        string(TOUPPER ${NGF_BACKEND} NGF_BACKEND)
    endif()
endif()
string(TOLOWER ${NGF_BACKEND} NGF_BACKEND_SUFFIX)
set(NICEGRAF_LIB "nicegraf-${NGF_BACKEND_SUFFIX}")
set_property(TARGET nicegraf-internal nicegraf-util ${NICEGRAF_LIB} PROPERTY FOLDER "nicegraf")

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
target_link_libraries("${PROJECT_NAME}" PRIVATE ${NICEGRAF_LIB} nicegraf-util)
