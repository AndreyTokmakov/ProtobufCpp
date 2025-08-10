cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Manual)
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++26)

# This requires GCC_15.1 Libraries exported:
# set(PROTO_BUFF_COMPILER "/home/andtokm/DiskS/ProjectsUbuntu/third_party/protobuf/build/protoc")

set(PROTO_BUFF_COMPILER protoc)

set(PROTO_FILES_DIR ${PROJECT_SOURCE_DIR}/schema)
set(PROTO_FILES_GEN ${PROJECT_SOURCE_DIR}/schema_out)

# Get list of "*.proto" of files in 'schema' folder
file(GLOB PROTO_BUFF_FILES ${PROTO_FILES_DIR}/**.proto)

foreach (proto_file ${PROTO_BUFF_FILES})
    get_filename_component(filename ${proto_file} NAME)
    # message("Compiling ${filename} to ${PROTO_FILES_GEN}")
    execute_process(COMMAND ${PROTO_BUFF_COMPILER} --proto_path=${PROTO_FILES_DIR} --cpp_out=${PROTO_FILES_GEN} ${proto_file})
endforeach (proto_file ${PROTO_BUFF_FILES})


# Get all "*.cc" files generated:
file(GLOB PROTO_BUFF_CPP_GEN ${PROTO_FILES_GEN}/**.cc)

#[[
foreach (proto_cpp_file ${PROTO_BUFF_CPP_GEN})
    get_filename_component(filename ${proto_cpp_file} NAME)
    message(${filename})
endforeach (proto_cpp_file ${PROTO_BUFF_CPP_GEN})
#]]

add_executable(${PROJECT_NAME}
        main.cpp
        person/Person.cpp
        request/Request.cpp
        common/Common.cpp
        ${PROTO_BUFF_CPP_GEN}
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        # ${CMAKE_CURRENT_BINARY_DIR}
        ${PROTO_FILES_GEN}
)

target_link_libraries(${PROJECT_NAME}
        utils
        pthread
        protobuf
        # Or path to '/home/andtokm/DiskS/ProjectsUbuntu/third_party/protobuf/build'
        ${EXTRA_LIBS}
)