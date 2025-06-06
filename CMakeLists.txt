cmake_minimum_required(VERSION 3.25)
project(JuegoDelPirata)

set(CMAKE_CXX_STANDARD 20)

# Agregamos los subdirectorios de lógica y consola
add_subdirectory(core)
add_subdirectory(app_console)
