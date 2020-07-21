#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <map>
#include "data_pool.h"
#include "common.h"
#include "udp_data.h"

class udp_server{
	private:
		bool is_friend_exist(const std::string &key);
		int add_friend(struct sockaddr_in &cli);
		int del_friend(struct sockaddr_in &cli);
		int send_data(const std::string &in,const struct sockaddr_in &client,const socklen_t &len);
	public:
		udp_server(const std::string &_ip = "127.0.0.1",const int &_port = 9999);
		void init();
		int recv_data(std::string &out);
		int brodcast_data();
		~udp_server();
	private:
		int sock;
		std::string ip;
		int port;
		std::map<std::string,struct sockaddr_in> online_user;
		data_pool pool;
}
