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

	if (enemy->questions_4_observer.can_jump) {
		//enemy->answers_4_observable.can_jump = ;
	}
	else if (enemy->questions_4_observer.can_move_in_opposite_direction) {
		//enemy->answers_4_observable.can_move_in_opposite_direction = ;
	}
	else if (enemy->questions_4_observer.can_move_in_same_direction) {
		//enemy->answers_4_observable.can_move_in_same_direction = ;
	}
}