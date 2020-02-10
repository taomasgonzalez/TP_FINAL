#include "PlayerActionsFSM.h"

void player_revive(void* data);
void start_pushing_r(void* data);

void check_push_and_push(void* data);
void reset_push(void* data);
void iddle_graph_player(void* data);
void stop_inmunity_graph_player(void *data);

void respawn_graph_player(void* data);
void player_die(void*data);

void do_nothing_player_r(void* data);
void stop_inmunity_r(void* data);

void do_nothing_player_r(void* data) {

}


void stop_inmunity_r(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;

	stop_inmunity_graph_player(data);
	fsm->stop_inmunity();
}


PlayerActionsFSM::PlayerActionsFSM(Player* player): CharacterActionsFSM(player)
{
	this->player = player;

	set_states();
	set_processes();
	create_all_timers();
	this->actual_state = iddle_state;

	this->player_ev_queue = al_create_event_queue();
	respawn_timer = al_create_timer(RESPAWN_TIME);
	inmune_timer = al_create_timer(INMUNE_TIME);

	al_register_event_source(this->player_ev_queue, al_get_timer_event_source(this->inmune_timer));
	al_register_event_source(this->player_ev_queue, al_get_timer_event_source(this->respawn_timer));

}

PlayerActionsFSM::~PlayerActionsFSM()
{
	delete pushing_state;
}

void PlayerActionsFSM::run_fsm(EventPackage * ev_pack) {

	update_from_allegro_timers_for_player();

	FSM::run_fsm(ev_pack);
}


void PlayerActionsFSM::update_from_allegro_timers_for_player() {

	//move toda la info de los timers aca, sacalas del observer


	//guido ac� levantas los eventos, hace una sola cola si total no te
	ALLEGRO_EVENT  allegroEvent;

	while (al_get_next_event(player_ev_queue, &allegroEvent))
	{
		if (allegroEvent.timer.source == respawn_timer)
		{
			std::cout << "Pasaron 5 segundos, el jugador respaunea" << std::endl;
			al_stop_timer(respawn_timer);//the timer is stopped

			player->ev_handler->get_ev_gen()->append_new_event(new REVIVE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);

			al_start_timer(inmune_timer);
		}

		else if (allegroEvent.timer.source == inmune_timer) 
		{

			std::cout << "Pasaron 3 segundos, el jugador deja de estar inmune" << std::endl;
			al_stop_timer(inmune_timer);//the timer is stopped

			player->ev_handler->get_ev_gen()->append_new_event(new STOP_INMUNITY_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);

		}
	}

	//una vez que terminas lo appendeas
	//ev_gen->append_new_event(event, (int)EventGenerator::LogicQueues::soft);

	//entonces entr�s al run_fsm original con el envento cargado ya que lo vas agarrar recien en el siguiente ciclo porque ya paso el fetch_event
}

void PlayerActionsFSM::revive_player() {
	player->revive();
}

void PlayerActionsFSM::stop_inmunity() {

	player->set_the_player_inmunity(false);
}



void PlayerActionsFSM::set_states() {

	pushing_state = new std::vector<edge_t>();

	expand_state(iddle_state, { Event_type::PUSHED, pushing_state, start_pushing_r });
	expand_state(iddle_state, { Event_type::DIED, dead_state, player_die });

	expand_state(walking_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_state, { Event_type::DIED, dead_state, player_die });
	expand_state(jumping_forward_state, { Event_type::DIED, dead_state, player_die });
	expand_state(falling_state, { Event_type::DIED, dead_state, player_die });
	expand_state(attacking_state, { Event_type::DIED, dead_state, player_die });

	expand_state(walking_state, { Event_type::STOP_INMUNITY, walking_state, stop_inmunity_r });
	expand_state(jumping_state, { Event_type::STOP_INMUNITY, jumping_state, stop_inmunity_r });
	expand_state(jumping_forward_state, { Event_type::STOP_INMUNITY, jumping_forward_state, stop_inmunity_r });
	expand_state(falling_state, { Event_type::STOP_INMUNITY, falling_state, stop_inmunity_r });
	expand_state(attacking_state, { Event_type::STOP_INMUNITY, attacking_state, stop_inmunity_r });
	expand_state(iddle_state, { Event_type::STOP_INMUNITY, iddle_state, stop_inmunity_r });


	pushing_state->push_back({ Event_type::MOVE, pushing_state, check_push_and_push });
	pushing_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_push });
	pushing_state->push_back({ Event_type::DIED, dead_state, get_routine(iddle_state,Event_type::DIED) });
	pushing_state->push_back({ Event_type::STOP_INMUNITY, pushing_state, stop_inmunity_r });
	pushing_state->push_back({ Event_type::END_OF_TABLE, pushing_state, do_nothing_player_r });



	expand_state(dead_state, { Event_type::REVIVED, iddle_state, player_revive });
}

void PlayerActionsFSM::create_all_timers() {
}

void PlayerActionsFSM::set_processes() {

	pushing_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	pushing_left_process.push_back(std::make_pair(Direction_type::Left, 0));
}


void PlayerActionsFSM::start_pushing() {
	obs_info.start_pushing_graph = true;
	notify_obs();
	obs_info.start_pushing_graph = false;

	PUSHED_EventPackage * curr_push = (PUSHED_EventPackage*)get_fsm_ev_pack();

	if (curr_push->pushing_direction == Direction_type::Jump_Right) 
		set_curr_process(&pushing_right_process);
	else if (curr_push->pushing_direction == Direction_type::Jump_Left) 
		set_curr_process(&pushing_left_process);

}

void player_revive(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	respawn_graph_player(data);
	fsm->revive_player();
}
void player_die(void* data) {

	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->kill_player();

}

void PlayerActionsFSM::kill_player() {

	obs_info.dying_graph = true;
	notify_obs();
	obs_info.dying_graph = false;

	player->die();

	//If the player has lives, the player respawns
	if (player->has_lives())
	{
		al_start_timer(respawn_timer);
	}
		player->set_the_player_inmunity(true);

}

void start_pushing_r(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->start_pushing();
}

void check_push_and_push(void* data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	
}
void reset_push(void* data) {
	iddle_graph_player(data);
}

void iddle_graph_player(void *data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->obs_info.reset_graph = true;
	fsm->notify_obs();
	fsm->obs_info.reset_graph = false;
}

void respawn_graph_player(void *data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->obs_info.respawn_graph = true;
	fsm->notify_obs();
	fsm->obs_info.respawn_graph = false;
}

void stop_inmunity_graph_player(void *data) {
	PlayerActionsFSM* fsm = (PlayerActionsFSM*)data;
	fsm->obs_info.stop_inmunity_graph = true;
	fsm->notify_obs();
	fsm->obs_info.stop_inmunity_graph = false;
}





