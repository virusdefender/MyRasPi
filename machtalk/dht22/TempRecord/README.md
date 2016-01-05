# dep
	apt-get install sqlite3 libsqlite3-dev 

# create database with sql file 
	$ sqlite3 temps.db < create-table-only-sqlite3.sql 

# build example file 

	$ g++ -o recordtemp RecordTemps.cpp -lsqlite3 


