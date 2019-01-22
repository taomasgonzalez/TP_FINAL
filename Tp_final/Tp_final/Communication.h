#pragma once
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "general.h"
#include "Observer.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "Observable.h"
#include "Package.h"
#include <ctime>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>    

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
	Communication(std::string ip);
	~Communication();

	void endCom();
	void sendMessage(Package * package_received);
	Package * receiveMessage();
	std::string give_me_my_name();

	//Package * get_received_package();
	uint32_t get_expected_id();

	std::string my_ip;
	std::string his_ip;

	bool has_new_info();

	bool is_client();
	bool is_the_connection_healthy();

private:

	//parametros de boost para el manejo de IO por internet.
	boost::asio::io_service* IO_handler = NULL;
	boost::asio::ip::tcp::socket* socket = NULL;
	boost::asio::ip::tcp::resolver* client_resolver = NULL;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::ip::tcp::acceptor* acceptor = NULL;

	void Connecting_as_a_server();
	void Connecting_as_a_client(std::string ip);

	void renewServerItems();
	void renewClientItems();

	bool client_mode=true;		//By default we try to connect as a client
	bool new_info=false;
	bool healthy_connection = true;
	bool rebooting_mode = false; //When rebooting the communication between the programs with closing the program

	uint32_t expected_ack_id;

	std::string my_name; //must have terminator
	std::string his_name; //must have terminator


};

