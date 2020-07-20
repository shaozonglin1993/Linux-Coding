void myinsert(char *arg)
{
	sql_api *sql = new sql_api;

	std::string cols = "(name, school, hobby)";

	char *buf[4];
	buf[3] = NULL:
	int index = 2;

	char *end = arg + strlen(arg) - 1;
	while( end > arg){
		if( *end == '=' ){
			buf[index--] = end + 1;
		}
		if( *end == '&'){
			*end = '\0';
		}

		end--;
	}

	std::string data = "(\"";
	data += buf[0];
	data += "\",\"";
	data += buf[1];
	data += "\",\"";
	data +=buf[2];
	data += "\")";

	sql->my_connect_mysql();
	sql->my_insert(cols, data);

	delete sql;
}
