#include "GraphicProyectileFSM.h"

void do_nothing(void* data);
void impact(void* data);
void move(void* data);
void disappear(void* data);

GraphicProyectileFSM::GraphicProyectileFSM(Userdata* data): FSM(data)
{

	moving_state = new std::vector<edge_t>();
	impacting_state = new std::vector<edge_t>();

	moving_state->push_back({ Event_type::MOVE_TICKED, this->impacting_state, move });
	moving_state->push_back({ Event_type::GOT_HIT, this->moving_state, impact });
	moving_state->push_back({ Event_type::DISAPPEARED, this->impacting_state, disappear });
	moving_state->push_back({ Event_type::END_OF_TABLE, this->moving_state, do_nothing });


	impacting_state->push_back({ Event_type::MOVE_TICKED, this->impacting_state, move });
	impacting_state->push_back({ Event_type::DISAPPEARED, this->impacting_state, disappear });
	impacting_state->push_back({ Event_type::END_OF_TABLE, this->moving_state, do_nothing });

}



GraphicProyectileFSM::~GraphicProyectileFSM()
{
	delete moving_state;
	delete impacting_state;
}

/***********************************
*	action_routines
************************************/

void do_nothing(void* data) {

}
void move(void* data) {
	GraphicProyectileFSM* fsm = (GraphicProyectileFSM*)data;
	fsm->should_move = true;
	fsm->notify_obs();
	fsm->should_move = false;
}

void impact(void*data) {
	GraphicProyectileFSM* fsm = (GraphicProyectileFSM*)data;
	fsm->should_impact = true;
	fsm->notify_obs();
	fsm->should_impact = false;
}

void disappear(void* data) {
	GraphicProyectileFSM* fsm = (GraphicProyectileFSM*)data;
	fsm->should_disappear = true;
	fsm->notify_obs();
	fsm->should_disappear = false;
}