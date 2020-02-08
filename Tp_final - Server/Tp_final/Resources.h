#pragma once

#include <string>
#include <vector>
#include "DRAW.h"

#include "GraphicEventGenerator.h"
#include "LogicEventGenerator.h"
#include "EventHandler.h"

#include "Communication.h"
#include "LogicClientFSM.h"
#include "LogicServerFSM.h"
#include "GraphicGameFSM.h"
#include "Allegroclass.h"


#include "Userdata.h"
#include "Scene.h"
#include "Allegroclass.h"
#include "general.h"
#include "EventHandler.h"
#include "GraphicInterface.h"


class Resources
{
public:
	Resources();
	~Resources();  //Delete all the resources loaded

	//My Models
	Userdata* my_user_data;			//Pointer to manage the user data

	Allegro * my_allegro_container = NULL;	//Pointer to manage allegro

	GraphicInterface* my_graphic_interface = NULL; //Pointer to manage de graphic interface

	//My Controllers
	EventHandler * my_logic_event_handler = NULL;
	EventHandler * my_graphic_event_handler = NULL;

	bool initialize_all_the_resources();
	bool initialize_all_the_resources(bool client);

	bool game_is_running();
	Scene * my_scenario = NULL;				//Pointer to manage the scenario

private:	
	/*
		once resources are initialized, the game will start running
		this boolean indicates whether the game is running or not, independent of the state of the gameplay:
		being in menu state will also mean game_running = true;
	*/
	bool game_running = false;

	DRAW* my_drawer = NULL;
	Communication * my_communication = NULL;  //Pointer to manage the communication
	LogicFSM* my_logic_fsm = NULL;
	LogicEventGenerator* my_logic_ev_gen = NULL;
	GraphicGameFSM * my_graphic_fsm = NULL;
	GraphicEventGenerator* my_graphic_ev_gen = NULL;

	//Methods
	void add_all_observers();
	void set_myUserData();
};					



