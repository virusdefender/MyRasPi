#cmake 
# support connect to mysql 5.5 
#
#//compile guide
#//$ g++ -o rt record_temp.cpp -lmysqlclient -L/usr/lib/mysql -I/usr/include/mysql
cmake_minimum_required(VERSION 2.8)

AUX_SOURCE_DIRECTORY(. MYSQL_TEMP_RECORD_SRCS)
ADD_DEFINITIONS("-L/usr/lib/mysql")
ADD_DEFINITIONS("-I/usr/include/mysql")
#include_directories("/usr/include/mysql")
ADD_LIBRARY(libTempRecord SHARED ${MYSQL_TEMP_RECORD_SRCS})

#target_link_libraries(libTempRecord -lmysqlpp)
target_link_libraries(libTempRecord -lmysqlclient)
#set_target_properties(libTempRecord PROPERTIES OUTPUT_NAME "TempRecord")


	
