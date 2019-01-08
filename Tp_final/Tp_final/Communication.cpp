#include "Communication.h"
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>    

#define IPFILE "DireccionesIP.txt"
#define HELLO_PORT_STR "15667"
#define HELLO_PORT 15667

Communication::Communication(std::string ip) :Observable(Observable::Observable_type::com)
{

	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	resolver = new boost::asio::ip::tcp::resolver(*IO_handler);	

	
	this->client_mode = true;		//siempre intento ser cliente primero.

	
	if(!startConnectionForClient(his_ip.c_str())) {
		//generar numero aleatorio entre 2000 y 5000 segundos para esperar esa cantidad de milisegundos 
		this->client_mode = false;
		startConnectionForServer();
	}

	new_info = false;
}

Communication::~Communication()
{
	acceptor->close();
	socket->close();
	delete resolver;
	delete acceptor;
	delete socket;
	delete IO_handler;
	
}

/******************************

/******************************
***********endCom*************
*******************************
endCom avisa que se cierra el programa y espera al ACK para finalizar

INPUT:
	void.
OUTPUT:
	void.
*/
void Communication::endCom() {
	//aqui se informaria a todas las computadoras que se ha terminado la conversacion. 
	//Esto seria posible si hubiese un protocolo de comunicacion que cubra esto.
}







/*****************************************
***********startConnectionForClient****************
******************************************
startConnectionForClient inicia la conexión con maquina siendo cliente.

INPUT:
	void.
OUTPUT:
	bool:.
*/
bool Communication::startConnectionForClient(const char * host) {
	renewClientItems();
	try{

		endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));

		boost::asio::connect(*socket, endpoint);

		socket->non_blocking(true);
		client_mode = false;
	}
	catch ( std::exception & e) {
		std::cout << "Error al intentar conectar" << std::endl;
	}
	
}

/*****************************************
***********startConnectionForServer****************
******************************************
startConnectionForServer inicia la conexión con maquina siendo server.

INPUT:
	void.
OUTPUT:
	bool:.
*/
void Communication::startConnectionForServer() {
	
	renewServerItems();
	
	acceptor->accept(*socket);
	socket->non_blocking(true);

	client_mode = true;

}
/*****************************************
***********sendMessage********************
******************************************
sendMessage - Receives a package and makes the convertion to send it by networking

INPUT:
	Package *
OUTPUT:
	void.
*/
void Communication::sendMessage(Package * package_received) {

	//startConnectionForClient(his_ip.c_str());

	size_t len;
	boost::system::error_code error;
	
	do
	{
		len = socket->write_some(boost::asio::buffer(package_received->get_sendable_info(), package_received->get_info_length()), error);
	} 
	while ((error.value() == WSAEWOULDBLOCK));

	if (error)
		std::cout << "Error while trying to send message. " << error.message() << std::endl;
}

/*****************************************
***********receiveMessage*****************
******************************************
receiveMessage - Receives a message from networking and makes the appropiate package

INPUT:
	void.
OUTPUT:
	Package *
*/
Package * Communication::receiveMessage() {
	//startConnectionForServer();

	Package * package_received=NULL;

	boost::system::error_code error;	

	char buf[1000];		// por donde recibire el input

	size_t len = 0;


	len = socket->read_some(boost::asio::buffer(buf), error);			//leo el input que me envia la otra maquina									
	
	if (error.value() == WSAEWOULDBLOCK) {
		//no leyo nada!!
		std::cout << "NOREAD " << error.message() << std::endl;
	}
	else if (!error)
	{

		Package_type type = (Package_type)buf[0];


		switch (type)
		{
		case Package_type::ACK:

			package_received = new ACK_package;

			break;

		case Package_type::NAME:

			package_received = new NAME_package;

			break;

		case Package_type::NAME_IS:

			package_received = new NAME_IS_package(buf[1], &buf[2]); //sending namelength and newname(char*) to the constructor

			break;

		case Package_type::MAP_IS:

			package_received = new MAP_IS_package(&buf[1]);

			break;

		case Package_type::GAME_START:

			package_received = new GAME_START_package;

			break;

		case Package_type::MOVE:

			package_received = new MOVE_package((Character_type)buf[1], buf[2], buf[3]);

			break;

		case Package_type::ATTACK:

			package_received = new ATTACK_package((Character_type)buf[1], buf[2], buf[3]);

			break;

		case Package_type::ACTION_REQUEST:

			package_received = new ACTION_REQUEST_package((Action_type)buf[1], buf[2], buf[3]);

			break;

		case Package_type::ENEMY_ACTION:

			package_received = new ENEMY_ACTION_package(buf[1], (Action_type)buf[2], buf[3], buf[4]);

			break;

		case Package_type::WE_WON:

			package_received = new WE_WON_package;

			break;

		case Package_type::PLAY_AGAIN:

			package_received = new PLAY_AGAIN_package;

			break;

		case Package_type::GAME_OVER:

			package_received = new GAME_OVER_package;

			break;

		case Package_type::QUIT:

			package_received = new QUIT_package;

			break;

		case Package_type::ERROR:

			package_received = new ERROR_package;

			break;

		}
	}

	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;


	return package_received;
}

/***************************************
***********parseMessage*****************  NOT IN USE, DELETE AFTER REVIEW
****************************************

INPUT:
	void.
OUTPUT:
*/
void Communication::parseMessage() {
	
	notify_obs();

}

	string Communication::give_me_my_name()
	{
		return this->my_name;
	}

void Communication::renewClientItems() {
	if(socket != NULL )
		delete socket;
	if (IO_handler != NULL)
		delete IO_handler;
	if (resolver != NULL)
		delete resolver;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}
void Communication::renewServerItems() {

	if(acceptor != NULL)
		delete acceptor;
	if (socket != NULL)
		delete socket;
	if (IO_handler != NULL)
		delete IO_handler;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}


uint32_t Communication::get_expected_id() {
	return expected_ack_id;
}



Package * Communication::get_received_package() {
	return this->received_package;
}

bool Communication::has_new_info() {
	return this->new_info;
}
bool Communication::is_client() {
	return this->client_mode;
}