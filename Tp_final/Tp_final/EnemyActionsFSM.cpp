#include "EnemyActionsFSM.h"


void do_nothing_enemy_r(void* data);
void got_hit_r(void* data);
void partially_unfroze_r(void* data);
void freeze_r(void* data);
void unfroze_r(void* data);
void start_moving_snowball_r(void* data);
void snowball_move_r(void* data);
void enemy_die_r(void* data);

EnemyActionsFSM::EnemyActionsFSM(Enemy* enemy): CharacterActionsFSM(enemy)
{
	expand_state(iddle_state, {Event_type::GOT_HIT, freezing_state, got_hit_r});
	
	freezing_state->push_back({Event_type::GOT_HIT, freezing_state, got_hit_r});
	freezing_state->push_back({ Event_type::FROZE, frozen_state, freeze_r });
	freezing_state->push_back({ Event_type::PARTIALLY_UNFROZE, freezing_state, partially_unfroze_r });
	freezing_state->push_back({ Event_type::UNFROZE, iddle_state, unfroze_r });
	freezing_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_enemy_r });

	frozen_state->push_back({ Event_type::GOT_HIT, frozen_state, start_moving_snowball_r });
	frozen_state->push_back({Event_type::MOVE, frozen_state, snowball_move_r});
	frozen_state->push_back({ Event_type::DIED, dead_state, enemy_die_r});
	frozen_state->push_back({ Event_type::END_OF_TABLE, frozen_state, do_nothing_enemy_r });


}


EnemyActionsFSM::~EnemyActionsFSM()
{
}

void do_nothing_enemy_r(void* data) {

}
void got_hit_r(void* data) {
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
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.dying_graph = true;
	fsm->notify_obs();
	fsm->obs_info.dying_graph = false;
	fsm->kill_character();
}