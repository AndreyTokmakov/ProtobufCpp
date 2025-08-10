cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(ProtoBuff)
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)

list(APPEND EXTRA_LIBS)
if (CMAKE_SYSTEM_VERSION MATCHES "5.15") # 5.15 - My home Ubuntu-20.04
    set(THIRD_PARTY_DIR /home/andtokm/DiskS/ProjectsUbuntu/third_party)
    list(APPEND EXTRA_LIBS tbb)
else()
    set(THIRD_PARTY_DIR /home/andrei/Projects/third_party)
endif()

add_compile_options(-c -Wall -Wextra -O3 -std=c++26)

add_subdirectory(Basics)
add_subdirectory(Manual)
add_subdirectory(SimpleDemo)
add_subdirectory(Utilities)