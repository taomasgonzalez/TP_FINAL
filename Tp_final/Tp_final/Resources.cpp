#include "Resources.h"
#include <iostream>
#include "CommunicationEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "LogicFSMEventsObserver.h"
#include "LogicFSMSceneObserver.h"
#include "ScenarioEventsObserver.h"
#include "ScenarioDRAWObserver.h"
#include "LogicFSMGraphicEventsObserver.h"

Resources::Resources() {

	this->my_allegro_container = new Allegro();
	this->my_user_data = new Userdata();
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

	if (healthy_initialization)
	{
		my_drawer = new DRAW();
		my_user_data->drawer = my_drawer;
		
		my_communication = new Communication(my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful

	
		if (my_user_data->my_network_data.is_client()) {
			my_logic_fsm = new LogicClientFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
			my_scenario = new Scene(my_user_data, Item_type::NICK, Item_type::TOM);
		}
		else {
			my_logic_fsm = new LogicServerFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);	//tienen que estar aca por ahora para que las cosas internas de allegro se inicialicen correctamente
			my_scenario = new Scene(my_user_data, Item_type::TOM, Item_type::NICK);			
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
			my_logic_fsm = new LogicClientFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
			my_scenario = new Scene(my_user_data, Item_type::NICK, Item_type::TOM);
		}
		else {
			my_logic_fsm = new LogicServerFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);	//tienen que estar aca por ahora para que las cosas internas de allegro se inicialicen correctamente
			my_scenario = new Scene(my_user_data, Item_type::TOM, Item_type::NICK);
		}
		my_scenario->append_graphic_facility(my_drawer);

		my_graphic_fsm = new GraphicGameFSM(my_drawer);
		my_graphic_ev_gen = new GraphicEventGenerator();
		my_graphic_event_handler = new EventHandler(my_graphic_fsm, my_graphic_ev_gen);

		add_all_observers();
		game_running = true;			//starts running the game.
		//my_scenario->gameInit();
	}

	return healthy_initialization;
	return false;
}


void Resources::add_all_observers() {

	my_communication->add_observer(new CommunicationEventsObserver(my_logic_ev_gen, my_communication, my_user_data));

	my_logic_fsm->add_observer(new FSMCommunicationObserver(my_logic_fsm,my_communication, my_scenario, my_user_data));
	my_logic_fsm->add_observer(new LogicFSMEventsObserver(my_logic_ev_gen, my_logic_fsm, my_allegro_container, my_user_data, my_scenario));
	my_logic_fsm->add_observer(new LogicFSMSceneObserver(my_logic_fsm, my_scenario, my_logic_ev_gen, my_user_data));
	my_logic_fsm->add_observer(new LogicFSMGraphicEventsObserver(my_logic_fsm, my_graphic_ev_gen));

	my_scenario->add_observer(new ScenarioEventsObserver(my_logic_ev_gen, my_scenario, my_logic_fsm, my_user_data));
	my_scenario->add_observer(new ScenarioDRAWObserver(my_scenario, my_drawer));
}

bool Resources::game_is_running() {
	return game_running;
}