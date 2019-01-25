#include "Communication.h"



Communication::Communication(Userdata * my_user_data) :Observable(Observable_type::COMMUNICATION)
{
	this->IO_handler = new boost::asio::io_service();					//Creation of the common necessary objetcs for connection
	this->socket = new boost::asio::ip::tcp::socket(*this->IO_handler);
	
	Connecting_as_a_client(my_user_data->my_network_data.give_me_my_ip(), my_user_data);  //First the program try to start as a client

	
	if(!(my_user_data->my_network_data.is_client())) //me fijo si logre conectarme como cliente
	{
		Connecting_as_a_server(my_user_data);
	}

}

Communication::~Communication()
{
	acceptor->close();
	socket->close();
	delete client_resolver;
	delete acceptor;
	delete socket;
	delete IO_handler;
	
}

/******************************
	Connecting_as_a_client
/******************************
************************
*******************************
The process of trying to connect as a client is done here.

INPUT:
	The ip that it´s gonna be use by the client to connect
OUTPUT:
	void.
*/
void Communication::Connecting_as_a_client(std::string host, Userdata * my_user_data) {

	this->client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	this->endpoint = client_resolver->resolve( boost::asio::ip::tcp::resolver::query(host, SNOWBORS_PORT_STR));

	boost::system::error_code error;  //If the program can´t connect with the client boost throws an exception, we catch it here

	std::cout << "Trying to connect to " << host << " on port " << SNOWBORS_PORT_STR << std::endl;	//Debugging

	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;

	srand(time(NULL));
	unsigned int N = (rand() % 3000) + 2000; //Generation of a random number between 2000 and 5000
	std::cout << N << std::endl;

	do
	{
		boost::asio::connect(*socket, endpoint, error);
		socket->non_blocking(true);


		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e6;
			pastTime = currentTime;
			std::cout << "Pasaron " << elapsedSeconds << " segundos." << std::endl;
		}


	} while (error && elapsedSeconds < N);


	if (elapsedSeconds > 10)
		std::cout << "Pasaron más de " << elapsedSeconds << " segundos." << std::endl;

	if (error)
	{
		std::cout << "Error al intentar conectar como cliente" << std::endl;		//Debugging
		my_user_data->my_network_data.set_client(false);
	}
	else
		my_user_data->my_network_data.set_client(true);


};


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
***********Connecting_as_a_server****************
******************************************
startConnectionForClient inicia la conexión con maquina siendo cliente.

INPUT:
	void.
OUTPUT:
	bool:.
*/
void Communication::Connecting_as_a_server(Userdata * my_user_data) {
	
	//renewClientItems();
	boost::system::error_code error;  //If the program can´t connect with the server boost throws an exception, we catch it here

	this->acceptor = new boost::asio::ip::tcp::acceptor(*this->IO_handler, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SNOWBORS_PORT));
	
	this->acceptor->accept(*this->socket,error);
	this->socket->non_blocking(true);

	if (error)
		this->healthy_connection = false;
	else
		my_user_data->my_network_data.set_client(false);
	
}


/*****************************************
***********sendMessage********************
******************************************
sendMessage - Receives a package and makes the convertion to send it by networking

INPUT:
	Package *
OUTPUT:
	void
*/
void Communication::sendMessage(Package * package_received) {

	//startConnectionForClient(his_ip.c_str());

	size_t len;
	boost::system::error_code error;
	
	do
	{ //first parameter should be char [n] not char *, possible source of error
		len = socket->write_some(boost::asio::buffer(package_received->get_sendable_info(), package_received->get_info_length()), error); 
	} 
	while ((error.value() == WSAEWOULDBLOCK));

	if (error)
	{
		this->healthy_connection = false;
		std::cout << "Error while trying to send message. " << error.message() << std::endl;
	}
	delete package_received;

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

	do
	{
		len = socket->read_some(boost::asio::buffer(buf), error);			//leo el input que me envia la otra maquina		

	} while (error.value() == WSAEWOULDBLOCK); //NO DEBERÍA LOOPEAR, NO SALE NUNCA SI NO LE LLEGA EL MENSAJE, BLOQUEANTE, PARA ESO ESTÁ EL ALLEGRO TIMER

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

			package_received = new MAP_IS_package(&buf[1], buf[193]);

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

		case Package_type::ERROR1: //An error that was received by networking

			package_received = new ERROR_package;

			break;

		default:  //The program received an unknown header package, thus it´S considered that the package is corrupted

			this->healthy_connection = false; 
			package_received = new ERROR_package;
			break;

		}
	}

	else 
	{
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
		//this->healthy_connection = false; NO ES ERROR NECESARIAMENTE
	}

	return package_received;
}




void Communication::renewClientItems() {
	if(socket != NULL )
		delete socket;
	if (IO_handler != NULL)
		delete IO_handler;
	if (client_resolver != NULL)
		delete client_resolver;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
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
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), SNOWBORS_PORT));
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

}


uint32_t Communication::get_expected_id() {
	return expected_ack_id;
}



bool Communication::is_the_connection_healthy()
{
	return this->healthy_connection;
}
