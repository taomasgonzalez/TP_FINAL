#include "Package.h"
#include <sstream>
std::string Package::enum_to_string(Package_type package_to_be_translate){

	switch (package_to_be_translate) {

	case Package_type::ACTION_REQUEST:
		return std::string("\x33");

	case Package_type::ATTACK:
		return std::string("\x32");

	case Package_type::MOVE:
		return std::string("\x31");

	case Package_type::ENEMY_ACTION:
		return std::string("\x34");

	case Package_type::NAME_IS:
		return std::string("\x11");

	case Package_type::MAP_IS:
		return std::string("\x12");

	default:
		return "INVALID ENUM";
	}
}
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
	this->info_to_be_send = (char *)&(this->header);
}
Package::~Package(){

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

/**************************************************************
				GET_SENDABLE_INFO
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
std::string Package::get_sendable_info() {

	std::string info = this->info_to_be_send;
	return info;
}

/**************************************************************
				GET_INFO_LENGTH
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
int Package::get_info_length() {

	return this->info_length;
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
NAME_IS_package::NAME_IS_package(uchar namelenght,std::string newname) :Package(Package_type::NAME_IS) {

	this->count = namelenght-48; //elimino el desfasaje generado al enviar el string para evitar un posible terminador no deseado
	this->Name =  newname;
	this->info_length = 2 + this->count;

}
/**************************************************************
			NAME_IS_PACKAGE_CONSTRUCTOR
**************************************************************/
NAME_IS_package::NAME_IS_package(uchar namelenght, char * newname) :Package(Package_type::NAME_IS) {

	newname[namelenght-48] = '\0';
	this->count = namelenght-48;
	this->Name = newname;
	this->info_length = 2 + this->count;

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
std::string NAME_IS_package::give_me_your_name() {

	return this->Name;
}

/**************************************************************
				GET_SENDABLE_INFO
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
std::string NAME_IS_package::get_sendable_info() {

	std::string info2;
	std::stringstream ss;
	ss << enum_to_string(this->header);
	ss << (count+48); //corrimiento para evitar un 0 que sea funcione como un terminador no deseado
	ss << this->Name;
	ss >> info2;
	/*
	std::string info(enum_to_string(this->header));
	std::string info1(1,this->count);
	std::string info2= info+ info1+Name;
	*/

	return info2;
}

/******************************************************************************
*******************************************************************************
			MAP_IS_PACKAGE METHODS DEFINITIONS
*******************************************************************************
*******************************************************************************/
/**************************************************************
			MAP_IS_PACKAGE_CONSTRUCTOR
**************************************************************/
MAP_IS_package::MAP_IS_package(const char * themap, char my_checksum) :Package(Package_type::MAP_IS) {

	//FALTA CALCULAR CHECKSUM (IF CHECKSUM !=0) LO TENGO QUE HACER, SINO SOY CLIENTE Y SE CHEQUEA DESPUES
	this->map = new char[QBLOCKS];
	this->Checksum = my_checksum;
	memcpy(this->map, themap, (size_t)QBLOCKS);
	this->info_length = 2 + QBLOCKS;

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
/**************************************************************
				GET_SENDABLE_INFO
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
std::string MAP_IS_package::get_sendable_info() {

	std::string info(enum_to_string(this->header));
	std::string info1(map, 192);
	std::string info2(1, Checksum);
	//std::string info2((const char*)this->Checksum,1);
	std::string info3 = info + info1 + info2;

	return info3;
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
	this->destination_row = fil_de - 48;//elimino el desfasaje generado al enviar el string para evitar un posible terminador no deseado
	this->destination_column = col_de - 48;//elimino el desfasaje generado al enviar el string para evitar un posible terminador no deseado
	this->info_length = 4;


}
/**************************************************************
				GET_SENDABLE_INFO
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
std::string MOVE_package::get_sendable_info() {

	std::string info(enum_to_string(this->header));
	std::string info1(1,(char)this->character);
	std::string info2(1,this->destination_row+48);
	std::string info3(1,this->destination_column+48);

	std::string info4 = info + info1 + info2+ info3;

	return info4;
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
	this->destination_row = fil_de - 48; //elimino el desfasaje generado al enviar el string para evitar un posible terminador no deseado
	this->destination_column = col_de - 48;//elimino el desfasaje generado al enviar el string para evitar un posible terminador no deseado
	this->info_length = 4;

}
/**************************************************************
				GET_SENDABLE_INFO
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
std::string ATTACK_package::get_sendable_info() {


	std::string info(enum_to_string(this->header));
	std::string info1(1,(char)this->character);
	std::string info2(1,this->destination_row+48);
	std::string info3(1,this->destination_column+48);

	std::string info4 = info + info1 + info2 + info3;

	return info4.c_str();
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
	this->destination_row = fil_de-48;
	this->destination_column = col_de-48;
	this->info_length = 4;

}
/**************************************************************
				GET_SENDABLE_INFO
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
std::string ACTION_REQUEST_package::get_sendable_info() {

	std::string info(enum_to_string(this->header));
	std::string info1(1,(char)this->action);
	std::string info2(1,this->destination_row+48);
	std::string info3(1,this->destination_column+48);

	std::string info4 = info + info1 + info2 + info3;

	return info4;
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

	this->MonsterID = the_MonsterID-48;
	this->action = the_action;
	this->destination_row = fil_de-48;
	this->destination_column = col_de-48;
	this->info_length = 5;
}

/**************************************************************
				GET_SENDABLE_INFO
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
std::string ENEMY_ACTION_package::get_sendable_info() {

	std::string info(enum_to_string(this->header));
	std::string info1(1,this->MonsterID+48); //para evitar tener un terminador que cropee el string
	std::string info2(1,(char)this->action);
	std::string info3(1,this->destination_row+48);//cuidado porque a partir de columna/fila 10 ya no vas a tener un ascii número
	std::string info4(1,this->destination_column+48);

	std::string info5 = info + info1 + info2 + info3 + info4;

	return info5;
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
ERROR_package::ERROR_package() :Package(Package_type::ERROR1) {


}

/**************************************************************
			QUIT_PACKAGE_CONSTRUCTOR
**************************************************************/
QUIT_package::QUIT_package() :Package(Package_type::QUIT) {



}







