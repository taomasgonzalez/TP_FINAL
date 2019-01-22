#pragma once

#include <string>
#include <vector>
#include "EventsCommunicationObserver.h"
#include "FSMEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "FSMSceneObserver.h"
#include "ScenarioEventsObserver.h"
#include "EventsCommunicationObserver.h"
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

	Communication * communication;  //Pointer to manage the communication
	Allegro * allegro_container;	//Pointer to manage allegro
	Drawer* drawing_manager;		//Pointer to manage the drawer
	Scene* scenario;				//Pointer to manage the scenario
	Userdata* my_user_data;			//Pointer to manage the user data


	bool Intialize_all_the_resources();
	void add_all_observers( EventHandler* myUserData);


private:


};					



