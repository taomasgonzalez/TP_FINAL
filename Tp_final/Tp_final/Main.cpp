#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "general.h"
#include "Resources.h"


int main(void) {
	
	Resources* myResources = new Resources;		//Object that represents and allocs all the resources that are gonna be use
	

	if (myResources->Intialize_all_the_resources()) {	//Checks if the initialization was done properly

		EventHandler * my_event_handler = new EventHandler ((myResources->allegro_container), myResources->communication->is_client());

		myResources->add_all_observers( my_event_handler);

		myResources->scenario->gameInit(*myResources->my_user_data);

		while (!myResources->scenario->game_is_finished()) {
			my_event_handler->handle_event();
		}
	}
	else {

		std::cout << "Resources not loaded properly." << std::endl;
		delete myResources;   //for deleating all the loaded resources
	}

	return 0;
}


