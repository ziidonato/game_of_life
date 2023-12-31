cmake_minimum_required(VERSION 3.0.0)
project(game_of_life VERSION 0.1.0 LANGUAGES C)
add_compile_options(-Wall -Wextra -Wpedantic -std=gnu11)

include(CTest)
enable_testing()

set(SOURCES 
    src/life/life.c 
    src/gui/gui.c
    src/life/patterns.c
    src/base/base.c
    src/globals/globals.c
    )

set(HEADERS 
    src/config.h
    src/life/life.h 
    src/globals/globals.h 
    src/gui/gui.h
    src/config.h
    lib/ubench/ubench.h
    src/base/base.h
    src/life/patterns.h
    )

add_executable(game_of_life src/main.c ${SOURCES} ${HEADERS})
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


project(tests)
add_executable(tests tests/test.c ${SOURCES} ${HEADERS})
target_include_directories(tests PRIVATE lib/munit)
target_include_directories(tests PRIVATE src)
target_include_directories(tests PRIVATE lib/ubench)
target_link_libraries(tests PRIVATE raylib)

project(benchmarks)
set(BENCHMARKS_SOURCES 
    benchmarks/benchmark_life.c
    )
set(BENCHMARKS_HEADERS 
    )
add_executable(benchmarks benchmarks/main.c ${SOURCES} ${HEADERS} ${BENCHMARKS_SOURCES} ${BENCHMARKS_HEADERS})
target_include_directories(benchmarks PRIVATE lib/munit)
target_include_directories(benchmarks PRIVATE src)
target_include_directories(benchmarks PRIVATE lib/ubench)
target_link_libraries(benchmarks PRIVATE raylib)


