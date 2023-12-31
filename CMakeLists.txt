cmake_minimum_required(VERSION 3.25)
project(tetris)

# c++ version
set(CMAKE_CXX_STANDARD 20)

# compiler flags for different build configs
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_PROFILE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(tetris
    src/main.cpp
    src/core/game_state.h
    src/core/game.h
    src/core/game.cpp
    src/menu/menu_state.h
    src/menu/menu_state.cpp
    src/menu/config_state.h
    src/menu/config_state.cpp
    src/menu/score_state.h
    src/menu/score_state.cpp
    src/game/play_state.h
    src/game/play_state.cpp
        src/menu/config_state.h
    src/menu/config_state.cpp
        src/game/piece.cpp src/game/piece.h
        src/game/input.h
        src/game/input.cpp
        src/commands/command.h
        src/core/config.h
        src/commands/move_command.cpp
        src/game/piece_definitions.h
        src/game/grid.h
        src/game/grid.cpp
        src/menu/game_over.cpp
        src/menu/game_over.h
        src/core/scores.h
        src/core/scores.cpp
        src/game/ai_controller.h
        src/game/ai_controller.cpp
        src/commands/drop_command.h
)

# core include directories
target_precompile_headers(tetris PRIVATE src/pch.h)

target_include_directories(tetris
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# build raylib
add_subdirectory(lib/raylib)
target_include_directories(tetris PRIVATE lib/raylib/src)
target_link_libraries(tetris PRIVATE raylib)

# build raygui
target_include_directories(tetris PRIVATE lib/raygui)

# compile definitions for different build configurations
target_compile_definitions(
    tetris PRIVATE
    $<$<CONFIG:Debug>:TETRIS_DEBUG>
    $<$<CONFIG:Profile>:TETRIS_PROFILE>
    $<$<CONFIG:Release>:TETRIS_RELEASE>
)

# build without console in release builds only
# set_target_properties(tetris PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)