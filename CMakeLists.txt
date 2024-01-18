cmake_minimum_required(VERSION 3.24)
project(snek)

add_subdirectory("src/snek")

add_executable(${CMAKE_PROJECT_NAME} "src/main.c")

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE snek_lib)
