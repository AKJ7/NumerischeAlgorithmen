project("Numerische Algorithmen")

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(../matH/include ../matH/build)


add_subdirectory(blatt1)
add_subdirectory(blatt2)
add_subdirectory(blatt3)
add_subdirectory(blatt4)
add_subdirectory(blatt5)
add_subdirectory(blatt6)
add_subdirectory(blatt7)
add_subdirectory(blatt8)

add_subdirectory(projekt)