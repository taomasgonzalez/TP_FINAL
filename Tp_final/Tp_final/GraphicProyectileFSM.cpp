#include "GraphicProyectileFSM.h"

void do_nothing(void* data);
void impact(void* data);
void move(void* data);
void disappear(void* data);

GraphicProyectileFSM::GraphicProyectileFSM(Userdata* data): FSM(data)
{

	edge_t *moving_state_aux = new edge_t[4];
	this->moving_state = moving_state_aux;

	edge_t moving_state[5] =
	{
		{Event_type::MOVE_TICKED, this->impacting_state, move},
		{ Event_type::GOT_HIT, this->moving_state, impact },
	{ Event_type::DISAPPEARED, this->impacting_state, disappear },
	{ Event_type::END_OF_TABLE, this->moving_state, do_nothing }
	};
	copy_event(moving_state_aux, moving_state, 4);

	edge_t* impacting_state_aux = new edge_t[3];
	this->impacting_state = impacting_state_aux;

	edge_t impacting_state[3] =
	{
		{ Event_type::IMPACT_TICKED, this->impacting_state, impact },
	{Event_type::DISAPPEARED, this->impacting_state, disappear},
	{ Event_type::END_OF_TABLE, this->moving_state, do_nothing }
	};
	copy_event(impacting_state_aux, impacting_state, 3);

}



GraphicProyectileFSM::~GraphicProyectileFSM()
{
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