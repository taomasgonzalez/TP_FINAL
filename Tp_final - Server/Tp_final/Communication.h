#pragma once

#define _WIN32_WINNT 0x0501
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <boost/algorithm/string.hpp>    

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <queue>
#include "Package.h"
#include "general.h"
#include "Userdata.h"
#include "Observable.h"

using namespace std;
//typedef basic_string<char> string;


#define IPFILE "DireccionesIP.txt"
#define SNOWBORS_PORT_STR "13225"
#define SNOWBORS_PORT 13225

extern "C" {
#include <stdint.h>
}


#define ANIMATION_ID 0					//posicion en el mensaje YOU_GO donde ira a parar la animacion.
#define COUNT_ID 1						//posicion en el mensaje YOU_GO donde ira a parar el COUNT
#define MACHINES_ID (COUNT_ID+1)	    //posicion en el mensaje YOU_GO de la maquina 1 (de la primera maquina). Es la prox a COUNT_ID


class Communication : public Observable
{
public:
	Communication(Userdata * my_user_data);
	~Communication();

	void endCom();
	void sendMessage(Package * package_received);
	Package * receiveMessage();

	//Package * get_received_package();
	uint32_t get_expected_id();

	bool is_the_connection_healthy();

private:

	//parametros de boost para el manejo de IO por internet.
	boost::asio::io_service* IO_handler = NULL;
	boost::asio::ip::tcp::socket* socket = NULL;
	boost::asio::ip::tcp::resolver* client_resolver = NULL;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::ip::tcp::acceptor* acceptor = NULL;

	void Connecting_as_a_server(Userdata * my_user_data);
	void Connecting_as_a_client(std::string ip, Userdata * my_user_data);

	void renewServerItems();
	void renewClientItems();

	bool healthy_connection = true;
	bool rebooting_mode = false; //When rebooting the communication between the programs with closing the program

	uint32_t expected_ack_id;


	void copy_message(Package * package_received, unsigned char *buf);
	Package* create_package(unsigned char* aux_buf);
	Package * received = NULL;
	queue<Package*> packages_queue;

};

