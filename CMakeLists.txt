cmake_minimum_required(VERSION 3.24)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

add_executable(yadro main.cpp Info_Club.cpp Info_Club.h Event.cpp Event.h Processing_Event.cpp Processing_Event.h Time_Table.cpp Time_Table.h Time_Table.h)
