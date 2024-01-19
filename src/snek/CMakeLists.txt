project(snek_lib)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_path(LINMATH_INCLUDE_DIRS "linmath.h/linmath.h")

add_library(snek_lib STATIC
  "game.h"
  "render.h"
  "types.h"
  "util.h"
)

add_subdirectory(game)
add_subdirectory(render)

target_include_directories(snek_lib
PRIVATE
  ${LINMATH_INCLUDE_DIRS}
)

target_link_libraries(snek_lib
  PUBLIC
    glad::glad
    glfw
)

