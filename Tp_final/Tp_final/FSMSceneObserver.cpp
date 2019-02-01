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

	if (my_fsm->start_game) { //scene get´s noticed that the game has started, has to start executing actions
		my_scenario->initializing =false;// ya se hace desde main
	}

	if (my_fsm->ld_enemy_action) { //I´m the client, an EA arrived during initialization by networking, I must save it to run it later
		my_scenario->append_new_auxilar_event(my_fsm->get_fsm_ev_pack()); 
	}

	if (my_fsm->sv_enemy_action) { //I´m the server, EA generated before send it during initialization
		EventPackage * my_enemy_action = my_scenario->give_me_my_enemy_action(true);;
		my_scenario->append_new_auxilar_event(my_enemy_action);
		my_fsm->load_fsm_ev_pack(my_enemy_action); //saves it in the FSM so it can be send to the client later
	}

	if (my_fsm->ex_saved_enemy_actions) //for both client and server
	{

		while (my_scenario->assistant_queue->size() >= 1) //Execute all the pending Enemy actions beacuse the game starts
		{			
			this->my_scenario->execute_action(my_scenario->assistant_queue->front());
			my_scenario->assistant_queue->pop();
		}
	}
	
	if (my_fsm->ex_action)
	{
		this->my_scenario->execute_action(this->my_fsm->get_fsm_ev_pack()); 
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
			this->my_fsm->error_ocurred = false;
		}
	}

	if (my_fsm->check_action) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->is_the_action_possible(event_to_be_checked))//mando a analizar el EventPackage 
		{
			//If the EventPackage is not valid, the program can take two paths depending on the origin of the action
			//If it is a local action, the action is incompatible with the current developing of the game like a move into a wall so it´s skipped
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

	if (my_fsm->check_local_action_request) //I´m client
	{
		EventPackage* action_request_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (this->my_scenario->is_the_action_possible(action_request_to_be_checked))//mando a analizar el EventPackage 
		{
			//If valid, it should be send by networking
			my_fsm->valid_local_action_request = true;
			//If the ActionRequest is not valid, the action is incompatible with the current developing of the game like a move into a wall so it´s skipped
		}

	}


	if (my_fsm->we_won) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_win(event_to_be_checked))
		{
			this->my_event_gen->empty_all_queues();
			this->my_fsm->error_ocurred = true; //so the program don´t ask the user if wants to play again
			this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true));
		}

		

	}

	if (my_fsm->we_lost) {

		EventPackage* event_to_be_checked = this->my_fsm->get_fsm_ev_pack();

		if (!this->my_scenario->did_we_lost(event_to_be_checked)) //mando a analizar el EventPackage sea local 
		{
			this->my_event_gen->empty_all_queues();
			this->my_fsm->error_ocurred = true; //so the program don´t ask the user if wants to play again
			this->my_event_gen->append_new_soft_event(new ERROR_EventPackage(true));
		}

	}

	if (my_fsm->ld_new_map) //i´m server, load the map from the txt
	{
		this->my_scenario->load_new_map(this->my_user_data->my_network_data.is_client()); 
	}
}