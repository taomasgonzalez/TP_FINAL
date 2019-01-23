#pragma once

#include <string>
#include <vector>
#include "EventsCommunicationObserver.h"
#include "FSMEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "FSMSceneObserver.h"
#include "ScenarioEventsObserver.h"
#include "EventsCommunicationObserver.h"
#include "ScenarioDrawingObserver.h"
#include "EventHandler.h"
#include "Allegroclass.h"
#include "Userdata.h"
#include "Scene.h"
#include "Allegroclass.h"
#include "Drawer.h"
#include "general.h"

class Resources
{
public:
	Resources();
	~Resources();  //Delete all the resources loaded

	//My Models
	Userdata* my_user_data;			//Pointer to manage the user data
	FSM* my_fsm;					//Pointer to manage the FSM
	Allegro * my_allegro_container;	//Pointer to manage allegro
	Scene* my_scenario;				//Pointer to manage the scenario

	//My Controllers
	EventHandler * my_event_handler;
	Communication * my_communication;  //Pointer to manage the communication
	Drawer* my_drawing_manager;		//Pointer to manage the drawer

	//Methods
	bool Intialize_all_the_resources();
	void add_all_observers( );


private:


};					



