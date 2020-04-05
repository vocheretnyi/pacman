cmake_minimum_required(VERSION 3.15)
project(pac_man)

set(CMAKE_CXX_STANDARD 17)

#set(SFML_INCLUDE_DIR "/home/vocheretnyi-ua/SFML-2.5.1/include")
#set(SFML_LIBRARY_DIR "/home/vocheretnyi-ua/SFML-2.5.1/lib")
#set(SFML_DIR "/home/vocheretnyi-ua/SFML-2.5.1/lib/cmake/SFML")

#link_directories(SFML_LIBRARY_DIR)
#include_directories(SFML_INCLUDE_DIR)

#find_package(Freetype)
#find_package(JPEG)
#find_package(SFML 2.5.1 COMPONENTS window graphics system REQUIRED)

include_directories(include)

add_executable(pac_man src/main.cpp src/game_map.cpp src/pacman.cpp src/path_finder.cpp src/ghost.cpp src/minimax.cpp src/monster.cpp src/pacmanController.cpp src/ghostController.cpp)

target_link_libraries(pac_man sfml-graphics sfml-window sfml-system)

