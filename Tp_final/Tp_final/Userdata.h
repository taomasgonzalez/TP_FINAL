#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include <string>
#include <array>
#include "EventPackage.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


enum class Direction_type
{
	Left, Right, Jump_Straight, Jump_Left, Jump_Right , None
};

enum class Action_type { 
	Move = 'M', Attack = 'A' };

enum class Character_id {
	Player, Enemy
};

enum class Item_type {
	TOM = 'T', NICK = 'N', PURPLE_GUY = 'P', GREEN_FATTIE = 'G', CRAZY = 'C', FLOOR = 'F', NADA = 'E', FIREBALL = 'B', SNOWBALL = 'S'
};

class Action_info {

public:
	Action_info(ENEMY_ACTION_EventPackage* trasnlate_please);
	Action_info();
	bool is_local;
	bool finished_loading; //For ENEMYS_LOADED_EventPackage
	unsigned int id;
	int final_pos_x;
	int final_pos_y;
	Action_type action;
	bool valid = false;
};

class NetworkData {

public:

	//Getters
	std::string give_me_my_ip();
	std::string give_me_my_name();
	void tell_me_his_name(char * his_name, unsigned char his_name_length);
	bool get_should_check_for_new_messages();
	bool has_new_info();
	bool is_client();

	//setters
	void set_client(bool is_client);
	void set_should_check_for_new_messages(bool should_check);



private:
	std::string my_ip;
	std::string his_ip;
	bool client_mode;		//By default we try to connect as a client
	bool new_info = false;
	bool check_for_new_messages;
	std::string my_name="Eberto"; //must have terminator
	std::string his_name="Juacho"; //must have terminator
};

class AllegroData {

public:
	
	void LoadWormImages(); //replace with the images of the graphics elements of the game


	static const int GroundLevel = 616;
	static const int LeftWall = 685;
	static const int RightWall = 1170;


	static std::array<ALLEGRO_BITMAP*, 15> WormWalk; //Worm walk bitmaps
	std::string str = "wwalk-F";
	std::string ng = ".png";

	static std::array<ALLEGRO_BITMAP*, 10> WormJump; //Worm jump bitmaps
	std::string STR = "wjump-F";
	std::string NG = ".png";

	static ALLEGRO_BITMAP *Background;
	static ALLEGRO_BITMAP *WindowsBackground;

	//Worm 1 keys
	static const unsigned int worm1KeySet[2];

	//Worm 2 keys
	static const unsigned int worm2KeySet[2];
private:

};

class Userdata
{
public:
	Userdata();
	~Userdata();

	NetworkData my_network_data;
	AllegroData my_allegro_data;



};

