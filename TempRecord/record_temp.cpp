//install dep 
//TODO: you must install mysql-server 
//apt-get install -y libmysqlclient-dev libmysql++-dev libmysqlcppconn-dev

//compile guide
//$ g++ -o rt record_temp.cpp -lmysqlpp -lmysqlclient -L/usr/lib/mysql -I/usr/include/mysql


#include <iostream>
#include <mysql++/mysql++.h>

using namespace mysqlpp;
using namespace std;

#define DB_NAME "Temps"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PWD   "447826004"

int main() {
	mysqlpp::Connection _con(false);
	
	if(!_con.connect(DB_NAME,DB_HOST,DB_USER,DB_PWD)) {
		cout << "connect failed " << endl;
	}

	//query 
	mysqlpp::Query _query = _con.query("SELECT * FROM pi_temps;");
	
	//store the query 
	mysqlpp::StoreQueryResult _result = _query.store();

	for(unsigned int i = 0; i < _result.num_rows(); i++) {
		cout << "[id] " <<  _result[i][0] << endl;
		cout <<"[name] " << _result[i][1] << endl;
		cout << "[temp] " << _result[i][2] << endl;
		cout << "[humi] " << _result[i][3] << endl;
		}

	return 0;
}

