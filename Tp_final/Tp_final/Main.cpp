#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "parseCmdLine.h"
#include "parser.h"
#include "general.h"
#include "EventHandler.h"
#include "Allegroclass.h"
#include "Userdata.h"
#include "Scene.h"
#include "Allegroclass.h"
#include "Drawer.h"

#include "CommunicationEventsObserver.h"
#include "FSMEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "FSMSceneObserver.h"
#include "ScenarioEventsObserver.h"
#include "EventsCommunicationObserver.h"

void add_all_observers();


int main(int argc, char *argv[]) {
	infoType myData;
	pCallback functionPtr = &parseCallback;
	Drawer drawing_manager;
	Scene scenario = Scene();
	Event Event = Event::NO_EVENT;
	Userdata data_container;
	Allegro allegro_container;

	Communication *com = new Communication(myData.ip);
	
	if (allegro_container.Init(data_container)) {

		EventHandler event_handler(&allegro_container, com->is_client());

		//add_all_observers();
		scenario.add_observer(&drawing_manager);
		com->add_observer(new CommunicationEventsObserver(&event_handler, com));
		event_handler.add_observer(new FSMEventsObserver(&event_handler, &event_handler));
		event_handler.add_observer(new FSMCommunicationObserver(&event_handler, com));
		event_handler.add_observer(new FSMSceneObserver(&event_handler, &scenario));
		event_handler.add_observer(new EventsCommunicationObserver(&event_handler, com));
		scenario.add_observer(new ScenarioEventsObserver(&event_handler, &scenario));

		scenario.gameInit(data_container, &myData);
		while (!scenario.game_is_finished()) {
			event_handler.handle_event();
		}
	}
	else
		std::cout << "Resources not loaded properly." << std::endl;
	return 0;
}

void add_all_observers() {

}