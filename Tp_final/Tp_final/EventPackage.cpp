#include "EventPackage.h"

/******************************************************************************
*******************************************************************************
			EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************

/**************************************************************
				EventPackage CONSTRUCTOR
**************************************************************/
/*
*This function is the constructor of a package.
*
*INPUT:
*It receives the type of package.
*
*OUTPUT:
*Void
*/
EventPackage::EventPackage(Event_type event, bool is_local = NULL)
{
	this->my_internal_event = event;
	this->local_action = is_local;

}


/**************************************************************
				give_me_your_event_type
**************************************************************/
/*
*GETTER.This function returns the package header type.
*
*INPUT:
*Void
*
*OUTPUT:
*The package header type
*/
Event_type EventPackage::give_me_your_event_type()
{
	return this->my_internal_event;
}

/**************************************************************
				is_this_a_local_action
**************************************************************/

bool EventPackage::is_this_a_local_action() {

	return this->local_action;
}


/******************************************************************************
*******************************************************************************
			Action_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			Action_EventPackage CONSTRUCTOR
**************************************************************/
Action_EventPackage::Action_EventPackage(unsigned char fil_de=NULL, unsigned char col_de=NULL) {

	this->destination_row = fil_de;
	this->destination_column = col_de;
}

Action_EventPackage::Action_EventPackage(Direction_type direction_type= Direction_type::None) {

	this->my_direction = direction_type;
}


/**************************************************************
					give_me_your_destination_row 
**************************************************************/
unsigned char Action_EventPackage::give_me_your_destination_row() {
	return this->destination_row;
}
/**************************************************************
					give_me_your_destination_column
**************************************************************/
unsigned char Action_EventPackage::give_me_your_destination_column() {
	return this->destination_column;

}
/**************************************************************
					set_destination_row
**************************************************************/
void Action_EventPackage::set_destination_row(unsigned char my_destination_row) {

	this->destination_row = my_destination_row;
}
/**************************************************************
					set_destination_column
**************************************************************/
void Action_EventPackage::set_destination_column(unsigned char my_destination_column) {

	this->destination_column = my_destination_column;

}
/**************************************************************
				give_me_your_direction
**************************************************************/
Direction_type Action_EventPackage::give_me_your_direction() {

	return this->my_direction;
}
/**************************************************************
					set_direction 
**************************************************************/
void Action_EventPackage::set_direction(Direction_type new_direction) {
	this->my_direction = new_direction;

}
/******************************************************************************
*******************************************************************************
			ACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACK_EventPackage_CONSTRUCTOR
**************************************************************/
ACK_EventPackage::ACK_EventPackage() :EventPackage(Event_type::ACK) {


}

/******************************************************************************
*******************************************************************************
			LOCAL_QUIT_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_QUIT_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_QUIT_EventPackage::LOCAL_QUIT_EventPackage() :EventPackage(Event_type::LOCAL_QUIT) {

}

/******************************************************************************
*******************************************************************************
			EXTERN_QUIT_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_QUIT_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_QUIT_EventPackage::EXTERN_QUIT_EventPackage() :EventPackage(Event_type::EXTERN_QUIT) {

}


/******************************************************************************
*******************************************************************************
			MOVE_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MOVE_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Direction_type direction_type) :EventPackage(Event_type::MOVE,  true), Action_EventPackage(direction_type) { //LOCAL MOVE

}
/**************************************************************
			MOVE_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::MOVE, false),Action_EventPackage(fil_de,col_de) {			//EXTERN MOVE


}
/**************************************************************
			MOVE_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Character_type my_character,unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::MOVE, false), Action_EventPackage(fil_de, col_de) {			//EXTERN MOVE

	this->character = my_character;

}



/**************************************************************
				give_me_the_character
**************************************************************/
Character_type MOVE_EventPackage::give_me_the_character() {

	return this->character;
}
/**************************************************************
					set_character (LOCAL)
**************************************************************/
void MOVE_EventPackage::set_character(Character_type the_one_that_moves) {
	this->character = the_one_that_moves;

}

Character_type MOVE_package::give_me_the_character() {
	return this->character;
}


/******************************************************************************
*******************************************************************************
			ATTACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ATTACK_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage():EventPackage(Event_type::ATTACK, true), Action_EventPackage(Direction_type::None) {


}
/**************************************************************
			ATTACK_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::ATTACK, false), Action_EventPackage(fil_de, col_de) {


}
/**************************************************************
			ATTACK_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(Character_type my_character, unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::ATTACK, false), Action_EventPackage(fil_de, col_de) {

	this->character = my_character;

}



/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, Direction_type direction ) : EventPackage(Event_type::ACTION_REQUEST, true), Action_EventPackage(direction) { //local ACTION_REQUEST

	this->action = the_action;
}
/**************************************************************
			ACTION_REQUEST_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, char fil_de, char col_de) : EventPackage(Event_type::ACTION_REQUEST, false), Action_EventPackage(fil_de, col_de) { //extern ACTION_REQUEST

	this->action = the_action;

}

/**************************************************************
					give_me_the_action
**************************************************************/
Action_type ACTION_REQUEST_EventPackage::give_me_the_action() {
	return this->action;
}


/******************************************************************************
*******************************************************************************
			ERROR_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ERROR_EventPackage CONSTRUCTOR
**************************************************************/
ERROR_EventPackage::ERROR_EventPackage(bool is_local) :EventPackage(Event_type::ERROR1) {

	this->local_error = is_local;

}

/**************************************************************
				is_this_a_local_error
**************************************************************/
/*
*GETTER.This function returns the information to be send by networking.
*
*INPUT:
*Void
*
*OUTPUT:
*The information to be send by networking
*/
bool ERROR_EventPackage::is_this_a_local_error() {

	return this->local_error;
}

/******************************************************************************
*******************************************************************************
			NAME_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
				NAME_EventPackage
**************************************************************/
NAME_EventPackage::NAME_EventPackage() :EventPackage(Event_type::NAME) {

}


/******************************************************************************
*******************************************************************************
			NAME_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			NAME_IS_EventPackage CONSTRUCTOR
**************************************************************/
NAME_IS_EventPackage::NAME_IS_EventPackage(bool is_local , uchar namelenght, const char * newname) 
	:EventPackage(Event_type::NAME_IS,is_local), NAME_IS_package(namelenght,newname){



}


/******************************************************************************
*******************************************************************************
			MAP_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MAP_IS_EventPackage CONSTRUCTOR
**************************************************************/
MAP_IS_EventPackage::MAP_IS_EventPackage(bool is_local,  const char * themap, char checksum) :EventPackage(Event_type::MAP_IS, is_local), MAP_IS_package(themap,checksum){


}

/******************************************************************************
*******************************************************************************
			ENEMY_ACTION_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ENEMY_ACTION_EventPackage CONSTRUCTOR
**************************************************************/
ENEMY_ACTION_EventPackage::ENEMY_ACTION_EventPackage(bool is_local, uchar the_MonsterID, Action_type the_action, char fil_de, char col_de) 
	:EventPackage(Event_type::ENEMY_ACTION, is_local) {

	this->MonsterID = the_MonsterID;
	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;
}
uchar ENEMY_ACTION_EventPackage::give_me_the_monsterID() {
	return this->MonsterID;
}

Action_type ENEMY_ACTION_EventPackage::give_me_the_action() {
	return this->action;
}

char ENEMY_ACTION_EventPackage::give_me_the_destination_row() {
	return this->destination_row;

}
char ENEMY_ACTION_EventPackage::give_me_the_destination_column() {
	return this->destination_column;

}
/******************************************************************************
*******************************************************************************
			ENEMYS_LOADED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ENEMYS_LOADED_EventPackage CONSTRUCTOR
**************************************************************/
ENEMYS_LOADED_EventPackage::ENEMYS_LOADED_EventPackage():EventPackage(Event_type::ENEMYS_LOADED) {

}

/**************************************************************
			GAME_START_EventPackage
**************************************************************/
GAME_START_EventPackage::GAME_START_EventPackage() :EventPackage(Event_type::GAME_START) {


}

/**************************************************************
			WE_WON_EventPackage
**************************************************************/
WE_WON_EventPackage::WE_WON_EventPackage() :EventPackage(Event_type::WE_WON) {


}

/**************************************************************
			PLAY_AGAIN_EventPackage
**************************************************************/
PLAY_AGAIN_EventPackage::PLAY_AGAIN_EventPackage() :EventPackage(Event_type::PLAY_AGAIN) {


}

/**************************************************************
		GAME_OVER_EventPackage CONSTRUCTOR
**************************************************************/
GAME_OVER_EventPackage::GAME_OVER_EventPackage() :EventPackage(Event_type::GAME_OVER) {


}

/**************************************************************
		START_COMMUNICATION_EventPackage CONSTRUCTOR
**************************************************************/
START_COMMUNICATION_EventPackage::START_COMMUNICATION_EventPackage() :EventPackage(Event_type::START_COMMUNICATION) {


}

/**************************************************************
		FINISHED_LEVEL_EventPackage CONSTRUCTOR
**************************************************************/
FINISHED_LEVEL_EventPackage::FINISHED_LEVEL_EventPackage() :EventPackage(Event_type::FINISHED_LEVEL) {


}

/**************************************************************
		NO_EVENT_EventPackage CONSTRUCTOR
**************************************************************/
NO_EVENT_EventPackage::NO_EVENT_EventPackage() :EventPackage(Event_type::NO_EVENT) {


}

/**************************************************************
		END_OF_TABLE_EventPackage CONSTRUCTOR
**************************************************************/
END_OF_TABLE_EventPackage::END_OF_TABLE_EventPackage() :EventPackage(Event_type::END_OF_TABLE) {


}


















