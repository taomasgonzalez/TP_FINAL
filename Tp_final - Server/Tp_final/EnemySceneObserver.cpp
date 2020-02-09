#include "EnemySceneObserver.h"



EnemySceneObserver::EnemySceneObserver(Enemy* enemy, Scene * scene) : CharacterSceneObserver(scene, enemy)
{
	this->enemy = enemy;
	this->scene = scene;
	this->fsm = static_cast<EnemyActionsFSM*>(enemy->ev_handler->get_fsm());
	this->ev_gen = enemy->ev_handler->get_ev_gen();
	this->freezing_queue = al_create_event_queue();
	this->froze_queue = al_create_event_queue();

	al_register_event_source(this->freezing_queue, al_get_timer_event_source(this->fsm->get_freezing_timer()));
	al_register_event_source(this->froze_queue, al_get_timer_event_source(this->fsm->get_frozen_timer()));
}

EnemySceneObserver::~EnemySceneObserver()
{
}

void EnemySceneObserver::update() {
	CharacterSceneObserver::update();
	Action_info act_info = enemy->get_action_4_obs();
	if(enemy->enemy_questions_4_observer.can_make_movement)
		enemy->enemy_answers_4_observable.can_make_movement = scene->is_the_action_possible(&act_info, true);
	if(fsm->enemyObs_info.start_freezing_state1_graph)
		ev_gen->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), 0);
	if (fsm->enemyObs_info.start_freezing_state2_graph)
		ev_gen->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), 0);
	if (fsm->enemyObs_info.start_freezing_state3_graph)
		ev_gen->append_new_event(new PARTIALLY_UNFROZE_EventPackage(), 0);
	if (fsm->enemyObs_info.start_fozen_graph)
		ev_gen->append_new_event(new FROZE_EventPackage(), 0);
	if (fsm->enemyObs_questions.should_start_defrost)
	{
		fsm->enemyObs_answers.should_start_defrost = false;
		ALLEGRO_EVENT  allegroEvent;
		if (al_get_next_event(freezing_queue, &allegroEvent)) {
			if(allegroEvent.type == ALLEGRO_EVENT_TIMER)
			fsm->enemyObs_answers.should_start_defrost = true;
		}

	}
	if (fsm->enemyObs_questions.should_unfreeze)
	{
		fsm->enemyObs_answers.should_unfreeze = false;
		ALLEGRO_EVENT  allegroEvent;
		if (al_get_next_event(freezing_queue, &allegroEvent)) {
			if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
				fsm->enemyObs_answers.should_unfreeze = true;
		}
	}	
	if (fsm->enemyObs_questions.should_start_defrost)
	{
		fsm->enemyObs_answers.should_start_defrost = false;
		ALLEGRO_EVENT  allegroEvent;
		if (al_get_next_event(froze_queue, &allegroEvent)) {
			if (allegroEvent.type == ALLEGRO_EVENT_TIMER)
				fsm->enemyObs_answers.should_start_defrost = true;
		}
	}
}

void EnemySceneObserver::perform_movement(Action_info action) {
	bool should_be_hit = false;
	action.my_info_header = Action_info_id::ENEMY_ACTION;
	//action.my_character = character->get_printable();
	scene->execute_action(&action, should_be_hit);
	if (should_be_hit)
		ev_gen->append_new_event(new GOT_HIT_EventPackage(), 0);
}