#include "EventPackage.h"



PackageInfo::PackageInfo(Package_type my_header, Scene * escenario, Communication* com, EventPackage* my_event_info)
{
	this->header = my_header;

	switch (my_header)
	{
	case Package_type::NAME_IS:
		this->Name = com->give_me_my_name();
		break;

	case Package_type::MAP_IS:
		this->map = escenario->give_me_the_original_map();
		break;

	case Package_type::MOVE:
	case Package_type::ATTACK:
		this->character = my_event_info->my_info->character;
		this->destination_row = my_event_info->my_info->destination_row;
		this->destination_col = my_event_info->my_info->destination_col;

		break;

	case Package_type::ACTION_REQUEST:
		this->action = my_event_info->my_info->action;
		this->destination_row = my_event_info->my_info->destination_row;
		this->destination_col = my_event_info->my_info->destination_col;
		break;

	case Package_type::ENEMY_ACTION:
		this->MonsterID = my_event_info->my_info->MonsterID;
		this->action = my_event_info->my_info->action;
		this->destination_row = my_event_info->my_info->destination_row;
		this->destination_col = my_event_info->my_info->destination_col;
		break;

	}

}



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
EventPackage::EventPackage(Event_type event)
{
	this->my_internal_event = event;


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
				is_this_a_valid_action
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
bool EventPackage::is_this_a_valid_action()
{
	return this->valid_action;
}

/**************************************************************
				this_event_package_is_correct
**************************************************************/
/*
*GETTER.This function returns the lenght of the information to be
*send by networking.
*
*INPUT:
*Void
*
*OUTPUT:
*The lenght of the information to be send by networking.
*/
void EventPackage::this_event_package_is_correct(bool value) 
{
	 this->valid_action=value;
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
			LOCAL_ACTION_ACCEPTED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_ACTION_ACCEPTED_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_ACTION_ACCEPTED_EventPackage::LOCAL_ACTION_ACCEPTED_EventPackage(Action_type my_action, Character_type the_one_that_moves, char fil_de, char col_de) :EventPackage(Event_type::LOCAL_ACTION_ACCEPTED) {

	this->my_move = my_action;
	this->the_one_that_moves = the_one_that_moves;
	this->fil_de = fil_de;
	this->col_de = col_de;


}

/**************************************************************
				give_me_the_character
**************************************************************/
Character_type LOCAL_ACTION_ACCEPTED_EventPackage::give_me_the_character() {

	return this->the_one_that_moves;
}

/**************************************************************
				give_me_the_move 
**************************************************************/
Action_type LOCAL_ACTION_ACCEPTED_EventPackage::give_me_the_move() {

	return this->my_move;
}
/**************************************************************
				give_me_the_fil_de
**************************************************************/
char LOCAL_ACTION_ACCEPTED_EventPackage::give_me_the_fil_de() {

	return this->fil_de;
}
/**************************************************************
				give_me_the_col_de
**************************************************************/
char LOCAL_ACTION_ACCEPTED_EventPackage::give_me_the_col_de() {

	return this->col_de;

}


/******************************************************************************
*******************************************************************************
			LOCAL_ACTION_REQUESTED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_ACTION_REQUESTED_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_ACTION_REQUESTED_EventPackage::LOCAL_ACTION_REQUESTED_EventPackage() :EventPackage(Event_type::LOCAL_ACTION_REQUESTED) {



}


/******************************************************************************
*******************************************************************************
			LOCAL_ACTION_DENIED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_ACTION_DENIED_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_ACTION_DENIED_EventPackage::LOCAL_ACTION_DENIED_EventPackage() :EventPackage(Event_type::LOCAL_ACTION_DENIED) {



}

/******************************************************************************
*******************************************************************************
			EXTERN_ACTION_ACCEPTED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ACTION_ACCEPTED_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ACTION_ACCEPTED_EventPackage::EXTERN_ACTION_ACCEPTED_EventPackage() :EventPackage(Event_type::EXTERN_ACTION_ACCEPTED) {


}


/******************************************************************************
*******************************************************************************
			EXTERN_ACTION_RECEIVED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ACTION_RECEIVED_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ACTION_RECEIVED_EventPackage::EXTERN_ACTION_RECEIVED_EventPackage(Action_type my_action, Character_type the_one_that_moves, char fil_de, char col_de) :EventPackage(Event_type::EXTERN_ACTION_RECEIVED) {

	this->my_move = my_action;
	this->the_one_that_moves = the_one_that_moves;
	this->fil_de = fil_de;
	this->col_de = col_de;

}
/**************************************************************
				give_me_the_character
**************************************************************/
Character_type EXTERN_ACTION_RECEIVED_EventPackage::give_me_the_character() {

	return this->the_one_that_moves;
}

/**************************************************************
				give_me_the_move
**************************************************************/
Action_type EXTERN_ACTION_RECEIVED_EventPackage::give_me_the_move() {

	return this->my_move;
}
/**************************************************************
				give_me_the_fil_de
**************************************************************/
char EXTERN_ACTION_RECEIVED_EventPackage::give_me_the_fil_de() {

	return this->fil_de;
}
/**************************************************************
				give_me_the_col_de
**************************************************************/
char EXTERN_ACTION_RECEIVED_EventPackage::give_me_the_col_de() {

	return this->col_de;

}

/******************************************************************************
*******************************************************************************
			EXTERN_ACTION_DENIED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ACTION_DENIED_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ACTION_DENIED_EventPackage::EXTERN_ACTION_DENIED_EventPackage() :EventPackage(Event_type::EXTERN_ACTION_DENIED) {



}

/******************************************************************************
*******************************************************************************
			EXTERN_ACTION_ACCEPTED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ACTION_ACCEPTED_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ACTION_ACCEPTED_EventPackage::EXTERN_ACTION_ACCEPTED_EventPackage() :EventPackage(Event_type::EXTERN_ACTION_ACCEPTED) {



}

/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_RECIEVED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_RECIEVED_EventPackage CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_RECIEVED_EventPackage::ACTION_REQUEST_RECIEVED_EventPackage(Action_type the_action, char fil_de, char col_de) :EventPackage(Event_type::ACTION_REQUEST_RECIEVED) {

	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}
Action_type ACTION_REQUEST_RECIEVED_EventPackage::give_me_the_action() {

	return this->action;
}
char ACTION_REQUEST_RECIEVED_EventPackage::give_me_the_destination_row() {

	return this->destination_row;

}
char ACTION_REQUEST_RECIEVED_EventPackage::give_me_the_destination_column() {

	return this->destination_column;

}

/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_ACCEPTED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_ACCEPTED_EventPackage CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_ACCEPTED_EventPackage::ACTION_REQUEST_ACCEPTED_EventPackage() :EventPackage(Event_type::ACTION_REQUEST_ACCEPTED) {



}

/**************************************************************
				give_me_the_move
**************************************************************/
Action_type ACTION_REQUEST_ACCEPTED_EventPackage::give_me_the_move() {

	return this->my_move;
}
/**************************************************************
				give_me_the_fil_de
**************************************************************/
char ACTION_REQUEST_ACCEPTED_EventPackage::give_me_the_fil_de() {

	return this->fil_de;
}
/**************************************************************
				give_me_the_col_de
**************************************************************/
char ACTION_REQUEST_ACCEPTED_EventPackage::give_me_the_col_de() {

	return this->col_de;

}
/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_DENIED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_DENIED_EventPackage CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_DENIED_EventPackage::ACTION_REQUEST_DENIED_EventPackage() :EventPackage(Event_type::ACTION_REQUEST_DENIED) {



}

/******************************************************************************
*******************************************************************************
			EXTERN_ERROR_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ERROR_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ERROR_EventPackage::EXTERN_ERROR_EventPackage() :EventPackage(Event_type::EXTERN_ERROR) {



}

/******************************************************************************
*******************************************************************************
			LOCAL_ERROR_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_ERROR_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_ERROR_EventPackage::LOCAL_ERROR_EventPackage() :EventPackage(Event_type::LOCAL_ERROR) {



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
NAME_IS_EventPackage::NAME_IS_EventPackage(Communication* com) :EventPackage(Event_type::NAME_IS) {

	this->Name = com->give_me_my_name();

}

char * NAME_IS_EventPackage::give_me_your_name() {

	return (char *)(this->Name.data());
}

uchar NAME_IS_EventPackage::give_me_your_name_length() {

	return (uchar)this->Name.size();

}

/******************************************************************************
*******************************************************************************
			EXTERN_NAME_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_NAME_IS_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_NAME_IS_EventPackage::EXTERN_NAME_IS_EventPackage(char * his_name) {

	this->Name = std::string(his_name);
}

char * EXTERN_NAME_IS_EventPackage::give_me_your_name() {

	return (char *)(this->Name.data());
}

uchar EXTERN_NAME_IS_EventPackage::give_me_your_name_length() {

	return (uchar)this->Name.size();

}


/******************************************************************************
*******************************************************************************
			MAP_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MAP_IS_EventPackage CONSTRUCTOR
**************************************************************/
MAP_IS_EventPackage::MAP_IS_EventPackage(const char * themap) :EventPackage(Event_type::MAP_IS) {

	//FALTA CALCULAR CHECKSUM (IF CHECKSUM !=0) LO TENGO QUE HACER, SINO SOY CLIENTE Y SE CHEQUEA DESPUES
	this->map = new char[QBLOCKS];
	memcpy(this->map, themap,192);

}
/**************************************************************
					GIVE_ME_THE_MAP
**************************************************************/
char * MAP_IS_EventPackage::give_me_the_map() {
	return this->map;
}
/**************************************************************
					GIVE_ME_THE_CHECKSUM
**************************************************************/
char MAP_IS_EventPackage::give_me_the_checksum() {
	return this->Checksum;
}

/******************************************************************************
*******************************************************************************
			MAP_IS_OK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MAP_IS_OK_EventPackage CONSTRUCTOR
**************************************************************/
MAP_IS_OK_EventPackage::MAP_IS_OK_EventPackage(char * themap) :EventPackage(Event_type::MAP_IS_OK) {

	//FALTA CALCULAR CHECKSUM (IF CHECKSUM !=0) LO TENGO QUE HACER, SINO SOY CLIENTE Y SE CHEQUEA DESPUES
	this->map = new char[QBLOCKS];
	strcpy_s(this->map, themap);
	this->info_length = 2 + QBLOCKS;

}

/******************************************************************************
*******************************************************************************
			LOCAL_ENEMY_ACTION_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			LOCAL_ENEMY_ACTION_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_ENEMY_ACTION_EventPackage::LOCAL_ENEMY_ACTION_EventPackage(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de) :EventPackage(Event_type::LOCAL_ENEMY_ACTION) {

	this->MonsterID = the_MonsterID;
	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}

uchar LOCAL_ENEMY_ACTION_EventPackage::give_me_the_monsterID() {
	return this->MonsterID;
}

Action_type LOCAL_ENEMY_ACTION_EventPackage::give_me_the_action() {
	return this->action;
}

char LOCAL_ENEMY_ACTION_EventPackage::give_me_the_destination_row() {
	return this->destination_row;

}
char LOCAL_ENEMY_ACTION_EventPackage::give_me_the_destination_column() {
	return this->destination_column;

}

/******************************************************************************
*******************************************************************************
			EXTERN_ENEMY_ACTION_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			EXTERN_ENEMY_ACTION_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_ENEMY_ACTION_EventPackage::EXTERN_ENEMY_ACTION_EventPackage(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de) :EventPackage(Event_type::EXTERN_ENEMY_ACTION) {

	this->MonsterID = the_MonsterID;
	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}

uchar EXTERN_ENEMY_ACTION_EventPackage::give_me_the_monsterID() {
	return this->MonsterID;
}

Action_type EXTERN_ENEMY_ACTION_EventPackage::give_me_the_action() {
	return this->action;
}

char EXTERN_ENEMY_ACTION_EventPackage::give_me_the_destination_row() {
	return this->destination_row;

}
char EXTERN_ENEMY_ACTION_EventPackage::give_me_the_destination_column() {
	return this->destination_column;

}
/******************************************************************************
*******************************************************************************
			ENEMY_ACTION_IS_OK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ENEMY_ACTION_IS_OK_EventPackage CONSTRUCTOR
**************************************************************/
ENEMY_ACTION_IS_OK_EventPackage::ENEMY_ACTION_IS_OK_EventPackage() :EventPackage(Event_type::ENEMY_ACTION_IS_OK) {



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
		NO_EVENT_EventPackage CONSTRUCTOR
**************************************************************/
NO_EVENT_EventPackage::NO_EVENT_EventPackage() :EventPackage(Event_type::NO_EVENT) {


}

/**************************************************************
		END_OF_TABLE_EventPackage CONSTRUCTOR
**************************************************************/
END_OF_TABLE_EventPackage::END_OF_TABLE_EventPackage() :EventPackage(Event_type::END_OF_TABLE) {


}


















