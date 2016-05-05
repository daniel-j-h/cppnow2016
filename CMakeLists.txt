cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(pulling-visitors VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.59 REQUIRED coroutine thread system context)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})


add_executable(01 01.cc)
add_executable(02 02.cc)
add_executable(03 03.cc)
add_executable(04 04.cc)

add_executable(05 05.cc)
target_link_libraries(05 ${Boost_COROUTINE_LIBRARY} ${Boost_CONTEXT_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_executable(06 06.cc)

add_executable(07 07.cc)
target_link_libraries(07 ${Boost_COROUTINE_LIBRARY} ${Boost_CONTEXT_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_executable(08 08.cc)
