#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "general.h"
#include "Resources.h"

/*
TO DO:
-CHEQUEO GENERAL DEL FLUJO DEL PROGRAMA
-BUSCAR DONDE LIBERAR MEMORIA DE LOS PAQUETES Y TODO ESO
-FALTAN HACER ALGUNAS RUTINAS DE ACCIÓN
-HACER LISTA DE IMPLEMENTACIONES QUE FALTAN
-COMPLETAR ELEMENtOS DE ESCENA LOGICOS Y UNIRLO CON LA PARTE GRÁFICA
-HACER MENUES
-VER DE IMPLEMENTAR WRAP DE ALLEGRO
-Scene::is_the_action_possible(PAcakge *) analiza el paquete que llega por netwoking a ver si es válido
-Chequeo de movimiento posible dentro de model allegro, cuando se genera el allegro event (ver implementaciones en otros tps)
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


