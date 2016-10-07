#cmake 
# support parse ini file 
#//compile guide
#//$ gcc  -shared  -o libiniparser.so -Wl,-soname=libiniparser.so,-rpath=/usr/lib dictionary.c iniparser.c 
#project(iniparser)
cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_C_COMPILER "gcc")
#SET(CMAKE_CXX_COMPILER "g++")
#AUX_SOURCE_DIRECTORY(. INIPARSER_SRCS)
SET(INIPARSER_SRCS dictionary.c 
					iniparser.c)

SET(CMAKE_INSTALL_PREFIX /usr)

ADD_LIBRARY(iniparser SHARED ${INIPARSER_SRCS})

set(CMAKE_C_CFLAGS "-Wl,-soname=libiniparser.so,-rpath=/usr/lib")

INSTALL(TARGETS iniparser   DESTINATION lib)
INSTALL(FILES dictionary.h  DESTINATION include/iniparser)
INSTALL(FILES iniparser.h  DESTINATION include/iniparser)

set_target_properties(iniparser PROPERTIES OUTPUT_NAME "iniparser")

	
