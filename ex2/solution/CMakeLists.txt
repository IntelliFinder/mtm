cmake_minimum_required(VERSION 3.20)
project(solution)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(solution
        Citizen.h
        City.h
        Employee.h
        exceptions.h
        Faculty.h
        Manager.h
        Skill.h
        solution.cpp
        Workplace.h)
