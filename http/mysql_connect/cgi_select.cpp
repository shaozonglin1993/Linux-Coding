#include <iostream>

void myselect( char *arg )
{
	sql_api *sql = new sql_api;

	sql->my_connect_mysql();
	sql->my_select();

	delete sql;
}
