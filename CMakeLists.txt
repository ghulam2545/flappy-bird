cmake_minimum_required(VERSION 3.0.0)
project(flappy-bird)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

add_executable(
    flappy-bird main.cpp
    src/game.cpp 
    src/texture.cpp
    src/sound.cpp
    src/bird.cpp
    src/pipe.cpp
)

target_link_libraries(flappy-bird sfml-system sfml-window sfml-graphics sfml-audio sfml-network )