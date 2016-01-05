#CMakeLists.txt for build machtalk_upload 
project(machtalk_dht22)
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


set(SRC_LIST dht22.c 
		locking.c 
		machtalk.c 
		machtalk_dht22.cpp)

#set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(machtalk_dht22 ${SRC_LIST})


option(SUPPORT_MYSQL_DB 
	"insert the temp data to local database" ON)
if (SUPPORT_MYSQL_DB)
	ADD_DEFINITIONS("-DDB_SUPPORT")
	ADD_SUBDIRECTORY(TempRecord)
	include_directories(TempRecord)
endif (SUPPORT_MYSQL_DB) 
target_link_libraries(machtalk_dht22 -lwiringPi)
target_link_libraries(machtalk_dht22 -lpthread)

if (SUPPORT_MYSQL_DB)
	TARGET_LINK_LIBRARIES(machtalk_dht22 libTempRecord)
endif (SUPPORT_MYSQL_DB)

#add_definitions("-Wall")
#add_definitions("-std=c++11") 
