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
			MOVE_EventPackage CONSTRUCTOR
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Direction_type my_direction_type) :EventPackage(Event_type::MOVE)  {


}

/******************************************************************************
*******************************************************************************
			ATTACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ATTACK_EventPackage CONSTRUCTOR
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage():EventPackage(Event_type::ATTACK) {


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
	:EventPackage(Event_type::ENEMY_ACTION, is_local), ENEMY_ACTION_package(the_MonsterID, the_action, fil_de, col_de){

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


















