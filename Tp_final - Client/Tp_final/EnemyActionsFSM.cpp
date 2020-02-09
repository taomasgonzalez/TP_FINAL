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
void fall_and_start_got_hit_r(void* data);

EnemyActionsFSM::EnemyActionsFSM(Enemy* enemy): CharacterActionsFSM(enemy)
{
	this->enemy = enemy;

	set_states();
	set_processes();
	create_all_timers();
	actual_state = iddle_state;
}


EnemyActionsFSM::~EnemyActionsFSM()
{
	delete freezing_state;
	delete frozen_state;
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

	expand_state(iddle_state, { Event_type::GOT_SMASHED, dead_state, start_got_hit_r });
	expand_state(walking_state, { Event_type::GOT_SMASHED, dead_state, start_got_hit_r });
	expand_state(jumping_state, { Event_type::GOT_SMASHED, dead_state, fall_and_start_got_hit_r });
	expand_state(jumping_forward_state, { Event_type::GOT_SMASHED, dead_state, fall_and_start_got_hit_r });
	expand_state(attacking_state, { Event_type::GOT_SMASHED, dead_state, start_got_hit_r });
	expand_state(falling_state, { Event_type::GOT_SMASHED, dead_state, fall_and_start_got_hit_r }); //PRODUCE UNA ANIMACIÓN DISTINTA A LA de morir, hay dos formas de morir
	//una siendo aplastado por una bola que salís volando y otra desaparecer con la bola, que no es una animación de muerte, sólo desapareces vos con la bola




	freezing_state->push_back({ Event_type::GOT_HIT, freezing_state, check_got_hit_and_get_hit_r});
	freezing_state->push_back({ Event_type::FROZE, frozen_state, freeze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFROZE, iddle_state, unfroze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_enemy_r });

	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, start_moving_snowball_r });
	frozen_state->push_back({ Event_type::BOUNCE, frozen_state, start_moving_snowball_r });
	frozen_state->push_back({ Event_type::CHARGING, frozen_state, snowball_move_r }); 
	frozen_state->push_back({ Event_type::ROLLING, frozen_state, snowball_move_r }); //lo cambie porque se mueve a velocidad más lenta que un MOVE, me pareció más claro
	frozen_state->push_back({ Event_type::DIED, dead_state, enemy_die_r });
	frozen_state->push_back({ Event_type::END_OF_TABLE, frozen_state, do_nothing_enemy_r });

	actual_state = iddle_state;
}


void EnemyActionsFSM::set_processes() {

	rolling_right_process.push_back(std::make_pair(Direction_type::Right, 0));

	rolling_left_process.push_back(std::make_pair(Direction_type::Left, 0));

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


void fall_and_start_got_hit_r(void*data) {
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

