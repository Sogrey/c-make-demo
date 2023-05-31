CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(cTest)

# 设置 C++ 编译器的编译选项
set(CMAKE_CXX_FLAGS
    -std=c++11
)
set(CMAKE_INSTALL_BINDIR "./dist")

# SOURCE FILES
set(cTest_srcs
)

# HEADER FILES
set(cTest_hdrs
)

ADD_EXECUTABLE(cTest main.cpp)


