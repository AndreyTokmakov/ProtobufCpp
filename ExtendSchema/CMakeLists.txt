cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(ExtendSchema)
set(PROJECT_VERSION 1.0.0.0)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_compile_options(-c -Wall -Wextra -O3 -std=c++26)

find_package(Protobuf REQUIRED)

# Generating sources from .proto
# Will generate '.pb.h' and '.pb.cpc' to the build dir: CMAKE_CURRENT_BINARY_DIR
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
        proto/message.proto
)

# message("PROTO_SRCS = ${PROTO_SRCS}")
# message("PROTO_HDRS = ${PROTO_HDRS}")
# message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

add_executable(${PROJECT_NAME}
        main.cpp
        ${PROTO_SRCS}
        ${PROTO_HDRS}
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Utilities")
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_BINARY_DIR}/Utilities")

target_link_libraries(${PROJECT_NAME}
        utils
        pthread
        ${Protobuf_LIBRARIES}
        ${EXTRA_LIBS}
)