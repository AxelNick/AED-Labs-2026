cmake_minimum_required(VERSION 3.10)
project(PC3_SmartInfants)

# Añade la carpeta 'include' globalmente para no repetirlo
include_directories(include)

# 1. Ejecutable principal (Para AtCoder)
add_executable(main src/main.cpp)

# 2. Habilitar y compilar CTest
enable_testing()
add_executable(test_smart_infants tests/test_smart_infants.cpp)
add_test(NAME PruebasPC3 COMMAND test_smart_infants)

# 3. Construcción de la Demo Interactiva
add_executable(demo_smart_infants demos/demo_smart_infants.cpp)

# 4. Construcción del Benchmark de Rendimiento
add_executable(benchmark_pc3 benchmark/benchmark_pc3.cpp)
# Activamos la bandera de optimización extrema (-O3) solo para el benchmark
target_compile_options(benchmark_pc3 PRIVATE "-O3")