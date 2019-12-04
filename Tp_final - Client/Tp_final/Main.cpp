#include <iostream>

#include "Resources.h"


int main(void) {

	Resources my_resources = Resources();

	// if (!my_resources.initialize_all_the_resources()) {
	if (!my_resources.initialize_all_the_resources(true)) {
		printf("Error al inicializar los recursos\n");
		getchar();
		return 0;
	}
	// ahora salteo el handshake
	else {
		
	}
	my_resources.my_graphic_event_handler->get_ev_gen()->append_new_event(new GAME_START_EventPackage(), 0);

	string new_map = "FEPEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEPEEEEEEEFFEEFFFFFFFFFFEEFFEEPEEEEEEEEPEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	my_resources.my_scenario->load_new_map(my_resources.my_user_data->my_network_data.is_client(), new_map.c_str(), 18);

	while (my_resources.game_is_running()) {
		my_resources.my_logic_event_handler->handle_event();
		my_resources.my_graphic_event_handler->handle_event();
	}
	
	return 0;
}


