#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include <string>
#include <array>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


enum class Direction_type
{
	Left, Right, Jump, Left_Stop, Right_Stop, Toggle
};

enum class Action_type { Move = 'M', Attack = 'A' };

enum class Character_id {
	Player, Enemy
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
	std::string my_name; //must have terminator
	std::string his_name; //must have terminator
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

