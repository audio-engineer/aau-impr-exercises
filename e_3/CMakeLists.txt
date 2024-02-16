project(e_3 C)

configure_file(src/kampe-2023-2024.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(${PROJECT_NAME} src/main.c)
target_include_directories(${PROJECT_NAME} PRIVATE src/)
