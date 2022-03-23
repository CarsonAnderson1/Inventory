cmake_minimum_required(VERSION 3.21)
project(Inventory)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Inventory
        Inventory.cpp
        Inventory.h
        Item.cpp
        Item.h
        main.cpp
        menu.cpp
        menu.h
        menu_element.cpp
        menu_element.h
        static_functions.h
        static_functions.cpp)

