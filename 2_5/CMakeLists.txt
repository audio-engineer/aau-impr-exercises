project(2_5 C)

file(GLOB SRC_FILES src/*.c src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})
