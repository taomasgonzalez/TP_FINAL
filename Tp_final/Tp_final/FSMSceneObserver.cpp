#include "FSMSceneObserver.h"



FSMSceneObserver::FSMSceneObserver(FSM* fsm, Scene* scenario,EventGenerator *event_gen, Userdata * userdata)
{
	this->my_fsm = fsm;
	this->my_scenario = scenario;
	this->my_event_gen = event_gen;
	this->my_user_data = userdata;
}


FSMSceneObserver::~FSMSceneObserver()
{
}

void FSMSceneObserver::update() {
	if (my_fsm->end_game) {
		my_scenario->finish_game();
	}
	if (my_fsm->start_game) { //ver que onda en el caso de play again
		//scenario->gameInit();// ya se hace desde main
	}
	if (my_fsm->check_map) //I´m client and i receive a map from the server
	{
		EventPackage* map_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->is_the_map_okay(map_to_be_checked))//I must check it first
		{
				this->my_event_gen->empty_all_queues();
				this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true)); //load ERROR if the map was corrupted in the trasmition
		}
		else
		{
			this->my_scenario->load_new_map(this->my_user_data->my_network_data.is_client(), map_to_be_checked); //If the map is okay, the program proceeds to load it
			this->my_fsm->s_ack = true;
		}
	}

	if (my_fsm->check_action) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->is_the_action_possible(event_to_be_checked))//mando a analizar el EventPackage 
		{
			//If the EventPackage is not valid, the program can take two paths depending on the origin of the action
			//If it is a local action, the action is incompatible with the current developing of the game like a move into a wall
			//If it´s a extern action, a corruption in the received package has ocurred beacause a computer can not send invalid plays
			//thus, we send an error.
			if (event_to_be_checked->is_this_a_local_action() == false)
			{
				this->my_event_gen->empty_all_queues();
				this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true));
			}

		}
		else
			this->my_scenario->execute_action(event_to_be_checked); //The action is instantly executed if it´s valid
	}

	if (my_fsm->we_won) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_win(event_to_be_checked))
		{
			this->my_event_gen->empty_all_queues();
			this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true));
		}

		else
			this->my_event_gen->append_new_soft_event(new WE_WON_EventPackage(true));

	}

	if (my_fsm->we_lost) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_lost(event_to_be_checked)) //mando a analizar el EventPackage sea local 
		{
			this->my_event_gen->empty_all_queues();
			this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true));
		}

		else
			this->my_event_gen->append_new_soft_event(new GAME_OVER_EventPackage(true));

	}

	if (my_fsm->load_new_map) //i´m server, load the map from the txt
	{
		this->my_scenario->load_new_map(this->my_user_data->my_network_data.is_client()); 
	}
}