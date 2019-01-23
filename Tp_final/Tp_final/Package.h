#pragma once
extern "C" {
#include <stdint.h> 
}
#include <string.h>
#include "Userdata.h"

typedef unsigned int uint;
typedef unsigned char uchar;
#define QBLOCKS 192

/***********************************************************************************************************************
************************************************************************************************************************
										PACKAGE ZONE
************************************************************************************************************************
************************************************************************************************************************/
enum class Package_type {
	ACK = 0x01, NAME = 0x10, NAME_IS = 0x11, MAP_IS = 0x12, GAME_START = 0x20, MOVE = 0x31, ATTACK = 0x32
	, ACTION_REQUEST = 0x33, ENEMY_ACTION = 0x34, WE_WON = 0x40, PLAY_AGAIN = 0x50, GAME_OVER = 0x51, ERROR1 = 0xFE, QUIT = 0xFF
};

enum class Character_type { TOM = 'T', NICK = 'N', PURPLE_GUY = 'P', GREEN_FATTIE = 'G', CRAZY = 'C', FLOOR = 'F', NADA = 'E' };

/******************************************************************************
*******************************************************************************
								PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class Package {
public:
	Package(Package_type type);
	Package_type get_package_header();
	char * get_sendable_info();
	int get_info_length();

protected:
	char* info_to_be_send; //for Communication::SendMessage()
	int info_length = 1;//for Communication::SendMessage()
	Package_type header;

};

/******************************************************************************
*******************************************************************************
							ACK_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class ACK_package : public Package
{
public:
	ACK_package();

private:

};

/******************************************************************************
*******************************************************************************
							NAME_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/

class NAME_package : public Package
{
public:
	NAME_package();

private:

};

/******************************************************************************
*******************************************************************************
							NAME_IS_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/

class NAME_IS_package : public Package
{
public:
	NAME_IS_package(uchar namelenght, char * newname);
	uchar get_name_lenght();
	char * give_me_your_name();


private:
	uchar count;
	char * Name; // without terminator
};

/******************************************************************************
*******************************************************************************
							MAP_IS_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/

class MAP_IS_package : public Package
{
public:
	MAP_IS_package(const char * themap,char my_checksum);
	char * give_me_the_map();
	char give_me_the_checksum();

private:
	char * map;
	char Checksum=0;
};

/******************************************************************************
*******************************************************************************
							GAME_START_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class GAME_START_package : public Package
{
public:
	GAME_START_package();

private:

};


/******************************************************************************
*******************************************************************************
							MOVE_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class MOVE_package : public Package
{
public:
	MOVE_package(Character_type the_one_that_moves, char fil_de, char col_de);
	Character_type give_me_the_character();
	char give_me_the_destination_row();
	char give_me_the_destination_column();

private:
	Character_type character;
	char destination_row;
	char destination_column;

};


/******************************************************************************
*******************************************************************************
							ATTACK_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class ATTACK_package : public Package
{
public:
	ATTACK_package(Character_type the_one_that_attacks, char fil_de, char col_de);
	Character_type give_me_the_character();
	char give_me_the_destination_row();
	char give_me_the_destination_column();

private:
	Character_type character;
	char destination_row;
	char destination_column;

};



/******************************************************************************
*******************************************************************************
							ACTION_REQUEST_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class ACTION_REQUEST_package : public Package
{
public:
	ACTION_REQUEST_package(Action_type the_action, char fil_de, char col_de);
	Action_type give_me_the_action();
	char give_me_the_destination_row();
	char give_me_the_destination_column();

private:
	Action_type action;
	char destination_row;
	char destination_column;

};


/******************************************************************************
*******************************************************************************
							ENEMY_ACTION_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class ENEMY_ACTION_package : public Package
{
public:
	ENEMY_ACTION_package(uchar the_MonsterID, Action_type the_action, char fil_de, char col_de);
	uchar give_me_the_monsterID();
	Action_type give_me_the_action();
	char give_me_the_destination_row();
	char give_me_the_destination_column();

private:
	uchar MonsterID;
	Action_type action;
	char destination_row;
	char destination_column;

};


/******************************************************************************
*******************************************************************************
							WE_WON_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class WE_WON_package : public Package
{
public:
	WE_WON_package();

private:

};

/******************************************************************************
*******************************************************************************
							PLAY_AGAIN_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class PLAY_AGAIN_package : public Package
{
public:
	PLAY_AGAIN_package();

private:

};

/******************************************************************************
*******************************************************************************
							GAME_OVER_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class GAME_OVER_package : public Package
{
public:
	GAME_OVER_package();

private:

};


/******************************************************************************
*******************************************************************************
							QUIT_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class QUIT_package : public Package
{
public:
	QUIT_package();

};

/******************************************************************************
*******************************************************************************
							ERROR_PACKAGE CLASS
*******************************************************************************
*******************************************************************************/
class ERROR_package : public Package
{
public:
	ERROR_package();

};




