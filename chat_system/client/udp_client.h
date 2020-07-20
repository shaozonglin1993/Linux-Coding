#pragma once

#include <iostream>
#include <>


class udp_server{
	public:
		udp_server();
		void init();
		int recv_data();
		int send_data();
		int brodcast_data();
		~udp_server();
}
