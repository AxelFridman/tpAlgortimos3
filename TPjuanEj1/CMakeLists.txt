cmake_minimum_required(VERSION 3.20)
project(TPjuanEj1)

set(CMAKE_CXX_STANDARD 14)

add_executable(TPjuanEj1 main.cpp
        red.cpp tp1.cpp red.h tp1.h
        actividades_PD.h actividades_PD.cpp actividadesGoloso.cpp actividadesGoloso.h)