cmake_minimum_required(VERSION 3.7)
project(wet2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -DNDBUG")
set(SOURCE_FILES
        MinHeap.h
        library2.h
        Colosseum.h
        Exception.h
        Gladiator.h
        HashTable.h
        List.h
        SplayTree.h
        library2.cpp
        testFinal.cpp
        )
add_executable(WET2 ${SOURCE_FILES})