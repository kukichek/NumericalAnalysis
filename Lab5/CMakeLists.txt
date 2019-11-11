cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab5 main.cpp Matrix.h Matrix.cpp
        FrobeniusForm.h FrobeniusForm.cpp PrintToFile.h PrintToFile.cpp)