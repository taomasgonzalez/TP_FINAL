#pragma once
#include "Communication.h"
#include "FSM_Class.h"

class FSMCommunicationObserver: public Observer
{
public:
	FSMCommunicationObserver(Fsm * fsm, Communication * com);
	~FSMCommunicationObserver();

	virtual void update();
private:
	Fsm * fsm;
	Communication * com;
	Scene * scenario;
};

struct PackageInfo
{

	Package_type header;
	//NAME_IS
	uchar count;
	char * Name; // without terminator
	//MAP_IS
	char * map;
	char Checksum  0;
	//MOVE - ATTACK
	Character_type character;
	char destination_row;
	char destination_column;
	// ACTION REQUEST
	Action_type action;
	// ENEMY_ACTION
	uchar MonsterID;

};

