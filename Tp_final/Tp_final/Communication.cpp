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
sendMessage INCREMENTA EL COUNT y luego envia el mensaje a una sola maquina en espefico.

INPUT:
	void.
OUTPUT:
	void.
*/
void Communication::sendMessage(Package package_received) {

	//startConnectionForClient(his_ip.c_str());

		//IMPLEMENTAR RECIBIR EL PAQUETE A MANDAR COMO ARGUMENTO

	Package_type package_code = package_received.get_package_header();

	uint message_length;

	ACK_package *ack_package = NULL;
	MOVE_package *move_package = NULL;
	QUIT_package * quit_package = NULL;
	char * pos_char_pointer = NULL;
	uint16_t * pos_pointer = NULL;
	char * id_char_ptr = NULL;
	uint32_t * id_pointer = NULL;
	uint32_t  id_ack = NULL;
	uint32_t * id_pointer_ack = NULL;
	char * pos_char_pointer_ack = NULL;
	uint16_t * pos_pointer_imr = NULL;
	uint32_t id_move;
	uint32_t * id_ptr_move = NULL;
	char * id_char_ptr_move = NULL;
	uint16_t  worm_pos;


	switch (package_code)
	{
	case Package_type::ACK:

		message_length = 1; //amount of chars in ACK_package, only header

		break;

	case Package_type::NAME:

		message_length = 1; //amount of chars in NAME_package, only header
		package_to_be_send = new char[message_length];

		break;

	 case Package_type::NAME_IS:


		message_length = 2 + package_received.get_name_length(); //amount of chars in NAME_package, only header


		break;

	 case Package_type::MAP_IS:

		 message_length = 194; //amount of chars in NAME_package, only header


		 break;

	 case Package_type::MOVE:
	 case Package_type::ATTACK:
	 case Package_type::ACTION_REQUEST:

		 message_length = 4; //amount of chars in NAME_package, only header

		 break;


	case Package_type::QUIT:

		quit_package = new QUIT_package(package_code);
		message_length = quit_package->get_package_length();
		package_to_be_send[0] = (char)quit_package->get_package_header();
		this->expected_ack_id = 0;
		break;

	case Package_type::ERROR1:
		break;

	default:  //here arrives the packages that only have headers

		message_length = 1;

		break;
	}



	size_t len;
	boost::system::error_code error;
	
	do
	{
		len = socket->write_some(boost::asio::buffer((char *)&package_received, message_length), error);
	} 
	while ((error.value() == WSAEWOULDBLOCK));

	if (error)
		std::cout << "Error while trying to send message. " << error.message() << std::endl;
}

/*****************************************
***********receiveMessage*****************
******************************************
sendMessage INCREMENTA EL COUNT y luego envia el mensaje a una sola maquina en espefico.

INPUT:
void.
OUTPUT:
void.
*/
bool Communication::receiveMessage() {
	//startConnectionForServer();

	Package * package_received;
	bool returned = false;
	boost::system::error_code error;	

	char buf[100];		// por donde recibire el input. 20 chars maximo por el protocolo

	size_t len = 0;


	len = socket->read_some(boost::asio::buffer(buf), error);			//leo el input que me envia la otra maquina									
	
	if (error.value() == WSAEWOULDBLOCK) {
		//no leyo nada!!
		std::cout << "NOREAD " << error.message() << std::endl;
		returned = false;
	}
	else if (!error) {
		buf[len] = '\0';
		Package_type type = (Package_type) buf[0];
		Package * pack;
		uint32_t * posible_id;
		uint16_t * worm_pos;
		uint32_t * ID;
		switch (type)
		{
		case Package_type::ACK:
			
			Package * package_received = new ACK_package;

			break;

			case Package_type::NAME_IS:

			Package * package_received = new NAME_IS_package;

			break;

		case Package_type::I_AM_READY:
			worm_pos = (uint16_t*)(&buf[1]);
			pack = new I_AM_READY_package(type, *worm_pos);
			break;
		case Package_type::MOVE:
			ID = (uint32_t*)(&buf[2]);
			pack = new MOVE_package(type, (Move_type)buf[1], *ID);
			received_id = ((MOVE_package *)pack)->get_ID();
			break;
		case Package_type::QUIT:
			pack = new QUIT_package(type);
			break;
		case Package_type::ERROR1:
			pack = new ERROR_package(type);
			break;
		case Package_type::NONE:
			break;
		}
		this->received_package = pack;
		
		parseMessage();
		returned = true;
	}
	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;

	return returned;

}

/***************************************
***********parseMessage*****************
****************************************

INPUT:
	void.
OUTPUT:
*/
void Communication::parseMessage() {
	
	notify_obs();

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