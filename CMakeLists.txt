cmake_minimum_required(VERSION 3.24)
project(snek)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_path(LINMATH_INCLUDE_DIRS "linmath.h/linmath.h")

add_executable(${CMAKE_PROJECT_NAME}
  "src/engine.h"
  "src/game.h"
  "src/main.c")

add_subdirectory("src/engine")
add_subdirectory("src/game")

target_include_directories(${CMAKE_PROJECT_NAME}
PRIVATE
  ${LINMATH_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME} 
PRIVATE
  glad::glad
  glfw)
