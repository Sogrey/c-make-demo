CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(jsonTest)

include(CheckIncludeFileCXX)
# 设置 C++ 编译器的编译选项
set(CMAKE_CXX_FLAGS  -std=c++11)
set(CMAKE_REQUIRED_FLAGS -std=c++11)

# 检查头文件依赖是否存在
set(myIncludelist cstring memory cstddef cstdint istream ostream sstream string type_traits "allocator.h" "version.h" array exception map  deque iosfwd stack cstdlib algorithm cassert cmath iostream limits utility cstdio cctype iomanip)
foreach(_var ${myIncludelist})
	CHECK_INCLUDE_FILE_CXX(${_var} HAS_INCLUDE_${_var})
endforeach()

include_directories(
    ./json
)

# SOURCE FILES
set(jsonTest_srcs
    ./json/jsoncpp.cpp
)

# HEADER FILES
set(jsonTest_hdrs
    ./json/json.h
	./json/json-forwards.h
)

ADD_EXECUTABLE(jsonTest main.cpp 
./json/jsoncpp.cpp)


