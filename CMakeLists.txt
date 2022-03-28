cmake_minimum_required(VERSION 3.21)
project(tp1algo3)

set(CMAKE_CXX_STANDARD 14)

include_directories(tpEjercicio1Version1)

add_executable(tp1algo3
        tpEjercicio1Version1/main.cpp
        tpEjercicio1Version1/red.cpp
        tpEjercicio1Version1/red.h
        tpEjercicio1Version1/TP-1.cpp
        tpEjercicio1Version1/TP-1.h)
