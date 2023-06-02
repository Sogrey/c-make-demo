CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(nodeTest)

# 设置 C++ 编译器的编译选项
set(CMAKE_CXX_FLAGS
    -std=c++11
)
set(CMAKE_INSTALL_BINDIR "./dist")

# SOURCE FILES
set(nodeTest_srcs
)

# HEADER FILES
set(nodeTest_hdrs
)

ADD_EXECUTABLE(nodeTest main.cpp)


