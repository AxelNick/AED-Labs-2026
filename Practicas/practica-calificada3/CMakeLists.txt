cmake_minimum_required(VERSION 3.10)
project(PC3_SmartInfants)

# Le decimos al compilador dónde buscar los archivos .h (tus librerías)
include_directories(include)

# Creamos el ejecutable principal
add_executable(main src/main.cpp)