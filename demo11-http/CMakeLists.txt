CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(HH)

# 设置 C++ 编译器的编译选项
set(CMAKE_CXX_FLAGS  -std=c++11)
set(CMAKE_REQUIRED_FLAGS -std=c++11)

include(CheckIncludeFileCXX)

# 让make时显示编译命令
# set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_C_COMPILER /usr/local/gcc/bin/gcc)
# set(CMAKE_CXX_COMPILER /usr/local/gcc/bin/c++)

# 定义颜色值，message()时可用到
if(WIN32)
    set(OS_NAME "WINDOWS")
else()
    set(OS_NAME "LINUX")
    string(ASCII 27 Esc)
    set(ColorReset "${Esc}[m")
    set(ColorBold "${Esc}[1m")
    set(Red "${Esc}[31m")
    set(Green "${Esc}[32m")
    set(Yellow "${Esc}[33m")
    set(Blue "${Esc}[34m")
    set(Magenta "${Esc}[35m")
    set(Cyan "${Esc}[36m")
    set(White "${Esc}[37m")
    set(BoldRed "${Esc}[1;31m")
    set(BoldGreen "${Esc}[1;32m")
    set(BoldYellow "${Esc}[1;33m")
    set(BoldBlue "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan "${Esc}[1;36m")
    set(BoldWhite "${Esc}[1;37m")
endif()

# 检查是32位还是64位系统
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message("${Green}${OS_NAME}${ColorReset} ${Yellow}x86 system${ColorReset}")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message("${Green}${OS_NAME}${ColorReset} ${Yellow}x86_64 system${ColorReset}")
else()
    message("${Green}${OS_NAME}${ColorReset} ${Yellow}unknown bits system${ColorReset}")
endif()

# SOURCE FILES
set(HH_srcs
)

# HEADER FILES
set(HH_hdrs
)

ADD_EXECUTABLE(HH main.cpp
)
