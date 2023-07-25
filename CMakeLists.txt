cmake_minimum_required(VERSION 3.25)
project(tetris)

# c++ version
set(CMAKE_CXX_STANDARD 20)

# compiler flags for different build configs
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_PROFILE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(tetris src/main.cpp)

# core include directories
target_precompile_headers(tetris PRIVATE src/pch.h)
target_include_directories(tetris
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# SDL2
add_subdirectory(lib/sdl2)
target_compile_definitions(tetris PRIVATE SDL_MAIN_HANDLED)
target_include_directories(tetris PRIVATE lib/sdl2/include)
target_link_libraries(tetris PRIVATE SDL2-static)

# FMT
add_subdirectory(lib/fmt)
target_include_directories(tetris PUBLIC lib/fmt/include)
target_link_libraries(tetris PUBLIC fmt::fmt)


# compile definitions for different build configurations
target_compile_definitions(
    tetris PRIVATE
    $<$<CONFIG:Debug>:TETRIS_DEBUG>
    $<$<CONFIG:Profile>:TETRIS_PROFILE>
    $<$<CONFIG:Release>:TETRIS_RELEASE>
)

# build without console in release builds only
# set_target_properties(tetris PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)