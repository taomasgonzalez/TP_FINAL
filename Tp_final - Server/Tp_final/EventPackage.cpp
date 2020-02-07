#include "EventPackage.h"
#include <string>
#include <iostream>

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
EventPackage::EventPackage(Event_type event, uint16_t ID, bool is_local): Numbered_EventPackage(ID)
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
//Action_EventPackage::Action_EventPackage(unsigned char fil_de = NULL, unsigned char col_de = NULL, unsigned int ID, Direction_type dir = Direction_type::None) {

Action_EventPackage::Action_EventPackage(unsigned char fil_de, unsigned char col_de, Direction_type dir = Direction_type::None) {

	this->destination_row = fil_de;
	this->destination_column = col_de;
	this->my_direction = dir;
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


/**************************************************************
give_me_the_character
**************************************************************/
Item_type Action_EventPackage::give_me_the_character() {

	return this->character;
}
/**************************************************************
set_character (LOCAL)
**************************************************************/
void Action_EventPackage::set_character(Item_type the_one_that_moves) {
	this->character = the_one_that_moves;

}

/******************************************************************************
*******************************************************************************
Numbered_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
Numbered_EventPackage CONSTRUCTOR
**************************************************************/

Numbered_EventPackage::Numbered_EventPackage(uint16_t ID) {

	this->package_ID = ID;
}

/**************************************************************
	give_me_your_package_ID
**************************************************************/
uint16_t Numbered_EventPackage::give_me_your_package_ID() {

	return package_ID;

}

/**************************************************************
	give_me_your_package_ID
**************************************************************/
void Numbered_EventPackage::set_your_package_ID(uint16_t ID) {

	this->package_ID = ID;

}




/******************************************************************************
*******************************************************************************
ACK_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
ACK_EventPackage_CONSTRUCTOR
**************************************************************/
ACK_EventPackage::ACK_EventPackage(uint16_t ID, bool is_local) :EventPackage(Event_type::ACK,ID, is_local) {

}



/******************************************************************************
*******************************************************************************
LOCAL_QUIT_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
LOCAL_QUIT_EventPackage CONSTRUCTOR
**************************************************************/
LOCAL_QUIT_EventPackage::LOCAL_QUIT_EventPackage() :EventPackage(Event_type::LOCAL_QUIT,0,true) {

}

/******************************************************************************
*******************************************************************************
EXTERN_QUIT_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
EXTERN_QUIT_EventPackage CONSTRUCTOR
**************************************************************/
EXTERN_QUIT_EventPackage::EXTERN_QUIT_EventPackage() :EventPackage(Event_type::EXTERN_QUIT,0,false) {

}

/******************************************************************************
*******************************************************************************
RESET_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
RESET_EventPackage CONSTRUCTOR
**************************************************************/
RESET_EventPackage::RESET_EventPackage(bool is_local) :EventPackage(Event_type::RESET,0, is_local) {

}


/******************************************************************************
*******************************************************************************
MOVE_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (LOCAL)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Direction_type direction_type, uint16_t ID) :EventPackage(Event_type::MOVE, ID,true), Action_EventPackage(direction_type) { //LOCAL MOVE

}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(unsigned char fil_de, unsigned char col_de, uint16_t ID) :EventPackage(Event_type::MOVE,ID, false), Action_EventPackage(fil_de, col_de){			//EXTERN MOVE


}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de, uint16_t ID) :EventPackage(Event_type::MOVE,ID, false), Action_EventPackage(fil_de, col_de) {			//EXTERN MOVE

	this->set_character(my_character);

}
/**************************************************************
MOVE_EventPackage CONSTRUCTOR (MADE FROM AN Action_type)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(Action_info * my_info) :EventPackage(Event_type::MOVE, my_info->ID, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y) {

	this->set_character(my_info->my_character);
	this->set_direction(my_info->my_direction);

}

/**************************************************************
MOVE_EventPackage CONSTRUCTOR (MADE FROM AN ANOTHER MOVE)
**************************************************************/
MOVE_EventPackage::MOVE_EventPackage(MOVE_EventPackage* moved) :EventPackage(Event_type::MOVE, moved->give_me_your_package_ID(), moved->is_this_a_local_action()), Action_EventPackage(moved->give_me_your_destination_column(), moved->give_me_your_destination_row()) {

	this->set_character(moved->give_me_the_character());
	this->set_direction(moved->give_me_your_direction());

}



//Chequear uso de este constructor CUIDADO
MOVE_EventPackage::MOVE_EventPackage() :EventPackage(Event_type::MOVE,0, true), Action_EventPackage(Direction_type::None)
{

}





Action_info MOVE_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	returnable_info.final_pos_x = give_me_your_destination_row();
	returnable_info.final_pos_y = give_me_your_destination_column();
	returnable_info.my_character = give_me_the_character();
	returnable_info.action = Action_type::Move;
	returnable_info.id = (unsigned int)returnable_info.my_character;
	returnable_info.my_direction = give_me_your_direction();

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
ATTACK_EventPackage::ATTACK_EventPackage(uint16_t ID) :EventPackage(Event_type::ATTACK, ID,true), Action_EventPackage(Direction_type::None){


}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(unsigned char fil_de, unsigned char col_de, uint16_t ID) :EventPackage(Event_type::ATTACK, ID ,false), Action_EventPackage(fil_de, col_de) {


}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (MADE FROM AN AR)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(Item_type my_character, unsigned char fil_de, unsigned char col_de, uint16_t ID) :EventPackage(Event_type::ATTACK, ID, false), Action_EventPackage(fil_de, col_de) {

	this->set_character(my_character);

}
/**************************************************************
ATTACK_EventPackage CONSTRUCTOR
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(Action_info * my_info) :EventPackage(Event_type::ATTACK, my_info->ID, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y){

	this->set_character(my_info->my_character);
	this->set_direction(my_info->my_direction);


}

/**************************************************************
ATTACK_EventPackage CONSTRUCTOR (MADE FROM AN ANOTHER ATTACK)
**************************************************************/
ATTACK_EventPackage::ATTACK_EventPackage(ATTACK_EventPackage* attack) :EventPackage(Event_type::ATTACK, attack->give_me_your_package_ID(), attack->is_this_a_local_action()), Action_EventPackage(attack->give_me_your_destination_column(), attack->give_me_your_destination_row()) {

	this->set_character(attack->give_me_the_character());
	this->set_direction(attack->give_me_your_direction());

}



//cualquier queja (que no sea de logica interna) quejarse a Tommy.
Action_info ATTACK_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();
	returnable_info.action = Action_type::Attack;
	if (returnable_info.is_local)
		returnable_info.my_direction = give_me_your_direction(); //none
	else {
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
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, Direction_type direction, uint16_t ID) : EventPackage(Event_type::ACTION_REQUEST, ID, true), Action_EventPackage(direction){ //local ACTION_REQUEST

	this->action = the_action;
}
/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR (EXTERN)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_type the_action, unsigned char fil_de, unsigned char col_de, uint16_t ID) : EventPackage(Event_type::ACTION_REQUEST, ID, false), Action_EventPackage(fil_de, col_de) { //extern ACTION_REQUEST

	this->action = the_action;
}

/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(Action_info* my_info) : EventPackage(Event_type::ACTION_REQUEST, my_info->ID, my_info->is_local), Action_EventPackage(my_info->final_pos_x, my_info->final_pos_y){

	action = my_info->action;
	set_direction(my_info->my_direction);

}

/**************************************************************
ACTION_REQUEST_EventPackage CONSTRUCTOR (MADE FROM AN ANOTHER AR)
**************************************************************/
ACTION_REQUEST_EventPackage::ACTION_REQUEST_EventPackage(ACTION_REQUEST_EventPackage* action_request) :EventPackage(Event_type::ACTION_REQUEST, action_request->give_me_your_package_ID(), action_request->is_this_a_local_action()), Action_EventPackage(action_request->give_me_your_destination_column(), action_request->give_me_your_destination_row()){

	this->set_character(action_request->give_me_the_character());
	this->set_direction(action_request->give_me_your_direction());

}

/**************************************************************
give_me_the_action
**************************************************************/
Action_type ACTION_REQUEST_EventPackage::give_me_the_action() {
	return action;
}

//cualquier queja (que no sea de logica interna) quejarse a Tommy.
Action_info ACTION_REQUEST_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	if (!returnable_info.is_local) {
		returnable_info.final_pos_x = give_me_your_destination_row();
		returnable_info.final_pos_y = give_me_your_destination_column();
	}
	returnable_info.id = (unsigned int)CLIENT_PLAYER;
	returnable_info.action = give_me_the_action();
	returnable_info.my_direction = give_me_your_direction();
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
ERROR_EventPackage::ERROR_EventPackage(bool is_local) :EventPackage(Event_type::ERROR1,0, is_local) {

}


/******************************************************************************
*******************************************************************************
NAME_EventPackage METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
NAME_EventPackage
**************************************************************/
NAME_EventPackage::NAME_EventPackage(bool is_local) :EventPackage(Event_type::NAME,0, is_local) {

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
	:EventPackage(Event_type::NAME_IS,0, is_local) {
	this->Name = newname;
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
MAP_IS_EventPackage::MAP_IS_EventPackage(bool is_local, const unsigned char * themap, unsigned char checksum) :EventPackage(Event_type::MAP_IS,0, is_local) {

	this->map = themap;
	this->Checksum = checksum;
}
/**************************************************************
					GIVE_ME_THE_MAP
**************************************************************/
const unsigned char * MAP_IS_EventPackage::give_me_the_map() {
	return this->map;
}
/**************************************************************
					GIVE_ME_THE_CHECKSUM
**************************************************************/
unsigned char MAP_IS_EventPackage::give_me_the_checksum() {
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
ENEMY_ACTION_EventPackage::ENEMY_ACTION_EventPackage(bool is_local, uchar the_MonsterID, Action_type the_action, unsigned char fil_de, unsigned char col_de, uint16_t ID)
	:EventPackage(Event_type::ENEMY_ACTION,ID, is_local), Action_EventPackage(fil_de, col_de){

	this->MonsterID = the_MonsterID;
	this->action = the_action;
}

ENEMY_ACTION_EventPackage::ENEMY_ACTION_EventPackage(Action_info* ea_info) :EventPackage(Event_type::ENEMY_ACTION, ea_info->ID, ea_info->is_local), Action_EventPackage(ea_info->final_pos_y, ea_info->final_pos_x){

	this->action = ea_info->action;
	this->MonsterID = ea_info->id;
}

ENEMY_ACTION_EventPackage::ENEMY_ACTION_EventPackage(ENEMY_ACTION_EventPackage* enemy_action) :EventPackage(Event_type::ENEMY_ACTION, enemy_action->give_me_your_package_ID(), enemy_action->is_this_a_local_action()), Action_EventPackage(enemy_action->give_me_your_destination_column(), enemy_action->give_me_your_destination_row()) {

	this->action = enemy_action->give_me_the_action();
	this->MonsterID = enemy_action->give_me_the_monsterID();
}


uchar ENEMY_ACTION_EventPackage::give_me_the_monsterID() {
	return this->MonsterID;
}

Action_type ENEMY_ACTION_EventPackage::give_me_the_action() {
	return this->action;
}



Action_info ENEMY_ACTION_EventPackage::to_Action_info()
{
	Action_info returnable_info = EventPackage::to_Action_info();

	returnable_info.my_info_header = Action_info_id::ENEMY_ACTION;
	returnable_info.action = give_me_the_action();

	returnable_info.id = give_me_the_monsterID();
	returnable_info.my_direction = give_me_your_direction();

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
ENEMYS_LOADED_EventPackage::ENEMYS_LOADED_EventPackage() :EventPackage(Event_type::ENEMYS_LOADED,0,true) {

}

/**************************************************************
GAME_START_EventPackage
**************************************************************/
GAME_START_EventPackage::GAME_START_EventPackage(bool is_local) :EventPackage(Event_type::GAME_START,0,is_local) {


}

/**************************************************************
WE_WON_EventPackage
**************************************************************/
WE_WON_EventPackage::WE_WON_EventPackage(bool is_local) :EventPackage(Event_type::WE_WON,0,is_local) {


}

/**************************************************************
PLAY_AGAIN_EventPackage
**************************************************************/
PLAY_AGAIN_EventPackage::PLAY_AGAIN_EventPackage(bool is_local) :EventPackage(Event_type::PLAY_AGAIN,0,is_local) {


}

/**************************************************************
GAME_OVER_EventPackage CONSTRUCTOR
**************************************************************/
GAME_OVER_EventPackage::GAME_OVER_EventPackage(bool is_local) :EventPackage(Event_type::GAME_OVER,0, is_local) {


}

/**************************************************************
START_COMMUNICATION_EventPackage CONSTRUCTOR
**************************************************************/
START_COMMUNICATION_EventPackage::START_COMMUNICATION_EventPackage() :EventPackage(Event_type::START_COMMUNICATION,0,true) {


}

/**************************************************************
FINISHED_LEVEL_EventPackage CONSTRUCTOR
**************************************************************/
FINISHED_LEVEL_EventPackage::FINISHED_LEVEL_EventPackage() :EventPackage(Event_type::FINISHED_LEVEL,0,true) {


}


/**************************************************************
END_OF_TABLE_EventPackage CONSTRUCTOR
**************************************************************/
END_OF_TABLE_EventPackage::END_OF_TABLE_EventPackage() :EventPackage(Event_type::END_OF_TABLE,0,true) {


}

Action_info EventPackage::to_Action_info() {

	Action_info returnable_info;

	returnable_info.my_info_header = Event_type_2_Action_info_id(give_me_your_event_type());
	returnable_info.is_local = is_this_a_local_action();
	returnable_info.ID = give_me_your_package_ID();




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

FINISHED_MOVEMENT_EventPackage::FINISHED_MOVEMENT_EventPackage() : EventPackage(Event_type::FINISHED_MOVEMENT,0, true) {

}

WALKED_EventPackage::WALKED_EventPackage(Direction_type dir) : EventPackage(Event_type::WALKED,0, true) {
	walking_direction = dir;
}

WALKED_EventPackage::WALKED_EventPackage(const WALKED_EventPackage* walked) : EventPackage(Event_type::WALKED,0, true) {
	walking_direction = walked->walking_direction;
}



ATTACKED_EventPackage::ATTACKED_EventPackage() : EventPackage(Event_type::ATTACKED, 0,true) {

}

ATTACKED_EventPackage::~ATTACKED_EventPackage() {

}

JUMPED_EventPackage::JUMPED_EventPackage() : EventPackage(Event_type::JUMPED, 0,true) {

}
JUMPED_EventPackage::JUMPED_EventPackage(const JUMPED_EventPackage* walked) : EventPackage(Event_type::JUMPED,0, true) {
}


JUMPED_FORWARD_EventPackage::JUMPED_FORWARD_EventPackage(Direction_type dir) : EventPackage(Event_type::JUMPED_FORWARD,0, true) {
	jumping_direction = dir;
}
JUMPED_FORWARD_EventPackage::JUMPED_FORWARD_EventPackage(const JUMPED_FORWARD_EventPackage* walked) : EventPackage(Event_type::JUMPED_FORWARD,0, true) {
}




DIED_EventPackage::DIED_EventPackage() : EventPackage(Event_type::DIED, 0,true) {

}

FELL_EventPackage::FELL_EventPackage() : EventPackage(Event_type::FELL, 0,true) {

}

FINISHED_ATTACK_EventPackage::FINISHED_ATTACK_EventPackage() : EventPackage(Event_type::FINISHED_ATTACK, 0,true) {

}

GOT_HIT_EventPackage::GOT_HIT_EventPackage() : EventPackage(Event_type::GOT_HIT, 0,true)
{

}

PUSHED_EventPackage::PUSHED_EventPackage(Direction_type dir) : EventPackage(Event_type::PUSHED, 0,true)
{
	this->pushing_direction = dir;
}

PUSHED_EventPackage::~PUSHED_EventPackage()
{
}

PARTIALLY_UNFROZE_EventPackage::PARTIALLY_UNFROZE_EventPackage() : EventPackage(Event_type::PARTIALLY_UNFROZE, 0,true) {

}
PARTIALLY_UNFROZE_EventPackage::~PARTIALLY_UNFROZE_EventPackage() {

}

UNFROZE_EventPackage::UNFROZE_EventPackage() :EventPackage(Event_type::UNFROZE, 0,true) {

}
UNFROZE_EventPackage::~UNFROZE_EventPackage() {

}


FINISHED_GRAPH_STEP_EventPackage::FINISHED_GRAPH_STEP_EventPackage() : EventPackage(Event_type::FINISHED_GRAPH_STEP, 0,true) {

}
FINISHED_GRAPH_STEP_EventPackage::~FINISHED_GRAPH_STEP_EventPackage() {

}

