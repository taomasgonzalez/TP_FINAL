#pragma once
#include "Package.h"
#include "Scene.h"
#include "Communication.h"
#include "EventGenerator.h"
#include <cstring>
enum class Event_type  //Events that are use by the internal function of the program like during FSM
{
	
	/*
			EL MISMO TIPO DE EVENTO CON SUS SUBTIPOS PUEDEN SER METIDOS EN UN SOLO EVENTO CON VARIABLE DE CONTROL
			YO SÉ SI SOY CLIENTE O SI FUE CHEQUEADO O NO. CAMBIAR!!!!!!
	*/
	END_OF_TABLE,

	//ACK:
	ACK,

	//LOCAL_QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	LOCAL_QUIT,

	//EXTERN_QUIT: Evento que llega por networking del otro computador
	EXTERN_QUIT,

	//LOCAL_ACTION_REQUESTED: Evento generado por allegro pero no ejecutado por la maquina,falta analizar
	LOCAL_ACTION_REQUESTED,

	//LOCAL_ACTION: Evento generado por allegro y ya ejecutado por la maquina, debe ser enviado por networking
	LOCAL_ACTION_ACCEPTED,

	//LOCAL_ACTION_DENIED: Accion local rechazada, MUCHO QUE VER CON LA PARTE ANALÍTICA
	LOCAL_ACTION_DENIED,

	//EXTERN_ACTION_RECEIVED   Es un MOVE/ATTACK del servidor que llega por networking siendo cliente
	EXTERN_ACTION_RECEIVED,  

	//EXTERN_ACTION_REQUESTED: Evento que llega por networking y ya es chequeado
	EXTERN_ACTION_ACCEPTED,

	//EXTERN_ACTION_DENIED   Evento que llega por networking, fue chequeado y esta mal, hay que mandar ERROR
	EXTERN_ACTION_DENIED,

	//ACTION_REQUEST_REQUESTED    //action request generado por el cliente que no fue chequeado
	ACTION_REQUEST_REQUESTED,

	//ACTION_REQUEST_ACCEPTED	//action request generado por el cliente chequedo
	ACTION_REQUEST_ACCEPTED,

	//ACTION_REQUEST_DENIED //action request generado por el cliente inválido, se debe generar ERROR
	ACTION_REQUEST_DENIED,

	//ACTION_REQUEST_TO_BE_SEND action_request que va a ser enviado por el cliente
	ACTION_REQUEST_TO_BE_SEND,

	//EXTERN_ERROR: Evento de net cuando recibo un paquete de error, diversos origenes
	EXTERN_ERROR,

	//LOCAL_ERROR: Evento de software cuando se produce un error interno, diversos origenes
	LOCAL_ERROR,

	//NAME_IS: 
	NAME_IS,

	//EXTERN_NAME_IS: 
	EXTERN_NAME_IS,

	//NAME:
	NAME,

	//MAP_IS:
	MAP_IS,

	//MAP_IS_OK:
	MAP_IS_OK,

	//LOCAL_ENEMY_ACTION: El servidor crea una enemy action
	LOCAL_ENEMY_ACTION,

	//EXTERN_ENEMY_ACTION: Recibi un enemy action del servidor
	EXTERN_ENEMY_ACTION,

	//ENEMY_ACTION_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	ENEMY_ACTION_IS_OK,

	//GAME_START:
	GAME_START,

	//WE_WON
	WE_WON,

	//PLAY_AGAIN
	PLAY_AGAIN,

	//GAME_OVER
	GAME_OVER,

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	START_COMMUNICATION,

	NO_EVENT

};

struct PackageInfo //Information that is provided or is gonna me communicated by networking
{

	//PackageInfo(Package_type my_header, Scene * escenario, Communication* com, EventPackage* my_event_info);


	Package_type header;
	//NAME_IS
	uchar count;
	std::string Name; // without terminator
	//MAP_IS
	char * map;
	char Checksum;
	//MOVE - ATTACK
	Character_type character;
	char destination_row;
	char destination_col;
	// ACTION REQUEST
	Action_type action;
	// ENEMY_ACTION
	uchar MonsterID;

}; 




class EventPackage
{
public:
	EventPackage(Event_type event);

	Direction dir;

	void this_event_package_is_correct(bool value);
	bool is_this_a_valid_action();
	Event_type give_me_your_event_type();
	


protected:
	Event_type my_internal_event = Event_type::NO_EVENT;
	bool valid_action = false; //analyzed by the program if it´s a valid action


};

/******************************************************************************
*******************************************************************************
							ACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACK_EventPackage : public EventPackage
{
public:
	ACK_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
							LOCAL_QUIT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_QUIT_EventPackage : public EventPackage
{
public:
	LOCAL_QUIT_EventPackage();

};

/******************************************************************************
*******************************************************************************
							EXTERN_QUIT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_QUIT_EventPackage : public EventPackage
{
public:
	EXTERN_QUIT_EventPackage();

};

/******************************************************************************
*******************************************************************************
							LOCAL_ACTION_ACCEPTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_ACTION_ACCEPTED_EventPackage : public EventPackage
{
public:
	LOCAL_ACTION_ACCEPTED_EventPackage(Action_type my_action,Character_type the_one_that_moves, char fil_de, char col_de);
	Action_type give_me_the_move();
	Character_type give_me_the_character();
	char give_me_the_fil_de();
	char give_me_the_col_de();

private:
	Action_type my_move;
	Character_type the_one_that_moves;
	char fil_de; 
	char col_de;

};

/******************************************************************************
*******************************************************************************
							LOCAL_ACTION_REQUESTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_ACTION_REQUESTED_EventPackage : public EventPackage
{
public:
	LOCAL_ACTION_REQUESTED_EventPackage();

};


/******************************************************************************
*******************************************************************************
							LOCAL_ACTION_DENIED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_ACTION_DENIED_EventPackage : public EventPackage
{
public:
	LOCAL_ACTION_DENIED_EventPackage();

};

/******************************************************************************
*******************************************************************************
					EXTERN_ACTION_ACCEPTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_ACTION_ACCEPTED_EventPackage : public EventPackage
{
public:
	EXTERN_ACTION_ACCEPTED_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
					EXTERN_ACTION_RECEIVED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_ACTION_RECEIVED_EventPackage : public EventPackage
{
public:
	EXTERN_ACTION_RECEIVED_EventPackage(Action_type my_action, Character_type the_one_that_moves, char fil_de, char col_de);
	Action_type give_me_the_move();
	Character_type give_me_the_character();
	char give_me_the_fil_de();
	char give_me_the_col_de();

private:
	Action_type my_move;
	Character_type the_one_that_moves;
	char fil_de;
	char col_de;

};


/******************************************************************************
*******************************************************************************
					EXTERN_ACTION_DENIED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_ACTION_DENIED_EventPackage : public EventPackage
{
public:
	EXTERN_ACTION_DENIED_EventPackage();

};

/******************************************************************************
*******************************************************************************
					EXTERN_ACTION_ACCEPTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_ACTION_ACCEPTED_EventPackage : public EventPackage
{
public:
	EXTERN_ACTION_ACCEPTED_EventPackage();

};

/******************************************************************************
*******************************************************************************
					ACTION_REQUEST_REQUESTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_REQUESTED_EventPackage : public EventPackage
{
public:
	ACTION_REQUEST_REQUESTED_EventPackage();

};

/******************************************************************************
*******************************************************************************
					ACTION_REQUEST_ACCEPTED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_ACCEPTED_EventPackage : public EventPackage
{
public:
	ACTION_REQUEST_ACCEPTED_EventPackage();

	Action_type give_me_the_move();
	char give_me_the_fil_de();
	char give_me_the_col_de();

private:
	Action_type my_move;
	char fil_de;
	char col_de;

};


/******************************************************************************
*******************************************************************************
					ACTION_REQUEST_DENIED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_DENIED_EventPackage : public EventPackage
{
public:
	ACTION_REQUEST_DENIED_EventPackage();

};



/******************************************************************************
*******************************************************************************
							EXTERN_ERROR_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class EXTERN_ERROR_EventPackage : public EventPackage
{
public:
	EXTERN_ERROR_EventPackage();

};

/******************************************************************************
*******************************************************************************
							LOCAL_ERROR_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class LOCAL_ERROR_EventPackage : public EventPackage
{
public:
	LOCAL_ERROR_EventPackage();

};


/******************************************************************************
*******************************************************************************
							NAME_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_EventPackage : public EventPackage
{
public:
	NAME_EventPackage();



};

/******************************************************************************
*******************************************************************************
							NAME_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_IS_EventPackage : public EventPackage
{
public:
	NAME_IS_EventPackage(Communication* com);
	char * give_me_your_name();
	uchar give_me_your_name_length();

private:
	std::string Name; // without terminator

};

/******************************************************************************
*******************************************************************************
							EXTERN_NAME_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class EXTERN_NAME_IS_EventPackage : public EventPackage
{
public:
	EXTERN_NAME_IS_EventPackage(char * his_name);
	char * give_me_your_name();
	uchar give_me_your_name_length();

private:
	std::string Name; // without terminator

};


/******************************************************************************
*******************************************************************************
							MAP_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class MAP_IS_EventPackage : public EventPackage
{
public:
	MAP_IS_EventPackage(const char * themap);
	char * give_me_the_map();
	char give_me_the_checksum();

private:
	char * map;
	char Checksum = 0;
};

/******************************************************************************
*******************************************************************************
							MAP_IS_OK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class MAP_IS_OK_EventPackage : public EventPackage
{
public:
	MAP_IS_OK_EventPackage(char * themap);
	char * give_me_the_map();
	char give_me_the_checksum();

private:
	char * map;
	char Checksum = 0;
};

/******************************************************************************
*******************************************************************************
							LOCAL_ENEMY_ACTION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class LOCAL_ENEMY_ACTION_EventPackage : public EventPackage
{
public:
	LOCAL_ENEMY_ACTION_EventPackage(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de);
	uchar give_me_the_monsterID();
	Action_type give_me_the_action();
	char give_me_the_destination_row();
	char give_me_the_destination_column();

private:
	uchar MonsterID;
	Action_type action;
	char destination_row;
	char destination_column;
};

/******************************************************************************
*******************************************************************************
							EXTERN_ENEMY_ACTION CLASS
*******************************************************************************
*******************************************************************************/

class EXTERN_ENEMY_ACTION_EventPackage : public EventPackage
{
public:
	EXTERN_ENEMY_ACTION_EventPackage(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de);
	uchar give_me_the_monsterID();
	Action_type give_me_the_action();
	char give_me_the_destination_row();
	char give_me_the_destination_column();



private:

};

/******************************************************************************
*******************************************************************************
				ENEMY_ACTION_IS_OK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMY_ACTION_IS_OK_EventPackage : public EventPackage
{
public:
	ENEMY_ACTION_IS_OK_EventPackage();


private:

};

/******************************************************************************
*******************************************************************************
				GAME_START_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class GAME_START_EventPackage : public EventPackage
{
public:
	GAME_START_EventPackage();

private:

};


/******************************************************************************
*******************************************************************************
							WE_WON_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class WE_WON_EventPackage : public EventPackage
{
public:
	WE_WON_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
							PLAY_AGAIN_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class PLAY_AGAIN_EventPackage : public EventPackage
{
public:
	PLAY_AGAIN_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
						GAME_OVER_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class GAME_OVER_EventPackage : public EventPackage
{
public:
	GAME_OVER_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
						START_COMMUNICATION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class START_COMMUNICATION_EventPackage : public EventPackage
{
public:
	START_COMMUNICATION_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
						NO_EVENT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class NO_EVENT_EventPackage : public EventPackage
{
public:
	NO_EVENT_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
						END_OF_TABLE_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class END_OF_TABLE_EventPackage : public EventPackage
{
public:
	END_OF_TABLE_EventPackage();

private:

};
