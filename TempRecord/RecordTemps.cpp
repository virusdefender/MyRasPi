/*
  Record temp && humidity info into sqlite3 database 

*/

#include <string>
#include <iostream>
#include <sstream>
//sqlite3 
#include <sqlite3.h>

using namespace std;

sqlite3 *pdb;

int InsertT(float temp, float hum) {

char *errMsg;

int res = sqlite3_exec(pdb, "begin transaction;",0,0,&errMsg);

 //for (float i = 1.0; i < 10.0; i++) {

	std::stringstream strsql;
        strsql << "insert into temps(temperature,humidity) values(";
	strsql << temp <<  "," << hum << ");";

       // strsql << i << "," << (i+11.0) << ");";
        std::string str = strsql.str();
	res = sqlite3_exec(pdb,str.c_str(),0,0,&errMsg);

	if (res != SQLITE_OK) 
           	{
 		std::cout << "process error." << errMsg << std::endl;
		return -1;
 		} 

  	//}
	
	res = sqlite3_exec(pdb,"commit transaction;",0,0,&errMsg);
	std::cout << "Process success." << std::endl;
	return 0;
}

int main(int argc, char ** argv) {
	int res = sqlite3_open("./temps.db",&pdb);
	if (res) {
	std::cout << "Can't open database: " << sqlite3_errmsg(pdb);
	sqlite3_close(pdb);
	return -1;
	}
	
	res = InsertT(22.75,18.90);

	if (res != 0) {
		return 0;
		}

	return 0;
}





