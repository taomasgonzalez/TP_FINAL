#pragma once

#include "Userdata.h"

#include <stdint.h> 
#include <string>
#include "Action_Info.h"

typedef unsigned int uint;
typedef unsigned char uchar;
using namespace std;


enum class Event_type  //Events that are usde by the internal function of the program 
{
	END_OF_TABLE,

	//ACK:
	ACK,

	//LOCAL_QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	LOCAL_QUIT,

	//EXTERN_QUIT:Evento de networking de quit
	EXTERN_QUIT,

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

	NO_EVENT,

	//graphic events
	FPS_TICKED,
	APPEARED,
	DISAPPEARED,
	FINISHED_DRAWING,
	CHANGE_LEVEL,

	//character events
	JUMPED,
	JUMPED_FORWARD,
	WALKED,
	ATTACKED,
	FELL,
	PUSHED,
	FINISHED_MOVEMENT,
	FINISHED_ATTACK,
	DIED,

	//player events
	REVIVED,
	STOP_INMUNITY,

	//enemy and proyectiles events
	GOT_HIT,
	GOT_SMASHED,

	//enemy events
	FROZE,
	UNFROZE,
	UNFREEZE,
	PARTIALLY_UNFROZE,
	PARTIALLY_FROZE,
	BOUNCE,
	ROLLING,
	CHARGING,
	SNOWBALL_BREAKDOWN,
	//RESET(DEBUGGING)
	RESET,
	FINISHED_GRAPH_STEP

};

class Numbered_EventPackage
{
public:
	Numbered_EventPackage(uint16_t ID);

	uint16_t give_me_your_package_ID();
	void set_your_package_ID(uint16_t ID);


private:
	uint16_t package_ID = 0;

};

class EventPackage: public Numbered_EventPackage
{
public:
	EventPackage(Event_type event, uint16_t ID, bool is_local );
	EventPackage(Action_info * info_checked);
	virtual ~EventPackage();

	Event_type give_me_your_event_type();
	bool is_this_a_local_action();
	virtual Action_info to_Action_info();

protected:
	Event_type my_internal_event;
	bool local_action = true;

};

class Action_EventPackage
{
public:
	Action_EventPackage(unsigned char fil_de, unsigned char col_de, Direction_type direction_type);
	Action_EventPackage(Direction_type direction_type);

	unsigned char give_me_your_destination_row();
	unsigned char give_me_your_destination_column();

	void set_destination_row(unsigned char my_destination_row);
	void set_destination_column(unsigned char my_destination_column);

	Item_type give_me_the_character();
	void set_character(Item_type the_one_that_moves);

	Direction_type give_me_your_direction();
	void set_direction(Direction_type new_direction = Direction_type::None);


private:
	unsigned char destination_row;
	unsigned char destination_column;
	Direction_type my_direction = Direction_type::None;
	Item_type character;
};




/******************************************************************************
*******************************************************************************
ACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACK_EventPackage : public EventPackage 
{
public:
	ACK_EventPackage(uint16_t ID, bool is_local);

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
RESET_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class RESET_EventPackage : public EventPackage
{
public:
	RESET_EventPackage(bool is_local);

};

/******************************************************************************
*******************************************************************************
MOVE_EventPackage CLASS
*******************************************************************************
*******************************************************************************/


class MOVE_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	MOVE_EventPackage(Direction_type direction_type, uint16_t ID); //local MOVE
	MOVE_EventPackage(unsigned char fil_de, unsigned char col_de, uint16_t ID);			//extern MOVE
	MOVE_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de, uint16_t ID);		//MOVE to be send by networking made from an AR
	MOVE_EventPackage(Action_info * my_info);
	MOVE_EventPackage(MOVE_EventPackage* moved);

	//to be completed when neeeded!!
	MOVE_EventPackage();

	//cualquier queja (que no sea de logica interna) quejarse a Tommy.
	virtual Action_info to_Action_info();

private:
};

/******************************************************************************
*******************************************************************************
ATTACK_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ATTACK_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	ATTACK_EventPackage(uint16_t ID); // local ATTACK
	ATTACK_EventPackage(unsigned char fil_de, unsigned char col_de, uint16_t ID);			//extern ATTACK
	ATTACK_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de, uint16_t ID);		//ATTACK to be send by networking made from an AR
	ATTACK_EventPackage(Action_info * mmy_info);
	ATTACK_EventPackage(ATTACK_EventPackage* moved);

	//cualquier queja (que no sea de logica interna) quejarse a Tommy.
	virtual Action_info to_Action_info();

private:

};


/******************************************************************************
*******************************************************************************
ACTION_REQUEST_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	ACTION_REQUEST_EventPackage(Action_type the_action, Direction_type direction, uint16_t ID); //local ACTION_REQUEST
	ACTION_REQUEST_EventPackage(Action_type the_action, unsigned char fil_de, unsigned  char col_de, uint16_t ID); //extern ACTION_REQUEST
	ACTION_REQUEST_EventPackage(Action_info* my_info);
	ACTION_REQUEST_EventPackage(ACTION_REQUEST_EventPackage* moved);

	Action_type give_me_the_action();
	virtual Action_info to_Action_info();

private:
	Action_type action;

};


/******************************************************************************
*******************************************************************************
ERROR_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class ERROR_EventPackage : public EventPackage
{
public:
	ERROR_EventPackage(bool is_local = true);

private:

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

class NAME_IS_EventPackage : public EventPackage
{
public:
	NAME_IS_EventPackage(bool is_local, uchar namelenght, std::string newname);
	uchar get_name_lenght();
	std::string give_me_your_name();

private:
	uchar count;
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
	MAP_IS_EventPackage(bool is_local, const unsigned char * themap, unsigned char checksum);
	const unsigned char * give_me_the_map();
	unsigned char give_me_the_checksum();

private:
	const unsigned char * map;
	unsigned char Checksum;
};

/******************************************************************************
*******************************************************************************
			ENEMY_ACTION_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMY_ACTION_EventPackage : public EventPackage, public Action_EventPackage
{
public:
	ENEMY_ACTION_EventPackage(bool is_local, uchar the_MonsterID, Action_type the_action, unsigned char fil_de, unsigned char col_de, uint16_t ID);
	ENEMY_ACTION_EventPackage(Action_info * ea_info);
	ENEMY_ACTION_EventPackage(ENEMY_ACTION_EventPackage* enemy_action);


	uchar give_me_the_monsterID();
	Action_type give_me_the_action();

	//cualquier queja (que no sea de logica interna) quejarse a Tommy.
	virtual Action_info to_Action_info();

private:
	uchar MonsterID;
	Action_type action;
};

/******************************************************************************
*******************************************************************************
ENEMYS_LOADED_EventPackage CLASS
*******************************************************************************
*******************************************************************************/

class ENEMYS_LOADED_EventPackage : public EventPackage
{
public:
	ENEMYS_LOADED_EventPackage();

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
	START_COMMUNICATION_EventPackage();

private:

};

/******************************************************************************
*******************************************************************************
FINISHED_LEVEL_EventPackage CLASS
*******************************************************************************
*******************************************************************************/
class FINISHED_LEVEL_EventPackage : public EventPackage
{
public:
	FINISHED_LEVEL_EventPackage();

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

class FINISHED_MOVEMENT_EventPackage : public EventPackage {
public:
	FINISHED_MOVEMENT_EventPackage();
private:
};

class WALKED_EventPackage : public EventPackage {
public:
	WALKED_EventPackage(Direction_type dir);
	WALKED_EventPackage(const WALKED_EventPackage* walked);

	Direction_type walking_direction;
};

class ATTACKED_EventPackage : public EventPackage {
public:
	ATTACKED_EventPackage();

	~ATTACKED_EventPackage();
};

class JUMPED_EventPackage : public EventPackage {
public:
	JUMPED_EventPackage();
	JUMPED_EventPackage(const JUMPED_EventPackage* walked);

private:
};

class JUMPED_FORWARD_EventPackage : public EventPackage {
public:
	JUMPED_FORWARD_EventPackage(Direction_type dir);
	JUMPED_FORWARD_EventPackage(const JUMPED_FORWARD_EventPackage* walked);

	Direction_type jumping_direction;
};

class DIED_EventPackage : public EventPackage {
public:
	DIED_EventPackage();
};

class FELL_EventPackage : public EventPackage {
public:
	FELL_EventPackage();
};


class FINISHED_ATTACK_EventPackage : public EventPackage {
public:
	FINISHED_ATTACK_EventPackage();
};

class GOT_HIT_EventPackage : public EventPackage {
public:
	GOT_HIT_EventPackage();
};


class PUSHED_EventPackage : public EventPackage {
public:
	PUSHED_EventPackage(Direction_type dir);
	~PUSHED_EventPackage();
	Direction_type pushing_direction;
};

class CHARGING_EventPackage : public EventPackage {
public:
	CHARGING_EventPackage();
	~CHARGING_EventPackage();

};


class PARTIALLY_UNFROZE_EventPackage : public EventPackage {
public:
	PARTIALLY_UNFROZE_EventPackage();
	~PARTIALLY_UNFROZE_EventPackage();

};

class PARTIALLY_FROZE_EventPackage : public EventPackage {
public:
	PARTIALLY_FROZE_EventPackage();
	~PARTIALLY_FROZE_EventPackage();

};

class UNFROZE_EventPackage : public EventPackage {
public:
	UNFROZE_EventPackage();
	~UNFROZE_EventPackage();
};

class UNFREEZE_EventPackage : public EventPackage {
public:
	UNFREEZE_EventPackage();
	~UNFREEZE_EventPackage();
};

class FROZE_EventPackage : public EventPackage {
public:
	FROZE_EventPackage();
	~FROZE_EventPackage();
};

class FINISHED_GRAPH_STEP_EventPackage : public EventPackage {
public:
	FINISHED_GRAPH_STEP_EventPackage();
	~FINISHED_GRAPH_STEP_EventPackage();
};

class REVIVE_EventPackage : public EventPackage {
public:
	REVIVE_EventPackage();
	~REVIVE_EventPackage();
};

class STOP_INMUNITY_EventPackage : public EventPackage {
public:
	STOP_INMUNITY_EventPackage();
	~STOP_INMUNITY_EventPackage();
};

class SNOWBALL_BREAKDOWN_EventPackage : public EventPackage {
public:
	SNOWBALL_BREAKDOWN_EventPackage();
	~SNOWBALL_BREAKDOWN_EventPackage();
};
