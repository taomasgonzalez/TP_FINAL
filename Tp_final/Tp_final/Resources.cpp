#include "Resources.h"

#include "CommunicationEventsObserver.h"
#include "FSMCommunicationObserver.h"
#include "LogicFSMEventsObserver.h"
#include "LogicFSMSceneObserver.h"
#include "ScenarioEventsObserver.h"

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
		my_scenario = new Scene();			//tienen que estar aca por ahora para que las cosas internas de allegro se inicialicen correctamente
		my_scenario->append_graphic_facility(my_drawer);

		my_communication = new Communication(my_user_data);  //Initialize the communication
		healthy_initialization = this->my_communication->is_the_connection_healthy();  //Checks if the communication process was successful

		if (my_user_data->my_network_data.is_client()) {
			my_logic_fsm = new LogicClientFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
		}
		else {
			my_logic_fsm = new LogicServerFSM(my_user_data);
			my_logic_ev_gen = new LogicEventGenerator(my_allegro_container, my_user_data);
			my_logic_event_handler = new EventHandler(my_logic_fsm, my_logic_ev_gen);
		}

		my_graphic_fsm = new GraphicGameFSM(my_user_data, my_drawer);
		my_graphic_ev_gen = new GraphicEventGenerator(my_allegro_container, my_user_data);
		my_graphic_event_handler = new EventHandler(my_graphic_fsm, my_graphic_ev_gen);

		add_all_observers();
		game_running = true;			//starts running the game.
	}

	return healthy_initialization;
};

void Resources::add_all_observers() {

	my_communication->add_observer(new CommunicationEventsObserver(my_logic_ev_gen, my_communication, my_user_data));
	my_logic_fsm->add_observer(new FSMCommunicationObserver(my_logic_fsm,my_communication, my_scenario, my_user_data));
	my_logic_fsm->add_observer(new LogicFSMEventsObserver(my_logic_ev_gen, my_logic_fsm, my_allegro_container, my_user_data, my_scenario));
	my_logic_fsm->add_observer(new LogicFSMSceneObserver(my_logic_fsm, my_scenario, my_logic_ev_gen, my_user_data));
	my_scenario->add_observer(new ScenarioEventsObserver(my_logic_ev_gen, my_scenario, my_logic_fsm, my_user_data));

}

bool Resources::game_is_running() {
	return game_running;
}