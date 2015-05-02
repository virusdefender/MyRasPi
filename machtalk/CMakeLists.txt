#CMakeLists.txt for build machtalk_upload 
project(machtalk_upload)
cmake_minimum_required(VERSION 2.8)
#INCLUDE (CheckTypeSize)

#check c++11 support 
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


set(SRC_LIST dht11_v2.1.c machtalk_v1.c machtalk_upload.cpp)
#set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(machtalk_upload ${SRC_LIST})
target_link_libraries(machtalk_upload -lwiringPi)

#add_definitions("-Wall")
#add_definitions("-std=c++11") 
