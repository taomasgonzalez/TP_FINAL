#include "EnemyActionsFSM.h"

#define FREEZING_TIME (10.0)
#define FROZEN_TIME (30.0)

void do_nothing_enemy_r(void* data);
void check_got_hit_and_get_hit_r(void* data);
void partially_unfroze_r(void* data);
void froze_r(void* data);
void unfreeze_r(void* data);
void unfroze_r(void* data);
void start_moving_snowball_r(void* data);
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

	//move toda la info de los timers aca, sacalas del observer


	//guido ac� levantas los eventos, hace una sola cola si total no te
	ALLEGRO_EVENT  allegroEvent;

	while (al_get_next_event(defrost_queue, &allegroEvent))
	{
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
			handle_hits();
	}

	//una vez que terminas lo appendeas
	//ev_gen->append_new_event(event, (int)EventGenerator::LogicQueues::soft);

	//entonces entr�s al run_fsm original con el envento cargado ya que lo vas agarrar recien en el siguiente ciclo porque ya paso el fetch_event
}

void EnemyActionsFSM::set_states()
{
	freezing_state = new std::vector<edge_t>();
	frozen_state = new std::vector<edge_t>();

	expand_state(iddle_state, { Event_type::GOT_HIT, freezing_state, start_got_hit_r });
	expand_state(walking_state, { Event_type::GOT_HIT, freezing_state, start_got_hit_r });
	expand_state(jumping_state, { Event_type::GOT_HIT, freezing_state, fall_and_start_got_hit_r });
	expand_state(jumping_forward_state, { Event_type::GOT_HIT, freezing_state, fall_and_start_got_hit_r });
	expand_state(attacking_state, { Event_type::GOT_HIT, freezing_state, start_got_hit_r });
	expand_state(falling_state, { Event_type::GOT_HIT, freezing_state, fall_and_start_got_hit_r });


	//Eventually we can do two different enemy_die_r, one for GOT_SMAHED and other for SNOWBALL_BREAKDOWN
	expand_state(iddle_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(walking_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(jumping_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(jumping_forward_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(attacking_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r });
	expand_state(falling_state, { Event_type::GOT_SMASHED, dead_state, enemy_die_r }); //PRODUCE UNA ANIMACI�N DISTINTA A LA de morir, hay dos formas de morir
	//una siendo aplastado por una bola que sal�s volando y otra desaparecer con la bola, que no es una animaci�n de muerte, s�lo desapareces vos con la bola

	expand_state(snowballed_state, { Event_type::SNOWBALL_BREAKDOWN, dead_state, enemy_die_r });


	freezing_state->push_back({ Event_type::GOT_HIT, freezing_state, check_got_hit_and_get_hit_r});
	freezing_state->push_back({ Event_type::FROZE, frozen_state, froze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFROZE, iddle_state, unfreeze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, freezing_state, do_nothing_enemy_r });

	//diferencia entre los dos primeros????
	frozen_state->push_back({ Event_type::UNFROZE, freezing_state, unfroze_r });
	frozen_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, renew_hits_r });
	frozen_state->push_back({ Event_type::CHARGING, snowballed_state, start_moving_snowball_r });
	frozen_state->push_back({ Event_type::ROLLING, frozen_state, snowball_move_r }); //lo cambie porque se mueve a velocidad m�s lenta que un MOVE, me pareci� m�s claro
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
	case 0:
		enemy->ev_handler->get_ev_gen()->append_new_event(new UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);
		notify_obs();
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
	case 3:
		enemyObs_info.start_freezing_state3_graph = true;
		notify_obs();
		enemyObs_info.start_freezing_state3_graph = false;
		break;
	case 4:
		enemyObs_info.start_fozen_graph = true;
		notify_obs();
		enemyObs_info.start_fozen_graph = false;
		break;
	default:
		enemyObs_info.start_freezing_state3_graph = true;
		notify_obs();
		enemyObs_info.start_freezing_state3_graph = false;
		break;
	}
}

void EnemyActionsFSM::unfreeze()
{
	al_stop_timer(freezing_timer);

}

void EnemyActionsFSM::froze()
{
	start_frozen_timer();
//	enemyObs_questions.should_unfreeze = false;
//	enemyObs_questions.should_start_defrost = true;
}

void EnemyActionsFSM::start_moving_snowball()
{
	enemyObs_info.start_ballCharging_graph = true;
	notify_obs();
	enemyObs_info.start_ballCharging_graph = false;
}


void EnemyActionsFSM::unfroze()
{
	al_stop_timer(frozen_timer);
	enemy->amount_of_hits_taken = 3;
	enemyObs_info.start_freezing_state3_graph = true;
	notify_obs();
	enemyObs_info.start_freezing_state3_graph = false;
//	enemyObs_questions.should_start_defrost = false;
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
    partially_unfroze();
	start_freezing_timer();
}
void EnemyActionsFSM::start_got_hit() {

	got_hit();
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
void check_got_hit_and_get_hit_r(void* data) {
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
	fsm->got_hit();
}


void EnemyActionsFSM::handle_hits(void)
{
	if (enemy->amount_of_hits_taken == 4)
		unfroze();
	else if (enemy->amount_of_hits_taken > 0 && enemy->amount_of_hits_taken <= 3)
		enemy->amount_of_hits_taken--;
	enemy->ev_handler->get_ev_gen()->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), /*(int)EventGenerator::LogicQueues::soft*/ 0);

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
void start_moving_snowball_r(void* data){
	EnemyActionsFSM* fsm = (EnemyActionsFSM*)data;
	fsm->start_moving_snowball();
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

