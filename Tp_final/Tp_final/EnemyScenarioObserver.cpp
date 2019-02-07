#include "EnemyScenarioObserver.h"



EnemyScenarioObserver::EnemyScenarioObserver(Enemy* enemy, Scene * scene)
{
	this->enemy = enemy;
	this->scene = scene;
}

EnemyScenarioObserver::~EnemyScenarioObserver()
{
}
void EnemyScenarioObserver::update() {

	Action_info act_info;
	if (enemy->questions_4_observer.can_jump) {
		enemy->answers_4_observable.can_jump = scene->is_the_action_possible(act_info);
	}
	else if (enemy->questions_4_observer.can_move_in_opposite_direction) {
		enemy->answers_4_observable.can_move_in_opposite_direction = scene->is_the_action_possible(act_info);;
	}
	else if (enemy->questions_4_observer.can_move_in_same_direction) {
		enemy->answers_4_observable.can_move_in_same_direction = scene->is_the_action_possible(act_info);;
	}
}