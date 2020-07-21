#include "sql_api.h"

sql_api::sql_api(const std::string &_host, const std::string &_user, const std::string &_passwd, const std::string &_db)
	:host(_host)
	,user(_user)
	,passwd(_passwd)
	,db(_db)
{
	port = 3306;
	res = NULL;
	conn = mysql_init(NULL);
}


int sql__api::my_connect_mysql()
{
	int ret = -1;
	if( !mysql_real_connect(conn, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0) ){
		std::cerr<<"connect failed !"<<std::endl;
	}else{
		std::cout<<"connect success!"<<std::endl;
		ret = 0;
	}
	return ret;
}


int sql_api::my_insert(std::string &cols, std::string &data)
{
	std::string sql = "INSERT INTO mytable_info";
	sql += cols;
	sql +=" values ";
	sql += data;

	std::cout<<sql<<std::endl;

	if( mysql_query(conn, sql.c_str()) == 0 ){
		std::cout<<"insert success!"<<std::endl;
	}else{
		std::cerr<<"insert failed! "<<std::endl;
	}
}

int sql_api::my_select()
{
	std::string sql = "SELECT * FROM mytable";
	if( mysql_query(conn, sql.c_str()) == 0 ){
		std::cout<<"select success!"<<std::endl;
	}else{
		std::cerr<<"select  failed!"<<std::endl;
		return -1;
	}

	res = mysql_store_result(conn);
	if( res ){
		int lines = mysql_num_rows(res);
		int cols  = mysql_num_fields(res);

		std::cout<<"line : "<<lines<<" "<<"cols : "<<cols<<std::endl;
		MYSQL_FILED *_fn = NULL:
			for(; _fn = mysql_fetch_field(res); ){
				std::cout<<_fn->name<<"\t";
			}

		int i = 0;
		std::cout<<std::endl;

		for(; i < lines; i++ ){
			MYSQL_ROW row = mysql_fetch_row(res);
			int j = 0;
			for( ; j < cols; j++){
				std::cout<<row[j]<<'\t';
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
}

sql_api::~sql_api()
{
}

#ifdef _DEBUG_
int main()
{
	sql_api *sql = new sql_api;

	std::string cols = "(name, school, hobby)";
	std::string data = "('shaozonglin', 'XATU', coding)";

	sql->my_connect_mysql();

	sql->my_select();

	delete sql;
	sql = NULL;
	sts::cout<<"client info : "<<mysql_get_client_info()<<std::endl;
	return 0;
}
#endif
