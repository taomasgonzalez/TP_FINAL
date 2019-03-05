#include <iostream>

#include "Resources.h"


int main(void) {

	Resources my_resources = Resources();

	if (!my_resources.initialize_all_the_resources()) {
		printf("Error al inicializar los recursos\n");
		getchar();
		return 0;
	}

	while (my_resources.game_is_running()) {
		my_resources.my_logic_event_handler->handle_event();
		my_resources.my_graphic_event_handler->handle_event();
	}

	return 0;
}


