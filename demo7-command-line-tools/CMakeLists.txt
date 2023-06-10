CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(smd)


include(CheckIncludeFileCXX)
# 设置 C++ 编译器的编译选项
set(CMAKE_CXX_FLAGS  -std=c++11)
set(CMAKE_REQUIRED_FLAGS -std=c++11)

# 检查头文件依赖是否存在
set(myIncludelist iostream "stdlib.h" "string.h")
foreach(_var ${myIncludelist})
	CHECK_INCLUDE_FILE_CXX(${_var} HAS_INCLUDE_${_var})
endforeach()

# SOURCE FILES
set(smd_srcs
)

# HEADER FILES
set(smd_hdrs
)

ADD_EXECUTABLE(smd main.cpp)