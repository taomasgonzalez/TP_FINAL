#include "EnemyActionsFSM.h"



void do_nothing_enemy_r(void* data);
void got_hit_r(void* data);
void partially_unfroze_r(void* data);
void froze_r(void* data);
void unfreeze_r(void* data);
void unfroze_r(void* data);
void start_charging_r(void* data);
void snowball_move_r(void* data);
void enemy_die_r(void* data);
void start_got_hit_r(void*data);
void fall_and_start_got_hit_r(void* data);
void renew_hits_r(void* data);

EnemyActionsFSM::EnemyActionsFSM(Enemy* enemy): CharacterActionsFSM(enemy)
{
	this->enemy = enemy;

	set_states();
	set_processes();
	actual_state = iddle_state;
	create_all_timers();

	this->defrost_queue = al_create_event_queue();

	al_register_event_source(this->defrost_queue, al_get_timer_event_source(this->freezing_timer));
	al_register_event_source(this->defrost_queue, al_get_timer_event_source(this->frozen_timer));
}

void EnemyActionsFSM::run_fsm(EventPackage * ev_pack) {

	update_from_allegro_timers_for_enemy();

	FSM::run_fsm(ev_pack);
}

EnemyActionsFSM::~EnemyActionsFSM()
{
	delete freezing_state;
	delete frozen_state;
}

void EnemyActionsFSM::update_from_allegro_timers_for_enemy() {

	ALLEGRO_EVENT  allegroEvent;

	while (al_get_next_event(defrost_queue, &allegroEvent))
	{
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			handle_hits(allegroEvent);
	}

	//una vez que terminas lo appendeas
	//ev_gen->append_new_event(event, (int)EventGenerator::LogicQueues::soft);

	//entonces entr�s al run_fsm original con el envento cargado ya que lo vas agarrar recien en el siguiente ciclo porque ya paso el fetch_event
}

void EnemyActionsFSM::set_states()
{
	freezing_state = new std::vector<edge_t>();
	frozen_state = new std::vector<edge_t>();

	expand_state(iddle_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });
	expand_state(walking_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });
	expand_state(jumping_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });
	expand_state(jumping_forward_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });
	expand_state(attacking_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });
	expand_state(falling_state, { Event_type::GOT_HIT, freezing_state, got_hit_r });


	//Eventually we can do two different enemy_die_r, one for GOT_SMAHED and other for SNOWBALL_BREAKDOWN
	expand_state(iddle_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(walking_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(jumping_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(jumping_forward_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(attacking_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(falling_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r }); //PRODUCE UNA ANIMACI�N DISTINTA A LA de morir, hay dos formas de morir
	//una siendo aplastado por una bola que sal�s volando y otra desaparecer con la bola, que no es una animaci�n de muerte, s�lo desapareces vos con la bola

	expand_state(snowballed_state, { Event_type::SNOWBALL_BREAKDOWN, dead_state, enemy_die_r });


	freezing_state->push_back({ Event_type::GOT_HIT, freezing_state, got_hit_r });
	freezing_state->push_back({ Event_type::FROZE, frozen_state, froze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFREEZE, iddle_state, unfreeze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, freezing_state, do_nothing_enemy_r });

	frozen_state->push_back({ Event_type::UNFROZE, freezing_state, unfroze_r });
	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, renew_hits_r });
	frozen_state->push_back({ Event_type::CHARGING, snowballed_state, start_charging_r });
	frozen_state->push_back({ Event_type::ROLLING, frozen_state, snowball_move_r }); //FALTA
	frozen_state->push_back({ Event_type::END_OF_TABLE, frozen_state, do_nothing_enemy_r });


	actual_state = iddle_state;
}


void EnemyActionsFSM::set_processes() {

	rolling_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	rolling_left_process.push_back(std::make_pair(Direction_type::Left, 0));

}

void EnemyActionsFSM::create_all_timers() {
	freezing_timer = al_create_timer(FREEZING_TIME);
	frozen_timer = al_create_timer(FROZEN_TIME);
}

void EnemyActionsFSM::partially_unfroze()
{
	switch (enemy->amount_of_hits_taken)
	{

	case 0://nunca va a caer aca no? porque antes en got_hit minimo aumentaste uno
		break;
	case 1:
		enemyObs_info.start_freezing_state1_graph = true;
   		notify_obs();
		enemyObs_info.start_freezing_state1_graph = false;
		break;
	case 2:
		enemyObs_info.start_freezing_state2_graph = true;
		notify_obs();
		enemyObs_info.start_freezing_state2_graph = false;
		break;

	default:
		std::cout << "EnemyActionsFSM::partially_unfroze() default amount of hits, CHECK" << endl;
		break;
	}
}

void EnemyActionsFSM::unfreeze()
{
	start_iddle();
}

void EnemyActionsFSM::froze()
{
	start_frozen_timer();

}

void EnemyActionsFSM::start_charging()
{

	enemy->ev_handler->get_ev_gen()->append_new_event(new CHARGING_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);

	enemyObs_info.start_ballCharging_graph = true;
	notify_obs();
	enemyObs_info.start_ballCharging_graph = false;
}


void EnemyActionsFSM::timer_unfroze()
{
	al_stop_timer(frozen_timer);
	enemy->ev_handler->get_ev_gen()->append_new_event_front(new UNFROZE_EventPackage());

}




void EnemyActionsFSM::unfroze()
{
	enemy->amount_of_hits_taken = 2;
	enemy->set_rolling(false);

	enemyObs_info.start_freezing_state2_graph = true;
	notify_obs();
	enemyObs_info.start_freezing_state2_graph = false;
}



ALLEGRO_TIMER * EnemyActionsFSM::get_frozen_timer()
{
	return frozen_timer;
}

ALLEGRO_TIMER * EnemyActionsFSM::get_freezing_timer()
{
	return freezing_timer;
}

void EnemyActionsFSM::got_hit() {
	
	enemy->be_hit();

	switch (enemy->amount_of_hits_taken)
	{
	case 0:
		std::cout << "ERROR, debería tener al menos un hit porque estoy en freezing, no cero" << std::endl;
		break;

	case 1:
		enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	case 2:
		enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	case 3:
		enemy->ev_handler->get_ev_gen()->append_new_event(new FROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	default:
		std::cout << "EnemyActionsFSM::got_hit() Awkward amount of hits, CHECK" << std::endl;
		break;
	}

}
void EnemyActionsFSM::start_got_hit() {

	enemy->be_hit();
	enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_FROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);


}

void EnemyActionsFSM::start_freezing_timer()
{
	al_start_timer(freezing_timer);
}

void EnemyActionsFSM::start_frozen_timer()
{
	al_start_timer(frozen_timer);
}

void do_nothing_enemy_r(void* data) {

}
void got_hit_r(void* data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*) data;
	fsm->got_hit();
}

void start_got_hit_r(void*data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->start_got_hit();
}

void unfreeze_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->unfreeze();
}


void fall_and_start_got_hit_r(void*data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->start_got_hit();
}

void renew_hits_r(void*data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->renew_frosting();
}

void EnemyActionsFSM::renew_frosting() {
	al_start_timer(frozen_timer);
}

void EnemyActionsFSM::handle_hits(ALLEGRO_EVENT all_ev)
{
	if (all_ev.timer.source == frozen_timer)
	{
		timer_unfroze();
		al_start_timer(freezing_timer);
	}

	else if (all_ev.timer.source == freezing_timer)
	{
		timer_unfreeze();
	}
}

void EnemyActionsFSM::timer_unfreeze()
{

	switch (--(enemy->amount_of_hits_taken))
	{
	case 0:
		al_stop_timer(freezing_timer);
		enemy->ev_handler->get_ev_gen()->append_new_event(new UNFREEZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	case 1: 
		al_start_timer(freezing_timer);
		enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	case 2:
		al_start_timer(freezing_timer);
		enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		break;

	default:
		std::cout << "EnemyActionsFSM::timer_unfreeze() Awkward amount of hits, CHECK" << std::endl;
		break;
	}

}



void partially_unfroze_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->partially_unfroze();
}
void froze_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->froze();
}
void unfroze_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->unfroze();
}
void start_charging_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->start_charging();
}
void snowball_move_r(void* data){

}

void enemy_die_r(void* data) {
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->obs_info.dying_graph = true;
	fsm->notify_obs();
	fsm->obs_info.dying_graph = false;
	fsm->kill_character();
}

