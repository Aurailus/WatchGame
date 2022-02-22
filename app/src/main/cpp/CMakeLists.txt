cmake_minimum_required(VERSION 3.18.1)

project("Roguelike")

add_library(Roguelike SHARED main.cpp)

find_library(log-lib log)

target_link_libraries(Roguelike ${log-lib})