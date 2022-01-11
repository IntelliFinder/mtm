cmake_minimum_required(VERSION 3.20)
project(solution)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(solution
        citizen.h
        City.h
        employee.h
        exceptions.h
        faculty.h
        main.cpp
        manager.h
        skill.h
        solution.cpp
        Workplace.h)
