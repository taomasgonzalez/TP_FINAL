#include "EnemySceneObserver.h"



EnemySceneObserver::EnemySceneObserver(Enemy* enemy, Scene * scene) : CharacterSceneObserver(scene, enemy)
{
	this->enemy = enemy;
	this->scene = scene;
	this->fsm = static_cast<EnemyActionsFSM*>(enemy->ev_handler->get_fsm());
	this->ev_gen = enemy->ev_handler->get_ev_gen();
}

EnemySceneObserver::~EnemySceneObserver()
{
}

void EnemySceneObserver::update() {

	if (!scenario->avoid_character_scene_obs)
		CharacterSceneObserver::update();

	Action_info act_info = enemy->get_action_4_obs();
	if(enemy->enemy_questions_4_observer.can_make_movement)
		enemy->enemy_answers_4_observable.can_make_movement = scene->is_the_action_possible(&act_info, true);

}

void EnemySceneObserver::perform_movement(Action_info action) {
	bool should_be_hit = false;
	action.my_info_header = Action_info_id::ENEMY_ACTION;
	//action.my_character = character->get_printable();
	scene->execute_action(&action, should_be_hit);
	if (should_be_hit)
		ev_gen->append_new_event(new GOT_HIT_EventPackage(), 0);
}