#pragma once
#include "Package.h"
#include <cstring>

enum class Event_type  //Events that are use by the internal function of the program like during FSM
{
	END_OF_TABLE,

	//ACK:
	ACK,

	//QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	QUIT,

	//LOCAL_ACTION: Evento generado por allegro pero no ejecutado por la maquina,falta analizar
	MOVE,

	//EXTERN_ACTION   Es un MOVE/ATTACK del servidor que llega por networking siendo cliente
	ATTACK,  

	//ACTION_REQUEST   //action request generado por el cliente que no fue chequeado
	ACTION_REQUEST,

	//ERROR: Evento de software cuando se produce un error interno, diversos origenes
	ERROR1,

	//NAME_IS: 
	NAME_IS,

	//NAME:
	NAME,

	//MAP_IS:
	MAP_IS,

	//ENEMY_ACTION: El servidor crea una enemy action
	ENEMY_ACTION,

	//ENEMYS_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	ENEMYS_LOADED,

	//GAME_START:
	GAME_START,

	//WE_WON
	WE_WON,

	//PLAY_AGAIN
	PLAY_AGAIN,

	//FINISHED_LEVEL
	FINISHED_LEVEL,

	//GAME_OVER
	GAME_OVER,

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	START_COMMUNICATION,

	NO_EVENT

};


class EventPackage
{
public:
	EventPackage(Event_type event, bool is_local);

	void this_event_package_is_correct(bool value);  //sets if the EV represents a valid action
	bool is_this_a_valid_action();                  
	bool is_this_a_local_action();
	
	Event_type give_me_your_event_type();


protected:
	Event_type my_internal_event; //why it has a by deafult value?
	bool valid_action; //analyzed by the program if it´s a valid action
	bool local_action; 


};

/******************************************************************************
*******************************************************************************
							ACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACK_EventPackage : public EventPackage
{
public:
	ACK_EventPackage(bool is_local);

};

/******************************************************************************
*******************************************************************************
						QUIT_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class QUIT_EventPackage : public EventPackage
{
public:
	QUIT_EventPackage(bool is_local);

};

/******************************************************************************
*******************************************************************************
							MOVE_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class MOVE_EventPackage : public EventPackage, public MOVE_package
{
public:
	MOVE_EventPackage(bool is_local, Character_type the_one_that_moves, char fil_de, char col_de);


};

/******************************************************************************
*******************************************************************************
							ATTACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ATTACK_EventPackage : public EventPackage, public ATTACK_package
{
public:
	ATTACK_EventPackage(bool is_local, Character_type the_one_that_moves, char fil_de, char col_de);

};


/******************************************************************************
*******************************************************************************
					ACTION_REQUEST_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_EventPackage : public EventPackage, public ACTION_REQUEST_package
{
public:
	ACTION_REQUEST_EventPackage(bool is_local, Action_type the_action, char fil_de, char col_de);



};


/******************************************************************************
*******************************************************************************
							ERROR_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ERROR_EventPackage : public EventPackage
{
public:
	ERROR_EventPackage(bool is_local);

};


/******************************************************************************
*******************************************************************************
							NAME_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_EventPackage : public EventPackage
{
public:
	NAME_EventPackage(bool is_local);

};

/******************************************************************************
*******************************************************************************
							NAME_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class NAME_IS_EventPackage : public EventPackage, public NAME_IS_package
{
public:
	NAME_IS_EventPackage(bool is_local, uchar namelenght, char * newname);


};




/******************************************************************************
*******************************************************************************
							MAP_IS_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class MAP_IS_EventPackage : public EventPackage, public MAP_IS_package
{
public:
	MAP_IS_EventPackage(bool is_local, char * themap,char checksum);

};

/******************************************************************************
*******************************************************************************
							ENEMY_ACTION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMY_ACTION_EventPackage : public EventPackage, public ENEMY_ACTION_package
{
public:
	ENEMY_ACTION_EventPackage(bool is_local,uchar the_MonsterID, Action_type the_action, char fil_de, char col_de);

};


/******************************************************************************
*******************************************************************************
				GAME_START_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class GAME_START_EventPackage : public EventPackage
{
public:
	GAME_START_EventPackage(bool is_local);

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
	WE_WON_EventPackage(bool is_local);

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
	PLAY_AGAIN_EventPackage(bool is_local);

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
	GAME_OVER_EventPackage(bool is_local);

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
	START_COMMUNICATION_EventPackage(bool is_local);

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
	NO_EVENT_EventPackage(bool is_local);

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
	END_OF_TABLE_EventPackage(bool is_local);

private:

};
