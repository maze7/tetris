# Tetris

This project implements a simple tetris clone, including an AI which plays itself.

# Getting Started

This project uses [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) to link to external libraries.
To download all required dependencies, clone with the following command:

```bash
git clone --recurse-submodules git@github.com:maze7/tetris.git
```

If you have already cloned the repository, but are missing submodules, use the following commands:

```bash
git submodule init
git submodule update
```

### Dependencies

* [raylib](https://www.raylib.com/)

### Building the program

* This project uses [CMake](https://cmake.org/download/) as the build system. Please ensure you have CMake installed on your system before attempting to build.
Once you have cmake installed, you can build the program using the following command:

```bash
cmake .
```

# Code Standards & Naming Conventions

### Files & Folders
* All files and folders should use lowercase snake_case naming conventions. All files should clearly describe their contents and should not contain non alpha-numeric characters. For example: `game_state.h`

### Classes & Namespaces
* All classes and namespaces should use PascalCase naming, and should clearly describe the contents and functionality of the class. Prefer descriptiveness over brevity. For example; `GameState`

### Variables & Member Variables
* All variables (including class member variables) should use snake_case naming conventions. Variable names should clearly describe the use and contents of the variable.
Class member variables should be prefixed with an `m_` prefix. For example; `m_current_state`.

### Functions & Member Functions
* All functions should use snake_case naming conventions. A function name should clearly describe the use of the function, as well as any side effects of calling a function. For example; `handle_input()`

### Miscellaneous
* All header files should begin with `#pragma once` to reduce the chance of cyclical includes. Where possible, forward declaration should be preferred over includes in header files in an effort to keep compile times low.

# Directory Structure & Files
```
.
├── build                               # intermediate build files and resulting binary executable
│ 
├── lib                                 # third-party libraries
│   ├── raylib                          # raylib main library
│   └── raygui                          # raylib immediate-mode UI library
│   
├── res                                 # game resources / assets
│   ├── crt_shader.frag                 # CRT Effect shader for main menu logo (18 loc)
│   └── tetris_logo.png                 # Tetris logo for main menu
│   
├── src                                 # project source code
│   ├── core                            # engine core files
│   │   ├── config.h                    # Config struct for game settings (8 loc)
│   │   ├── game.h                      # Main application loop & manager class header (31 loc)
│   │   ├── game.cpp                    # Main application loop & manager class implementation (40 loc)
│   │   └── game_state.h                # Definition of GameState inteface and DummyState class (33 loc)
│   │
│   ├── game                            # GameState-related files
│   │   ├── commands.h                  # Defines the Command, MoveCommand and RotateCommand classes (39 loc)
│   │   ├── input.h                     # Defines the InputSystem static class (9 loc)
│   │   ├── input.cpp                   # Implementation for the InputSystem class (21 loc)
│   │   ├── piece.h                     # Defines the Piece class (Tetronimo Piece) (55 loc)
│   │   ├── piece.cpp                   # Implementation for the Piece class (14 loc)
│   │   ├── play_state.h                # Defines the PlayState class, which acts as the game state (33 loc)
│   │   └── play_state.cpp              # Implementation for the PlayState class (150 loc)
│   │
│   ├── menu                            # MenuState-related files
│   │   ├── config_state.h              # Defines the ConfigState class which acts as the config menu (29 loc)
│   │   ├── config_state.cpp            # Implementation of the ConfigState class (91 loc)
│   │   ├── menu_state.h                # Defines the MenuState class which acts as the main menu (25 loc)
│   │   ├── menu_state.cpp              # Implementation of the MenuState class (55 loc)
│   │   ├── score_state.h               # Definition of ScoreState class, which displays the game over score (20 loc)
│   │   └── score_state.cpp             # Implementation of the ScoreState class (32 loc)
│   │
│   ├── main.cpp                        # program entry point (16 loc)
│   └── pch.h                           # Pre-compiled Headers (14 loc)
│   
├── CMakeLists.txt                      # CMake build script
└── README.md

TOTAL LINES OF CODE: 733
```

## Authors

* Callan Acton
* Nathan Wilson 
* Bailey Bingham-Wilson
