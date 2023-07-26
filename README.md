# 2805ICT - Tetris

A collaborative group assignment for 2805ICT at Griffith University. This project implements a simple tetris clone 
using software engineering best practices.

## Getting Started

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
cmake --build .
```

## Authors

* Callan Acton
* Nathan Wilson 
* Bailey Bingham-Wilson