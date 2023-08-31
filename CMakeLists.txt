cmake_minimum_required(VERSION 3.0.0)
project(game_of_life VERSION 0.1.0 LANGUAGES C)
add_compile_options(-Wall -Wextra -Wpedantic -std=gnu11)

include(CTest)
enable_testing()

set(SOURCES src/main.c src/life/life.c)
set(HEADERS src/config.h src/life/life.h)

add_executable(game_of_life ${SOURCES})
target_include_directories(game_of_life PRIVATE src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 4.5.0
)

FetchContent_MakeAvailable(raylib)
target_link_libraries(game_of_life PRIVATE raylib)