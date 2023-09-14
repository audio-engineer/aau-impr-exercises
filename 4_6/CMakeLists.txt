project(4_6 C)

file(GLOB SRC_FILES src/*.c src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})
