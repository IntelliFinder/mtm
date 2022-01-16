cmake_minimum_required(VERSION 3.20)
project(zipping_folder)

set(CMAKE_CXX_STANDARD 14)

include_directories(solution)

add_executable(zipping_folder
        solution/Citizen.cpp
        solution/Citizen.h
        solution/City.cpp
        solution/City.h
        solution/Employee.cpp
        solution/Employee.h
        solution/exceptions.h
        solution/Faculty.h
        solution/Manager.cpp
        solution/Manager.h
        solution/Skill.cpp
        solution/Skill.h
        solution/Workplace.cpp
        solution/Workplace.h)
