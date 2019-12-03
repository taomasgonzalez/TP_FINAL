#include "LogicFSMSceneObserver.h"

#include "EventPackageFactory.h"

LogicFSMSceneObserver::LogicFSMSceneObserver(LogicFSM* fsm, Scene* scenario, LogicEventGenerator *event_gen, Userdata * userdata)
{
	this->my_fsm = fsm;
	this->my_scenario = scenario;
	this->my_event_gen = event_gen;
	this->my_user_data = userdata;
}

LogicFSMSceneObserver::~LogicFSMSceneObserver()
{
}

void LogicFSMSceneObserver::update() {

	if (my_fsm->end_game) {
		my_scenario->finish_game();
	}

	if (my_fsm->start_game) { //scene get´s noticed that the game has started, has to start executing actions
		my_scenario->initializing = false; // ya se hace desde main
	}

	if (my_fsm->ld_enemy_action) { //I´m the client, an EA arrived during initialization by networking, I must save it to run it later
		ENEMY_ACTION_EventPackage * info_EA = static_cast<ENEMY_ACTION_EventPackage*>(my_fsm->get_fsm_ev_pack());
		my_scenario->append_new_auxilar_event(info_EA->to_Action_info());
	}

	if (my_fsm->sv_enemy_action) { //I´m the server, EA generated before send it during initialization
		Action_info my_enemy_action_struct = my_scenario->give_me_my_enemy_action(true); //me devuelve * EA_info

		if (!my_enemy_action_struct.finished_loading)
		{
			my_scenario->append_new_auxilar_event(my_enemy_action_struct);  //cola de la struct y no EVPs
			my_event_gen->append_new_event(new ENEMY_ACTION_EventPackage(&my_enemy_action_struct), (int)EventGenerator::LogicQueues::soft); //has to be send to the client
		}
	}

	if (my_fsm->ex_saved_enemy_actions) //for both client and server
	{

		while (my_scenario->assistant_queue->size() >= 1) //Execute all the pending Enemy actions beacuse the game starts
		{			
			bool should_die = false;
			this->my_scenario->execute_action(&(my_scenario->assistant_queue)->front(), should_die);
			my_scenario->assistant_queue->pop();
		}
	}
	
	if (my_fsm->check_map) //I´m client and i receive a map from the server
	{
		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();
		MAP_IS_EventPackage*map_to_be_checked = (MAP_IS_EventPackage*)event_to_be_checked;

		if (!this->my_scenario->is_the_map_okay(map_to_be_checked->give_me_the_map(), map_to_be_checked->give_me_the_checksum()))//I must check it first
		{
				this->my_event_gen->empty_all_queues();
				this->my_event_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR if the map was corrupted in the trasmition
		}
		else
		{
			this->my_scenario->load_new_map(this->my_user_data->my_network_data.is_client(), map_to_be_checked->give_me_the_map(), map_to_be_checked->give_me_the_checksum()); //If the map is okay, the program proceeds to load it
			this->my_fsm->error_ocurred = false;
		}
	}

	if (my_fsm->check_action) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();
		Action_info acting_information;

		switch (event_to_be_checked->give_me_your_event_type())
		{
		case Event_type::MOVE:
		{
			MOVE_EventPackage * info_mo = static_cast<MOVE_EventPackage*>(event_to_be_checked);
			acting_information = info_mo->to_Action_info();
			break;
		}
		case Event_type::ATTACK:
		{
			ATTACK_EventPackage * info_attack = static_cast<ATTACK_EventPackage*>(event_to_be_checked);
			acting_information = info_attack->to_Action_info();
			break;
		}
		case Event_type::ACTION_REQUEST:
		{
			ACTION_REQUEST_EventPackage * info_actrequest = static_cast<ACTION_REQUEST_EventPackage*>(event_to_be_checked);
			acting_information = info_actrequest->to_Action_info();
			break;
		}
		case Event_type::ENEMY_ACTION:
		{
			ENEMY_ACTION_EventPackage * info_enemyact = static_cast<ENEMY_ACTION_EventPackage*>(event_to_be_checked);
			acting_information = info_enemyact->to_Action_info();
			break;
		}
		}

		if (!this->my_scenario->is_the_action_possible(&acting_information)) //mando a analizar el EventPackage 
			my_fsm->error_ocurred = true;
		else 
			my_fsm->set_fsm_ev_pack(EventPackageFactory().create_event_package(&acting_information));

	}

	if (my_fsm->ex_action)
	{
		if (!my_fsm->valid_extern_action)
		{
			this->my_event_gen->empty_all_queues();
			this->my_event_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR 
			my_fsm->error_ocurred = false;
		}
		else if (!my_fsm->valid_local_action)
		{
			(void)0; //ignore
			my_fsm->error_ocurred = false;
		}
		else //if it´s valid, it should be execute
			this->my_scenario->load_action_on_character(my_fsm->get_fsm_ev_pack()->to_Action_info());
	}



	if (my_fsm->we_won) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_win())
		{
			this->my_event_gen->empty_all_queues();
			this->my_fsm->error_ocurred = true; //so the program don´t ask the user if wants to play again
			this->my_event_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR 
		}	
	}

	if (my_fsm->we_lost) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_lose()) //mando a analizar el EventPackage sea local 
		{
			this->my_event_gen->empty_all_queues();
			this->my_fsm->error_ocurred = true; //so the program don´t ask the user if wants to play again
			this->my_event_gen->append_new_event(new ERROR_EventPackage(true), (int)LogicEventGenerator::LogicQueues::soft); //load ERROR 
		}

	}

	if (my_fsm->check_game_state) {

		this->my_scenario->check_current_game_situation();

	}

	if (my_fsm->ld_new_map) //i´m server, load the map from the txt
	{
		this->my_scenario->load_new_map(this->my_user_data->my_network_data.is_client()); 
	}
}

