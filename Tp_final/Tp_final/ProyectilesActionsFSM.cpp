#include "ProyectilesActionsFSM.h"

void do_nothing_proy(void* data);
void start_moving_r(void* data);
void check_move_and_move(void* data);
void impact_r(void* data);
void finished_impacting(void* data);
void start_falling_pr(void* data);

ProyectilesActionsFSM::ProyectilesActionsFSM(Proyectile* proyectile): FSM()
{
	std::vector<edge_t>* moving_state = new std::vector<edge_t>();
	std::vector<edge_t>* impact_state = new std::vector<edge_t>();
	std::vector<edge_t>*inactive_state = new std::vector<edge_t>();

	moving_state->push_back({ Event_type::MOVE, moving_state, check_move_and_move });
	moving_state->push_back({ Event_type::GOT_HIT, impact_state, impact_r });
	moving_state->push_back({ Event_type::END_OF_TABLE, moving_state, do_nothing_proy });

	impact_state->push_back({Event_type::DISAPPEARED, inactive_state, finished_impacting});
	impact_state->push_back({ Event_type::END_OF_TABLE, impact_state, do_nothing_proy});

	inactive_state->push_back({ Event_type::MOVE, moving_state, start_moving_r });
	inactive_state->push_back({ Event_type::END_OF_TABLE, inactive_state, do_nothing_proy});

	falling_state->push_back({ Event_type::FELL, falling_state, start_falling_pr });
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_proy });
	actual_state = inactive_state;
}


ProyectilesActionsFSM::~ProyectilesActionsFSM()
{
	delete moving_state;
	delete impact_state;
	delete inactive_state;
}

void ProyectilesActionsFSM::start_moving() {
	MOVE_EventPackage* ev_pack = (MOVE_EventPackage*) get_fsm_ev_pack();
	direction = ev_pack->give_me_your_direction();
	observer_info.move = true;
	notify_obs();
	observer_info.move = false;

}
void ProyectilesActionsFSM::impact() {
	observer_info.impact = true;
	notify_obs();
	observer_info.impact = false;

}

Direction_type ProyectilesActionsFSM::get_direction() {
	return direction;
}
void ProyectilesActionsFSM::start_falling() {
	observer_info.fall = true;
	notify_obs();
	observer_info.fall = false;
}

void do_nothing_proy(void* data) {

}


void check_move_and_move(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;

}

void impact_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->impact();
}

void finished_impacting(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;

}

void start_moving_r(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_moving();
}

void start_falling_pr(void* data) {
	ProyectilesActionsFSM* fsm = (ProyectilesActionsFSM*)data;
	fsm->start_falling();
}