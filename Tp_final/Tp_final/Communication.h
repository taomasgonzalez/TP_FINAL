#pragma once
#include <vector>
#include <iostream>
#include "general.h"
#include "Observer.h"
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "Observable.h"
#include "Package.h"

typedef basic_string<char> string;


extern "C" {
#include <stdint.h>
}


#define ANIMATION_ID 0					//posicion en el mensaje YOU_GO donde ira a parar la animacion.
#define COUNT_ID 1						//posicion en el mensaje YOU_GO donde ira a parar el COUNT
#define MACHINES_ID (COUNT_ID+1)	    //posicion en el mensaje YOU_GO de la maquina 1 (de la primera maquina). Es la prox a COUNT_ID

class Communication : public Observable
{
public:
	Communication(std::string ip = NULL);
	~Communication();

	void endCom();
	void sendMessage(Package * package_received);
	Package * receiveMessage();
	void parseMessage();

	Package * get_received_package();
	uint32_t get_expected_id();

	std::string my_ip;
	std::string his_ip;

	bool has_new_info();

	bool is_client();

private:

	//parametros de boost para el manejo de IO por internet.
	boost::asio::io_service* IO_handler = NULL;
	boost::asio::ip::tcp::socket* socket = NULL;
	boost::asio::ip::tcp::resolver* resolver = NULL;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::ip::tcp::acceptor* acceptor = NULL;

	bool startConnectionForServer();
	bool startConnectionForClient(const char * host);

	void renewServerItems();
	void renewClientItems();

	bool client_mode;

	uint32_t expected_ack_id;

	std::string my_name;
	std::string his_name;

	bool new_info;

};

