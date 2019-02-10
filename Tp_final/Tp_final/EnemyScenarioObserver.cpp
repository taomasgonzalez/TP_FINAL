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

	Action_info act_info = enemy->get_action_4_obs();
	if(enemy->enemy_questions_4_observer.can_make_movement)
		enemy->enemy_answers_4_observable.can_make_movement = scene->is_the_action_possible(&act_info);

}