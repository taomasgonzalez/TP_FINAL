#pragma once
#include "Package.h"
#include "Scene.h"
#include "Communication.h"
#include "EventGenerator.h"

class PackageInfo
{
public:
	PackageInfo(Package_type my_header, Scene * escenario, Communication* com, EventPackage* my_event_info);


	Package_type header;
	//NAME_IS
	uchar count;
	char * Name; // without terminator
	//MAP_IS
	char * map;
	char Checksum;
	//MOVE - ATTACK
	Character_type character;
	char destination_row;
	char destination_col;
	// ACTION REQUEST
	Action_type action;
	// ENEMY_ACTION
	uchar MonsterID;

};

