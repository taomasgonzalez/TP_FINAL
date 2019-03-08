#include "ProyectilesActionsFSMDRAWObserver.h"

Direction direction_translation(Direction_type dir);

ProyectilesActionsFSMDRAWObserver::ProyectilesActionsFSMDRAWObserver(Proyectile * proyectile)
{
	this->proyectile = proyectile;
	this->fsm = static_cast<ProyectilesActionsFSM*>(proyectile->get_my_fsm());
	this->drawer = Userdata::drawer;
	this->ev_gen = proyectile->get_my_ev_gen();
}


ProyectilesActionsFSMDRAWObserver::~ProyectilesActionsFSMDRAWObserver()
{
}


void ProyectilesActionsFSMDRAWObserver::update() {
	if (fsm->obs_info.start_moving_graph) {
		drawer->startDraw(proy_MOVING, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_MOVING;
	}
	else if (fsm->obs_info.start_impacting_graph) {
		drawer->startDraw(proy_IMPACT, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_IMPACT;
	}
	else if (fsm->obs_info.start_falling_graph) {
		drawer->startDraw(proy_FALLING, proyectile->id, direction_translation(fsm->get_current_action_direction()), proyectile->pos_x, proyectile->pos_y);
		curr_state = proy_FALLING;
	}
}

Direction direction_translation(Direction_type dir) {
	return (dir == Direction_type::Left) ? Direction::Left : Direction::Right ;
}