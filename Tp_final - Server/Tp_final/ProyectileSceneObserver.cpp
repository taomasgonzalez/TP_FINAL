#include "ProyectileSceneObserver.h"


ProyectileSceneObserver::ProyectileSceneObserver(Proyectile* proy, Scene * scenario)
{
	this->proy = proy;
	this->scenario = scenario;
	this->fsm = static_cast<ProyectilesActionsFSM*>(proy->ev_handler->get_fsm());
	this->ev_gen = proy->ev_handler->get_ev_gen();
}


ProyectileSceneObserver::~ProyectileSceneObserver()
{
}

void ProyectileSceneObserver::update(){
	if (fsm->obs_info.perform_logical_movement) 
		perform_logical_movement();
	if (fsm->obs_questions.can_perform_movement) {
		Action_info info;
		info.my_info_header = Action_info_id::MOVE;
		info.action = Action_type::Move;
		info.my_direction = fsm->get_current_action_direction();
		info.id = proy->id;
		direction_to_deltas(&info);
		fsm->obs_answers.can_perform_movement = scenario->is_the_action_possible(&info, true);
	}
	if (fsm->obs_info.perform_logical_movement) {

		MOVE_EventPackage ev_pack;
		Action_info info = ev_pack.to_Action_info();
		info.my_direction = fsm->get_current_action_direction();
		info.id = proy->id;
		direction_to_deltas(&info);
		perform_movement(info);
	}
}
void ProyectileSceneObserver::perform_logical_movement() {
		bool should_be_hit = false;
		Action_info info = fsm->get_fsm_ev_pack()->to_Action_info();
		info.id = fsm->get_id();
		scenario->execute_action(&info, should_be_hit);
		if (should_be_hit)
			ev_gen->append_new_event(new GOT_HIT_EventPackage(), 0);
}


void ProyectileSceneObserver::direction_to_deltas(Action_info* action) {
	action->final_pos_x = proy->pos_x;
	action->final_pos_y = proy->pos_y;

	if (action->my_direction == Direction_type::Right) {
		action->final_pos_x += 1;
		proy->set_sense(Sense_type::Right);
	}
	else if (action->my_direction == Direction_type::Left) {
		action->final_pos_x -= 1;
		proy->set_sense(Sense_type::Left);
	}
}

void ProyectileSceneObserver::perform_movement(Action_info action) {
	bool should_be_hit = false;
	scenario->execute_action(&action, should_be_hit);
	if (should_be_hit)
		ev_gen->append_new_event(new GOT_HIT_EventPackage(), 0);
}