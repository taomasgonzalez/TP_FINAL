#include <iostream>

#include "Resources.h"


int main(void) {

	Resources my_resources = Resources();

	 //if (!my_resources.initialize_all_the_resources()) {
	if (!my_resources.initialize_all_the_resources(false)) {
		printf("Error al inicializar los recursos\n");
		getchar();
		return 0;
	}

	my_resources.my_graphic_event_handler->get_ev_gen()->append_new_event(new GAME_START_EventPackage(true), 0);


	//mapa para caida libre
	//string new_map = "FEEEEENTEEEEEEEFFEFFFFFFFFFFFFEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFFFFFFFFFFFF";

	//mapa para salto corto y largo
	//string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEFFFFFFFFFFFFEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";

	
	//mapa sin enemigos
	//string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";

	//mapa con un purple
	string new_map = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEPEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	
	my_resources.my_scenario->load_new_map(false,(const unsigned char *) new_map.c_str(), 18);

	while (my_resources.game_is_running()) {
		my_resources.my_logic_event_handler->handle_event();
		my_resources.my_graphic_event_handler->handle_event();
	}
	
	return 0;
}


