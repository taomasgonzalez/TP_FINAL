#include "ProyectilesActionsFSMDRAWObserver.h"

Direction direction_translation(Direction_type dir);

ProyectilesActionsFSMDRAWObserver::ProyectilesActionsFSMDRAWObserver(Proyectile * proyectile)
{
	this->proyectile = proyectile;
	this->fsm = static_cast<ProyectilesActionsFSM*>(proyectile->ev_handler->get_fsm());
	this->drawer = Userdata::drawer;
	this->ev_gen = proyectile->ev_handler->get_ev_gen();
}


ProyectilesActionsFSMDRAWObserver::~ProyectilesActionsFSMDRAWObserver()
{
}


void ProyectilesActionsFSMDRAWObserver::update() {

	if (first_update) {
		drawer->add_observer(proyectile->id, this);
		first_update = false;
	}
	if (fsm->obs_info.start_moving_graph) {
		drawer->startDraw(proy_MOVING, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_MOVING;
	}
	if (fsm->obs_info.start_impacting_graph) {
		drawer->startDraw(proy_IMPACT, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_IMPACT;
	}
	if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(proy_FALLING, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_FALLING;
	}

	if (fsm->obs_questions.should_interrupt_movement) {
		fsm->obs_answers.should_interrupt_movement = drawer->secuenceOver(proyectile->id);
	}
	if (fsm->obs_info.interrupt_movement) {
		ev_gen->append_new_event(new FINISHED_MOVEMENT_EventPackage(),0);
	}
	if (fsm->obs_info.interrupt_impact) {
		//set inactive state
	}
}

Direction direction_translation(Direction_type dir) {
	return (dir == Direction_type::Left) ? Direction::Left : Direction::Right ;
}