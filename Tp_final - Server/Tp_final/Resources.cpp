#include "Resources.h"
#include <iostream>
#include "ScenarioEventsObserver.h"
#include "ScenarioDRAWObserver.h"
#include "LogicFSMGraphicEventsObserver.h"

Resources::Resources() {

	my_allegro_container = new Allegro();
	my_user_data = new Userdata();
	my_graphic_interface = new GraphicInterface();
};

Resources::~Resources() {  //Delete all the resources loaded
	delete my_scenario;
	delete my_drawer;
	delete my_allegro_container;
	delete my_user_data;
	delete my_communication;
	delete my_logic_event_handler;
	delete my_graphic_event_handler;
};


bool Resources::initialize_all_the_resources() {

	bool healthy_initialization = true;

	healthy_initialization = my_allegro_container->Init(*my_user_data);  //se puede ver de pedirla por allegro, el tema es que no estaría iniciado todavía

	my_graphic_interface->Init();
	//my_graphic_interface->print_messaje(INTRO);
	set_myUserData();

	if (healthy_initialization)
	{
		my_drawer = new DRAW();
		my_user_data->drawer = my_drawer;
		
		my_communication = new Communication(my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful

	
		if (my_user_data->my_network_data.is_client()) {
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_scenario = new Scene(my_user_data, CLIENT_PLAYER, SERVER_PLAYER);
			my_logic_fsm = new LogicClientFSM(my_user_data, my_logic_ev_gen, my_scenario, my_communication);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
		}
		else {
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_scenario = new Scene(my_user_data, SERVER_PLAYER, CLIENT_PLAYER);
			my_logic_fsm = new LogicServerFSM(my_user_data, my_logic_ev_gen, my_scenario, my_communication);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);	//tienen que estar aca por ahora para que las cosas internas de allegro se inicialicen correctamente
		}
		my_scenario->append_graphic_facility(my_drawer);

		my_graphic_fsm = new GraphicGameFSM(my_drawer);
		my_graphic_ev_gen = new GraphicEventGenerator();
		my_graphic_event_handler = new EventHandler(my_graphic_fsm, my_graphic_ev_gen);

		add_all_observers();
		game_running = true;			//starts running the game.
		my_scenario->gameInit();
	}

	//if (healthy_initialization)
		//my_graphic_interface->start_game_scenario_alt();
	return healthy_initialization;
}

bool Resources::initialize_all_the_resources(bool client)
{

	bool healthy_initialization = true;

	healthy_initialization = my_allegro_container->Init(*my_user_data);  //se puede ver de pedirla por allegro, el tema es que no estaría iniciado todavía
	my_user_data->my_network_data.handshake = false;
	my_user_data->my_network_data.set_client(client);

	if (healthy_initialization)
	{
		my_drawer = new DRAW();
		my_user_data->drawer = my_drawer;

		my_communication = new Communication(my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful

		if (my_user_data->my_network_data.is_client()) {
			my_scenario = new Scene(my_user_data, Item_type::NICK, Item_type::TOM);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_fsm = new LogicClientFSM(my_user_data, my_logic_ev_gen, my_scenario, my_communication);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
		}
		else {
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_scenario = new Scene(my_user_data, Item_type::TOM, Item_type::NICK);
			my_logic_fsm = new LogicServerFSM(my_user_data, my_logic_ev_gen, my_scenario, my_communication);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);	//tienen que estar aca por ahora para que las cosas internas de allegro se inicialicen correctamente
		}
		my_scenario->append_graphic_facility(my_drawer);

		my_graphic_fsm = new GraphicGameFSM(my_drawer);
		my_graphic_ev_gen = new GraphicEventGenerator();
		my_graphic_event_handler = new EventHandler(my_graphic_fsm, my_graphic_ev_gen);

		add_all_observers();
		game_running = true;			//starts running the game.
		my_scenario->gameInit();
	}

	return healthy_initialization;
}


void Resources::add_all_observers() {

	my_logic_fsm->add_observer(new LogicFSMGraphicEventsObserver(my_logic_fsm, my_graphic_ev_gen));

	my_scenario->add_observer(new ScenarioEventsObserver(my_logic_ev_gen, my_scenario, my_logic_fsm, my_user_data));
	my_scenario->add_observer(new ScenarioDRAWObserver(my_scenario, my_drawer));
}

void Resources::set_myUserData()
{
	string my_name;
	my_name = "hola";
	//my_name = my_graphic_interface->request_user_name();
	//my_user_data->my_network_data.my_name_is(my_name);

	/*
	string my_ip;
	my_name = my_graphic_interface->request_user_IP();
	my_user_data->my_network_data.my_name_is(my_ip);
	*/

	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_flip_display();
}

bool Resources::game_is_running() {
	return game_running;
}