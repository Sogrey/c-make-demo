cmake_minimum_required(VERSION 2.8)

project(sql)

set(CMAKE_CXX_STANDARD 11)

add_executable(sql main.cpp)

target_link_libraries(sql sqlite3)

