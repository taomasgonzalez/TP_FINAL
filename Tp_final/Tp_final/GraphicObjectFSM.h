#pragma once
#include "FSM_Class.h"
#include "DRAW.h"

class GraphicObjectFSM: public FSM
{
public:
	
	GraphicObjectFSM(Userdata* data, DRAW* drawer, unsigned int id, Obj_Graf* graphical_obj);
	~GraphicObjectFSM();

protected:
	std::vector<edge_t>* drawing_state;
	std::vector<edge_t>* waiting_to_draw_state;
	std::vector<edge_t> * inactive_state;

	DRAW* drawer;
	unsigned int id;

private:
	void is_able_to_attack();
	void is_able_to_move();
	void is_able_to_die();
	/*
	expand_state(waiting_to_draw_state, {Event_type::ATTACK, this->drawing_state, attack});
	//tiene que detectar la clase de movimiento que es y luego ejecutarlo!
	expand_state(waiting_to_draw_state, {Event_type::MOVE, this->drawing_state, move});s
	*/

	Obj_Graf * graphical_obj = NULL;
};

