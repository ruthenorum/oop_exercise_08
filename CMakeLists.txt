cmake_minimum_required(VERSION 3.17)
project(OOP8)
set(CMAKE_CXX_STANDARD 14)
add_executable(OOP8 main.cpp)
find_package( Threads )
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )

