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
EventPackage::EventPackage(Event_type event,bool is_local)
{
	this->my_internal_event = event;
	this->local_action = is_local;
	this->my_internal_event = Event_type::NO_EVENT;

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
				is_this_a_local_action
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
bool EventPackage::is_this_a_local_action() {

	return this->local_action;
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
ACK_EventPackage::ACK_EventPackage(bool is_local) :EventPackage(Event_type::ACK, is_local) {


}

/******************************************************************************
*******************************************************************************
			QUIT_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			QUIT_EventPackage CONSTRUCTOR
**************************************************************/
QUIT_EventPackage::QUIT_EventPackage(bool is_local) :EventPackage(Event_type::QUIT, is_local) {



}



/******************************************************************************
*******************************************************************************
			MOVE_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MOVE_EventPackage CONSTRUCTOR
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(bool is_local, Character_type the_one_that_moves, char fil_de, char col_de)
	:EventPackage(Event_type::MOVE, is_local),MOVE_package(the_one_that_moves, fil_de, col_de) {


}

/******************************************************************************
*******************************************************************************
			ATTACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ATTACK_EventPackage CONSTRUCTOR
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(bool is_local, Character_type the_one_that_moves, char fil_de, char col_de)
	:EventPackage(Event_type::ATTACK, is_local), ATTACK_package(the_one_that_moves, fil_de, col_de) {


}



/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_EventPackage CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(bool is_local, Action_type the_action, char fil_de, char col_de) 
	:EventPackage(Event_type::ACTION_REQUEST, is_local), ACTION_REQUEST_package(the_action,fil_de,col_de){


}


/******************************************************************************
*******************************************************************************
			ERROR_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ERROR_EventPackage CONSTRUCTOR
**************************************************************/
ERROR_EventPackage::ERROR_EventPackage(bool is_local) :EventPackage(Event_type::ERROR1, is_local) {



}


/******************************************************************************
*******************************************************************************
			NAME_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
				NAME_EventPackage
**************************************************************/
NAME_EventPackage::NAME_EventPackage(bool is_local) :EventPackage(Event_type::NAME, is_local) {

}


/******************************************************************************
*******************************************************************************
			NAME_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			NAME_IS_EventPackage CONSTRUCTOR
**************************************************************/
NAME_IS_EventPackage::NAME_IS_EventPackage(bool is_local , uchar namelenght, char * newname) 
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
MAP_IS_EventPackage::MAP_IS_EventPackage(bool is_local, const char * themap, char cheksum) :EventPackage(Event_type::MAP_IS, is_local), MAP_IS_package(themap,checksum){


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
	:EventPackage(Event_type::ENEMY_ACTION, is_local), ENEMY_ACTION_package(the_MonsterID, the_action, fil_de, col_de){

}



/**************************************************************
			GAME_START_EventPackage
**************************************************************/
GAME_START_EventPackage::GAME_START_EventPackage(bool is_local) :EventPackage(Event_type::GAME_START,is_local) {


}

/**************************************************************
			WE_WON_EventPackage
**************************************************************/
WE_WON_EventPackage::WE_WON_EventPackage(bool is_local) :EventPackage(Event_type::WE_WON,is_local) {


}

/**************************************************************
			PLAY_AGAIN_EventPackage
**************************************************************/
PLAY_AGAIN_EventPackage::PLAY_AGAIN_EventPackage(bool is_local) :EventPackage(Event_type::PLAY_AGAIN,is_local) {


}

/**************************************************************
		GAME_OVER_EventPackage CONSTRUCTOR
**************************************************************/
GAME_OVER_EventPackage::GAME_OVER_EventPackage(bool is_local) :EventPackage(Event_type::GAME_OVER,is_local) {


}

/**************************************************************
		START_COMMUNICATION_EventPackage CONSTRUCTOR
**************************************************************/
START_COMMUNICATION_EventPackage::START_COMMUNICATION_EventPackage(bool is_local) :EventPackage(Event_type::START_COMMUNICATION,is_local) {


}

/**************************************************************
		NO_EVENT_EventPackage CONSTRUCTOR
**************************************************************/
NO_EVENT_EventPackage::NO_EVENT_EventPackage(bool is_local) :EventPackage(Event_type::NO_EVENT,is_local) {


}

/**************************************************************
		END_OF_TABLE_EventPackage CONSTRUCTOR
**************************************************************/
END_OF_TABLE_EventPackage::END_OF_TABLE_EventPackage(bool is_local) :EventPackage(Event_type::END_OF_TABLE, is_local) {


}


















