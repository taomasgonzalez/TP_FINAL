#include "EventPackage.h"

Action_info_id Event_type_2_Action_info_id(Event_type event_t);
Event_type Action_info_id_2_Event_type(Action_info_id event_t);
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
EventPackage::EventPackage(Event_type event, bool is_local)
{
	this->my_internal_event = event;
	this->local_action = is_local;

}

EventPackage::~EventPackage() {

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
Action_EventPackage::Action_EventPackage(unsigned char fil_de = NULL, unsigned char col_de = NULL) {

	this->destination_row = fil_de;
	this->destination_column = col_de;
}

Action_EventPackage::Action_EventPackage(Direction_type direction_type) {
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
MOVE_EventPackage::MOVE_EventPackage(Direction_type direction_type) :EventPackage(Event_type::MOVE, true), Action_EventPackage(direction_type) { //LOCAL MOVE

}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::MOVE, false), Action_EventPackage(fil_de, col_de) {			//EXTERN MOVE


}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::MOVE, false), Action_EventPackage(fil_de, col_de) {			//EXTERN MOVE

	this->character = my_character;

}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (MADE FROM AN Action_type)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Action_info * my_info) :EventPackage(Event_type::MOVE, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y) {

	this->character = my_info->my_character;
	this->set_direction(my_info->my_direction);

}

MOVE_EventPackage::MOVE_EventPackage():EventPackage(Event_type::MOVE, true)
{

}



/**************************************************************
give_me_the_character
**************************************************************/
Item_type MOVE_EventPackage::give_me_the_character() {

	return this->character;
}
/**************************************************************
set_character (LOCAL)
**************************************************************/
void MOVE_EventPackage::set_character(Item_type the_one_that_moves) {
	this->character = the_one_that_moves;

}

Action_info MOVE_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	if (returnable_info.is_local)
		returnable_info.my_direction = give_me_your_direction();
	else{
		returnable_info.my_character = give_me_the_character();
		returnable_info.final_pos_x = give_me_your_destination_row();
		returnable_info.final_pos_y = give_me_your_destination_column();
	}
	return returnable_info;
}


/******************************************************************************
*******************************************************************************
ATTACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage() :EventPackage(Event_type::ATTACK, true), Action_EventPackage(Direction_type::None) {


}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::ATTACK, false), Action_EventPackage(fil_de, col_de) {


}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de) :EventPackage(Event_type::ATTACK, false), Action_EventPackage(fil_de, col_de) {

	this->character = my_character;

}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR 
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(Action_info * my_info) :EventPackage(Event_type::ATTACK, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y) {

	this->character = my_info->my_character;
	this->set_direction(my_info->my_direction);


}


/**************************************************************
give_me_the_character
**************************************************************/
Item_type ATTACK_EventPackage::give_me_the_character() {

	return this->character;
}
/**************************************************************
set_character (LOCAL)
**************************************************************/
void ATTACK_EventPackage::set_character(Item_type the_one_that_moves) {
	this->character = the_one_that_moves;

}

//cualquier queja (que no sea de logica interna) quejarse a Tommy.
Action_info ATTACK_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	if (returnable_info.is_local)
		returnable_info.my_direction = give_me_your_direction(); //none
	else{
		returnable_info.my_character = give_me_the_character();
		returnable_info.final_pos_x = give_me_your_destination_row();
		returnable_info.final_pos_y = give_me_your_destination_column();
	}
	return returnable_info;
}


/******************************************************************************
*******************************************************************************
ACTION_REQUEST_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, Direction_type direction) : EventPackage(Event_type::ACTION_REQUEST, true), Action_EventPackage(direction) { //local ACTION_REQUEST

	this->action = the_action;
}
/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, char fil_de, char col_de) : EventPackage(Event_type::ACTION_REQUEST, false), Action_EventPackage(fil_de, col_de) { //extern ACTION_REQUEST

	this->action = the_action;

}

/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR 
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_info* my_info) : EventPackage(Event_type::ACTION_REQUEST, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y) {
	
	this->action = my_info->action;
	this->set_direction(my_info->my_direction);

}

/**************************************************************
give_me_the_action
**************************************************************/
Action_type ACTION_REQUEST_EventPackage::give_me_the_action() {
	return this->action;
}

//cualquier queja (que no sea de logica interna) quejarse a Tommy.
Action_info ACTION_REQUEST_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	if (returnable_info.is_local)
		returnable_info.my_direction = give_me_your_direction(); //none
	else
	{
		returnable_info.action = give_me_the_action();
		returnable_info.final_pos_x = give_me_your_destination_row();
		returnable_info.final_pos_y = give_me_your_destination_column();
	}

	return returnable_info;
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
NAME_IS_EventPackage::NAME_IS_EventPackage(bool is_local, uchar namelenght, std::string newname)
	:EventPackage(Event_type::NAME_IS, is_local) {
	this->Name =  newname;
	this->count = namelenght;
}

/**************************************************************
					GET_NAME_LENGHT
**************************************************************/
uchar NAME_IS_EventPackage::get_name_lenght() {

	return this->count;
}

/**************************************************************
					GIVE_ME_YOUR_NAME
**************************************************************/
std::string NAME_IS_EventPackage::give_me_your_name() {

	return this->Name;
}

/******************************************************************************
*******************************************************************************
MAP_IS_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
MAP_IS_EventPackage CONSTRUCTOR
**************************************************************/
MAP_IS_EventPackage::MAP_IS_EventPackage(bool is_local, const char * themap, char checksum) :EventPackage(Event_type::MAP_IS, is_local) {

	this->map =(char *) themap;
	this->Checksum = checksum;
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

ENEMY_ACTION_EventPackage::ENEMY_ACTION_EventPackage(Action_info* ea_info) :EventPackage(Event_type::ENEMY_ACTION, ea_info->is_local) {

	this->action = ea_info->action;
	this->destination_row = ea_info->final_pos_x;
	this->destination_column = ea_info->final_pos_y;
	this->MonsterID = ea_info->id;
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

//cualquier queja (que no sea de logica interna) quejarse a Tommy.
Action_info ENEMY_ACTION_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	returnable_info.action = give_me_the_action();
	returnable_info.final_pos_x = give_me_the_destination_row();
	returnable_info.final_pos_y = give_me_the_destination_column();
	returnable_info.id = give_me_the_monsterID();

	return returnable_info;
}
/******************************************************************************
*******************************************************************************
ENEMYS_LOADED_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
ENEMYS_LOADED_EventPackage CONSTRUCTOR
**************************************************************/
ENEMYS_LOADED_EventPackage::ENEMYS_LOADED_EventPackage() :EventPackage(Event_type::ENEMYS_LOADED) {

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

Action_info EventPackage::to_Action_info() {

	Action_info returnable_info;

	returnable_info.my_info_header = Event_type_2_Action_info_id(give_me_your_event_type());
	returnable_info.is_local = is_this_a_local_action();

	return returnable_info;
}


Action_info_id Event_type_2_Action_info_id(Event_type event_t) {
	Action_info_id returnable_ai_id = Action_info_id::None;

	if (event_t == Event_type::MOVE)
		returnable_ai_id = Action_info_id::MOVE;

	else if (event_t == Event_type::ATTACK)
		returnable_ai_id = Action_info_id::ATTACK;

	else if (event_t == Event_type::ACTION_REQUEST)
		returnable_ai_id = Action_info_id::ACTION_REQUEST;

	else if (event_t == Event_type::ENEMY_ACTION)
		returnable_ai_id = Action_info_id::ENEMY_ACTION;

	return returnable_ai_id;
}
Event_type Action_info_id_2_Event_type(Action_info_id ai_id) {
	Event_type returnable_ev_t = Event_type::END_OF_TABLE;

	if (ai_id == Action_info_id::MOVE)
		returnable_ev_t = Event_type::MOVE;

	else if (ai_id == Action_info_id::ATTACK)
		returnable_ev_t = Event_type::ATTACK;

	else if (ai_id == Action_info_id::ACTION_REQUEST)
		returnable_ev_t = Event_type::ACTION_REQUEST;

	else if (ai_id == Action_info_id::ENEMY_ACTION)
		returnable_ev_t = Event_type::ENEMY_ACTION;

	return returnable_ev_t;
}

FINISHED_MOVEMENT_EventPackage::FINISHED_MOVEMENT_EventPackage() : EventPackage(Event_type::FINISHED_MOVEMENT, true){

}

WALKED_EventPackage::WALKED_EventPackage(Direction_type dir): EventPackage(Event_type::WALKED, true)
{
}

JUMPED_EventPackage::JUMPED_EventPackage(): EventPackage(Event_type::JUMPED, true)
{

}
JUMPED_FORWARD_EventPackage::JUMPED_FORWARD_EventPackage(Direction_type dir) : EventPackage(Event_type::JUMPED_FORWARD, true) {

}

DIED_EventPackage::DIED_EventPackage() : EventPackage(Event_type::DIED, true) {

}

FELL_EventPackage::FELL_EventPackage() : EventPackage(Event_type::FELL, true){

}

FINISHED_ATTACK_EventPackage::FINISHED_ATTACK_EventPackage() : EventPackage(Event_type::FINISHED_ATTACK, true) {

}

GOT_HIT_EventPackage::GOT_HIT_EventPackage():EventPackage(Event_type::GOT_HIT, true)
{

}

PUSHED_EventPackage::PUSHED_EventPackage(Direction_type dir) : EventPackage(Event_type::PUSHED, true)
{
	this->pushing_direction = dir;
}

PUSHED_EventPackage::~PUSHED_EventPackage()
{
}

PARTIALLY_UNFROZE_EventPackage::PARTIALLY_UNFROZE_EventPackage() : EventPackage(Event_type::PARTIALLY_UNFROZE, true){

}
PARTIALLY_UNFROZE_EventPackage::~PARTIALLY_UNFROZE_EventPackage() {

}

UNFROZE_EventPackage::UNFROZE_EventPackage() :EventPackage(Event_type::UNFROZE, true) {

}
UNFROZE_EventPackage::~UNFROZE_EventPackage() {

}