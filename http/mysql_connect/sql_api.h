#pragma once

#include <iostream>
#include <string.h>
#include "mysql.h"

class sql_api{
	public:
		sql_api(const std::string &_host="127.0.0.1", const std::string &user="root",const std::string &passwd="", const std::string &_db="mytable");
		int my_connect_mysql();
		int my_insert(std::string &cols, std::string &data);
		int my_select();
		~sql_api();
	private:
		MYSQL *conn;
		MYSQL_RES *res;
		std::string host;
		str::string user;
		std::string passwd;
		std::string db;
		int port;
};
