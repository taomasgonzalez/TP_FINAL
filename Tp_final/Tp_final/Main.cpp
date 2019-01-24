#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "general.h"
#include "Resources.h"

/*
TO DO:
-CONSTRUCTORES DE EVENTPACKAGES NUEVOS, VER NUEVOS EVENTOS
-CHEQUEO GENERAL DEL FLUJO DEL PROGRAMA
-FALTAN HACER ALGUNAS RUTINAS DE ACCIÓN
-HACER LISTA DE IMPLEMENTACIONES QUE FALTAN
-COMPLETAR ELEMENOS DE ESCENA LOGICOS Y UNIRLO CON LA PARTE GRÁFICA
-HACER MENUES
-VER DE IMPLEMENTAR WRAP DE ALLEGRO

*/
int main(void) {
	
	Resources* myResources = new Resources;		//Object that represents and allocs all the resources that are gonna be use
	

	if (myResources->Intialize_all_the_resources()) {	//Checks if the initialization was done properly

		myResources->my_scenario->gameInit();

		while (!myResources->my_scenario->game_is_finished()) {
			myResources->my_event_handler->handle_event();
		}
	}
	else {

		std::cout << "Resources not loaded properly." << std::endl;
		delete myResources;   //for deleating all the loaded resources
	}

	return 0;
}


