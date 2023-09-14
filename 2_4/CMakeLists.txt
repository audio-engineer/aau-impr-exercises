cmake_minimum_required(VERSION 3.26)
project(2_4 C)

file(GLOB SRC_FILES src/*.c src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})
