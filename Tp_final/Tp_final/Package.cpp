#include "Package.h"

/**************************************************************
		INITIALIZATION OF THE STATIC COUNTER
**************************************************************/
//This static variable counts the amount of MOVE packages created.
//This counter represnt the ID of the MOVE package,it´s unique. We prefer this against a rand number.
uint32_t Package::MOVE_Package_counter = 1;

/******************************************************************************
*******************************************************************************
			PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************

/**************************************************************
				PACKAGE CONSTRUCTOR
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
Package::Package(Package_type type)
{
	this->header = type;
}

/**************************************************************
				GET_PACKAGE_HEADER
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
Package_type Package::get_package_header()
{
	return this->header;
}

char* Package::get_sendable_info() {

}


/******************************************************************************
*******************************************************************************
			ACK_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACK_PACKAGE_CONSTRUCTOR
**************************************************************/
ACK_package::ACK_package() :Package(Package_type::ACK) {


}

/******************************************************************************
*******************************************************************************
			NAME_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			NAME_PACKAGE_CONSTRUCTOR
**************************************************************/
NAME_package::NAME_package() :Package(Package_type::NAME) {


}

/******************************************************************************
*******************************************************************************
			NAME_IS_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			NAME_IS_PACKAGE_CONSTRUCTOR
**************************************************************/
NAME_IS_package::NAME_IS_package(uchar namelenght, char * newname) :Package(Package_type::NAME_IS) {

	this->count = namelenght;
	this->Name = new char[namelenght];
	strcpy(this->Name, newname);
}

/**************************************************************
					GET_NAME_LENGHT
**************************************************************/
uchar NAME_IS_package::get_name_lenght() {

	return this->count;
}
/**************************************************************
					GIVE_ME_YOUR_NAME
**************************************************************/
char * NAME_IS_package::give_me_your_name() {


}

/******************************************************************************
*******************************************************************************
			MAP_IS_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MAP_IS_PACKAGE_CONSTRUCTOR
**************************************************************/
MAP_IS_package::MAP_IS_package(char * themap) :Package(Package_type::MAP_IS) {

	this->map = new char[192];
	strcpy(this->map, themap);

}

/**************************************************************
					GIVE_ME_THE_MAP
**************************************************************/
char * MAP_IS_package::give_me_the_map() {
	return this->map;
}
/**************************************************************
					GIVE_ME_THE_CHECKSUM
**************************************************************/
char MAP_IS_package::give_me_the_checksum() {
	return this->Checksum;
}

/******************************************************************************
*******************************************************************************
			GAME_START_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			GAME_START_PACKAGE_CONSTRUCTOR
**************************************************************/
GAME_START_package::GAME_START_package() :Package(Package_type::GAME_START) {


}

/******************************************************************************
*******************************************************************************
			MOVE_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MOVE_PACKAGE_CONSTRUCTOR
**************************************************************/
MOVE_package::MOVE_package(Character_type the_one_that_moves, char fil_de, char col_de) : Package(Package_type::MOVE) {

	this->character = the_one_that_moves;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}

Character_type MOVE_package::give_me_the_character() {
	return this->character;
}

char MOVE_package::give_me_the_destination_row() {
	return this->destination_row;

}
char MOVE_package::give_me_the_destination_column() {
	return this->destination_column;

}

/******************************************************************************
*******************************************************************************
			ATTACK_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ATTACK_PACKAGE_CONSTRUCTOR
**************************************************************/
ATTACK_package::ATTACK_package(Character_type the_one_that_attacks, char fil_de, char col_de) :Package(Package_type::ATTACK) {

	this->character = the_one_that_attacks;
	this->destination_row = fil_de;
	this->destination_column = col_de;
}
Character_type ATTACK_package::give_me_the_character() {
	return this->character;
}

char ATTACK_package::give_me_the_destination_row() {
	return this->destination_row;

}
char ATTACK_package::give_me_the_destination_column() {
	return this->destination_column;

}

/******************************************************************************
*******************************************************************************
			ACTION_REQUEST_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ACTION_REQUEST_PACKAGE_CONSTRUCTOR
**************************************************************/
ACTION_REQUEST_package::ACTION_REQUEST_package(Action_type the_action, char fil_de, char col_de) :Package(Package_type::ACTION_REQUEST) {

	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}

Action_type ACTION_REQUEST_package::give_me_the_action() {
	return this->action;
}

char ACTION_REQUEST_package::give_me_the_destination_row() {
	return this->destination_row;

}
char ACTION_REQUEST_package::give_me_the_destination_column() {
	return this->destination_column;

}

/******************************************************************************
*******************************************************************************
			ENEMY_ACTION_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			ENEMY_ACTION_PACKAGE_CONSTRUCTOR
**************************************************************/
ENEMY_ACTION_package::ENEMY_ACTION_package(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de) :Package(Package_type::ENEMY_ACTION) {

	this->MonsterID = the_MonsterID;
	this->action = the_action;
	this->destination_row = fil_de;
	this->destination_column = col_de;

}

uchar ENEMY_ACTION_package::give_me_the_monsterID() {
	return this->MonsterID;
}

Action_type ENEMY_ACTION_package::give_me_the_action() {
	return this->action;
}

char ENEMY_ACTION_package::give_me_the_destination_row() {
	return this->destination_row;

}
char ENEMY_ACTION_package::give_me_the_destination_column() {
	return this->destination_column;

}






/*******************************************************************************
*******************************************************************************/
/**************************************************************
			WE_WON_CONSTRUCTOR
**************************************************************/
WE_WON_package::WE_WON_package() :Package(Package_type::WE_WON) {


}

/*******************************************************************************
*******************************************************************************/
/**************************************************************
			PLAY_AGAIN_PACKAGE_CONSTRUCTOR
**************************************************************/
PLAY_AGAIN_package::PLAY_AGAIN_package() :Package(Package_type::PLAY_AGAIN) {


}

/**************************************************************
			GAME_OVER_PACKAGE_CONSTRUCTOR
**************************************************************/
GAME_OVER_package::GAME_OVER_package() :Package(Package_type::GAME_OVER) {



}



/*******************************************************************************
*******************************************************************************/
/**************************************************************
			ERROR_PACKAGE_CONSTRUCTOR
**************************************************************/
ERROR_package::ERROR_package() :Package(Package_type::ERROR) {


}

/**************************************************************
			QUIT_PACKAGE_CONSTRUCTOR
**************************************************************/
QUIT_package::QUIT_package() :Package(Package_type::QUIT) {



}







