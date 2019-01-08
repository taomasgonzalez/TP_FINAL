#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include <string>
#include <array>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#define JUMP_MUSIC "Super Mario Bros - Jump Sound Effect.wav"

enum class Direction
{
	Left, Right, Jump, Left_Stop, Right_Stop, Toggle
};

enum class Action_type { Move = 'M', Attack = 'A' };

enum class Character_id {
	Player, Enemy
};

class Userdata
{
public:
	Userdata();
	~Userdata();
	void LoadWormImages();


	static const int GroundLevel = 616;
	static const int LeftWall = 685;
	static const int RightWall = 1170;
	/*
	static std::array<ALLEGRO_BITMAP*, 15> WormWalk; //Worm walk bitmaps
	std::string str = "wwalk-F";
	std::string ng = ".png";

	static std::array<ALLEGRO_BITMAP*, 10> WormJump; //Worm jump bitmaps
	std::string STR = "wjump-F";
	std::string NG = ".png";

	static ALLEGRO_BITMAP *Background;
	static ALLEGRO_BITMAP *WindowsBackground;

	//Worm 1 keys
	static const unsigned int worm1KeySet[TotalActions];

	//Worm 2 keys
	static const unsigned int worm2KeySet[TotalActions];
	*/
};

