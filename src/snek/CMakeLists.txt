project(snek_lib)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_path(LINMATH_INCLUDE_DIRS "linmath.h/linmath.h")

add_library(snek_lib STATIC
  "game.h"
  "global_variables.c"
  "global_variables.h"
  "input.h"
  "io.h"
  "render.h"
  "time.h"
  "types.h"
  "util.h"
)

add_subdirectory(game)
add_subdirectory(io)
add_subdirectory(render)
add_subdirectory(time)

target_include_directories(snek_lib
PRIVATE
  ${LINMATH_INCLUDE_DIRS}
)

target_link_libraries(snek_lib
PRIVATE
    glad::glad
    glfw
)

