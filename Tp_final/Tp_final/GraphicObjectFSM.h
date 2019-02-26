#pragma once
#include "FSM_Class.h"
#include "DRAW.h"
#include "GraficObject.h"

class GraphicObjectFSM: public FSM
{
public:
	
	GraphicObjectFSM(Userdata* data, unsigned int id, Item_type identifyer, Obj_Graf* graphical_obj, DRAW* drawer);
	~GraphicObjectFSM();

	Obj_Graf* get_fsm_obj_graf();
protected:
	std::vector<edge_t>* drawing_state = NULL;
	std::vector<edge_t>* waiting_to_draw_state = NULL;
	std::vector<edge_t>* inactive_state = NULL;

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
	DRAW* drawer = NULL;
	Obj_Graf * graphical_obj = NULL;
	Item_type identifyer;
};

