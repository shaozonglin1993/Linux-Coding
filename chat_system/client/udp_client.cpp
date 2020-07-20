#include "udp_server.h"

static void print_log(const std::string &msg,const char *fun, const int &line)
{
	std::cerr<< ;
}

udp_server::udp_server(const std::string &_ip,const int &port) 
{
}

void udp_server::init()
{
	sock = socket(AF_INET,SOCK_DGRAM, 0);
	if( sock < 0){
		print_log("create socket error!",__FUNCTION__,__LINE__);
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());

	if( bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
	}
}

int udp_server::recv_data(std::string out)
{
	char buf[SIZE];
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
}

int udp_server::send_data(const std::string &in, const struct sockaddr_in &client, const socklen_t &len)
{
}

int udp_server::brodcast_data()
{
	return 0;
}

void udp_server::~udp_server()
{

}




