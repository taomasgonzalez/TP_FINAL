#pragma once

#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include <string>
#include <array>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
class DRAW;


enum class Thing_Type { PLAYER, ENEMY, PROYECTILE, FLOOR };

enum class Sense_type {Right, Left, None};

enum class Direction_type{Right, Left, Jump_Straight, Jump_Left, Jump_Right , Down, None};

enum class Action_type { 
	Move = 'M', Attack = 'A' };

enum class Character_id {
	Player, Enemy
};

enum class Item_type {
	TOM = 'T', NICK = 'N', PURPLE_GUY = 'P', GREEN_FATTIE = 'G', CRAZY = 'C', FLOOR = 'F', NADA = 'E', FIREBALL = 'B', SNOWBALL = 'S'
};

class NetworkData {

public:
	NetworkData();
	//Getters
	std::string give_me_my_ip();
	std::string give_me_his_ip();

	std::string give_me_my_name();
	void tell_me_his_name(char * his_name, unsigned char his_name_length);
	bool get_should_check_for_new_messages();
	bool has_new_info();
	bool is_client();

	//setters
	void set_client(bool is_client);
	void set_should_check_for_new_messages(bool should_check);



private:
	std::string my_ip = "";
	std::string his_ip = "";
	bool client_mode;		//By default we try to connect as a client
	bool new_info = false;
	bool check_for_new_messages;
	std::string my_name = "Eberto"; //must have terminator
	std::string his_name = "Juacho"; //must have terminator
};


class Userdata
{
public:
	Userdata();
	~Userdata();

	NetworkData my_network_data;
	static DRAW *drawer;

};

