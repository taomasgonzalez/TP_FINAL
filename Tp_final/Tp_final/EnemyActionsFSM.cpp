#include "EnemyActionsFSM.h"


void do_nothing_enemy_r(void* data);
void check_got_hit_and_get_hit_r(void* data);
void partially_unfroze_r(void* data);
void freeze_r(void* data);
void unfroze_r(void* data);
void start_moving_snowball_r(void* data);
void snowball_move_r(void* data);
void enemy_die_r(void* data);
void start_got_hit_r(void*data);

EnemyActionsFSM::EnemyActionsFSM(Enemy* enemy): CharacterActionsFSM(enemy)
{
	this->enemy = enemy;

	set_states();
	set_processes();
	create_all_timers();
	this->actual_state = iddle_state;
}


EnemyActionsFSM::~EnemyActionsFSM()
{
	destroy_all_timers();
	delete freezing_state;
	delete frozen_state;
}
void EnemyActionsFSM::set_states()
{

	expand_state(iddle_state, { Event_type::GOT_HIT, freezing_state, start_got_hit_r });

	freezing_state = new std::vector<edge_t>();
	frozen_state = new std::vector<edge_t>();

	freezing_state->push_back({ Event_type::GOT_HIT, freezing_state, check_got_hit_and_get_hit_r});
	freezing_state->push_back({ Event_type::FROZE, frozen_state, freeze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFROZE, iddle_state, unfroze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_enemy_r });

	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, start_moving_snowball_r });
	frozen_state->push_back({ Event_type::MOVE, frozen_state, snowball_move_r });
	frozen_state->push_back({ Event_type::DIED, dead_state, enemy_die_r });
	frozen_state->push_back({ Event_type::END_OF_TABLE, frozen_state, do_nothing_enemy_r });
}


void EnemyActionsFSM::set_processes() {


}
void EnemyActionsFSM::create_all_timers() {

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

}
void EnemyActionsFSM::start_got_hit() {

	start_freezing_timer();
}

void EnemyActionsFSM::start_freezing_timer()
{
}

void EnemyActionsFSM::start_frozen_timer()
{
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

void partially_unfroze_r(void* data){

}
void freeze_r(void* data){

}
void unfroze_r(void* data){

}
void start_moving_snowball_r(void* data){

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

