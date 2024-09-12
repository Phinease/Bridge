cmake_minimum_required(VERSION 3.13)
project(Bridge_data_analyse C)

set(CMAKE_C_STANDARD 99)

add_executable(Bridge_data_analyse main.c monte_carol.h game.h process.h)