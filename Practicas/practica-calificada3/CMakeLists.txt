cmake_minimum_required(VERSION 3.10)
project(PC3_SmartInfants)

include_directories(include)

# Esta seccion se encarga de compilar el ejecutable principal
add_executable(main src/main.cpp)

# Esta seccion se encarga de habilitar el CTest
enable_testing()

# Compila y enlaza el ejecutable de pruebas
add_executable(test_smart_infants tests/test_smart_infants.cpp)
add_test(NAME PruebasPC3 COMMAND test_smart_infants)