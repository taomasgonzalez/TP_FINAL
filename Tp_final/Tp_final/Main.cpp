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

GERMAN:
-Terminar ultimas rutinas de acción fsm
-Chequeo final fsm
-Terminar Scene con todos sus componentes y hacer parte lógica

TOMMY:
-Ver de como meter lo que hizo guido en el resto del programa manteniendolo modular.
Ver como aplicar Drawer, sería un controller que seria llamadao por un observer de la clase allegro y que tenga un ptr a scene, allegro y a userdata. allegrodata
(donde estarían cargados los recursos)
-Diferenciar bien backend de frontend en cuanto a la parte de allegro, yo lo veo más que scene es como la parte logica con las reglas del juego (BE) y la clase
allegro el FE con sus recursos

GUIDO:
- Hacer 10 mapas con el formato pedido(Ver anexo mapas en la consigna)
Fijate que hay un par(carpeta maapas, en este mismo repo) que yo hice pero en otro formato, capaz que te sirven. Que incremente la dificultad a medida que aumentan 
los niveles ya se por cantidad de enemigos y/o que sean más jodidos
-Cargar los CVs(mapas) en el programa.
Esto lo haces mediante manejo de archivos en la función const char * Scene::give_me_the_CSV(unsigned int actual_map) en Scene.cpp que tenes que hacer
Probala aparte y fijate que funcione, ahí agregala

-Hacer checksums
Tener que hacer los checksums de los mapas que vas cargando. Ver consigna(anexo)
Tenés que hacer la funcióon unsigned char Map::make_checksum(const char * CSV_map_location) en Map.cpp, probalo antes de agregarlo

-Terminar lo que quedo pendiente de la parte gráfica
Para que saques imagenes para probar, después buscamos unas copadas o vemos de donde las conseguimos
https://blogs.unity3d.com/es/2016/11/28/free-vfx-image-sequences-flipbooks/   explosiones, humo, etc
https://ezgif.com/split te convierte un gif en frames
https://www.google.com/imgres?imgurl=http%3A%2F%2F2.bp.blogspot.com%2F-nKig37YrFhs%2FVJHGE1zYaRI%2FAAAAAAAABaQ%2FyZX2Y8_YoPM%2Fs1600%2F0600.png&imgrefurl=http%3A%2F%2Fwww.voicelandia.pun.pl%2Fviewtopic.php%3Fpid%3D2884&docid=VuQQ77xfmDtjbM&tbnid=z3Ho3x4cXnRmxM%3A&vet=1&w=500&h=364&bih=608&biw=1366&ved=2ahUKEwjf19uOwYrgAhUvHLkGHfygAiUQxiAoA3oECAEQFw&iact=c&ictx=1
https://www.fg-a.com/crabs.shtml  cangrejos y otros
https://www.google.com/url?sa=i&source=images&cd=&cad=rja&uact=8&ved=2ahUKEwj7mLixwYrgAhXPE7kGHaQtBXIQjhx6BAgBEAM&url=http%3A%2F%2Fgravityfalls.wikia.com%2Fwiki%2FFile%3APaul_Robertson_Fight_Fighters_Rumble_down_kick.gif&psig=AOvVaw1FDT133ISODBUMrEO_onjr&ust=1548559904505002
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


