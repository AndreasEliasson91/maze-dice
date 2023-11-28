# Set CMake version
cmake_minimum_required(VERSION 3.28)

# Define the project and set C++ standard
project(MazeDice)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files
set(MazeDice_SOURCES
    src/main.cpp
    src/game/assets/character/Character.cpp
    src/game/assets/inventory/Inventory.cpp
    src/game/assets/inventory/Item.cpp
    src/game/assets/maze/Cell.cpp
    src/game/assets/maze/Maze.cpp
    src/game/levels/GameLevel.cpp
)
    # src/utils/LevelUtil.cpp

# Collect header files
set(MazeDice_HEADERS
    src/game/assets/character/Character.h
    src/game/assets/inventory/Dice.h
    src/game/assets/inventory/Inventory.h
    src/game/assets/inventory/Item.h
    src/game/assets/maze/Cell.h
    src/game/assets/maze/Maze.h
    src/game/levels/GameLevel.h
    src/game/Game.h
    src/utils/LevelUtil.h
)

# Set include directories
set(MazeDice_INCLUDE_DIRS "")
foreach(_headerFile ${MazeDice_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND MazeDice_INCLUDE_DIRS ${_dir})
endforeach()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(REMOVE_DUPLICATES MazeDice_INCLUDE_DIRS)

# Create the executable target
add_executable(MazeDice ${MazeDice_SOURCES})
target_include_directories(MazeDice PRIVATE ${MazeDice_INCLUDE_DIRS})