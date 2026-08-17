cmake_minimum_required(VERSION 3.15)
project(GameOfLife CXX)

set(CMAKE_CXX_STANDARD 17)

# Télécharge et configure automatiquement Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Création de l'exécutable
add_executable(GameOfLife game_of_life.cpp)
target_link_libraries(GameOfLife PRIVATE raylib)