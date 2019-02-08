#pragma once

#include <string>
#include <vector>
#include "DRAW.h"

#include "EventsCommunicationObserver.h"
#include "FSMEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "FSMSceneObserver.h"
#include "ScenarioEventsObserver.h"
#include "EventsCommunicationObserver.h"
#include "GraphicEventGenerator.h"
#include "EventHandler.h"

#include "LogicClientFSM.h"
#include "LogicServerFSM.h"
#include "GraphicGameFSM.h"
#include "Allegroclass.h"
#include "Userdata.h"
#include "Scene.h"
#include "Allegroclass.h"
#include "general.h"

class Resources
{
public:
	Resources();
	~Resources();  //Delete all the resources loaded

	//My Models
	Userdata* my_user_data;			//Pointer to manage the user data
	LogicFSM* my_logic_fsm;					//Pointer to manage the FSM
	GraphicGameFSM* my_graphic_fsm;
	Allegro * my_allegro_container;	//Pointer to manage allegro
	Scene* my_scenario;				//Pointer to manage the scenario


	//My Controllers
	EventHandler * my_logic_event_handler;
	EventHandler * my_graphic_event_handler;
	Communication * my_communication;  //Pointer to manage the communication

	DRAW* my_drawer;
	//Methods
	bool Intialize_all_the_resources();
	void add_all_observers( );


private:


};					



