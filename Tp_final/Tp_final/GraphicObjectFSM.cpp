#include "GraphicObjectFSM.h"

void do_nothing_graph(void* data);
void appear(void* data);
void check_if_finished_moving_and_change(void* data);
void dissappear(void *data);
void die(void* data);
void attack(void* data);
void move(void* data);

GraphicObjectFSM::GraphicObjectFSM(Userdata* data, unsigned int id, Item_type identifyer, Obj_Graf* graphical_obj, DRAW* drawer): FSM(data)
{

	inactive_state = new std::vector<edge_t>();
	waiting_to_draw_state = new std::vector<edge_t>();
	drawing_state = new std::vector<edge_t>();

	inactive_state->push_back({Event_type::APPEARED, this->waiting_to_draw_state, appear });
	inactive_state->push_back({Event_type::END_OF_TABLE, this->inactive_state, do_nothing_graph });

	waiting_to_draw_state->push_back({ Event_type::DISAPPEARED, this->inactive_state, dissappear });	
	waiting_to_draw_state->push_back({Event_type::END_OF_TABLE, this->waiting_to_draw_state, do_nothing_graph });

	
	drawing_state->push_back({Event_type::DISAPPEARED, this->inactive_state, dissappear});
	drawing_state->push_back({Event_type::FPS_TICKED, this->drawing_state, check_if_finished_moving_and_change});
	drawing_state->push_back({ Event_type::FINISHED_DRAWING, this->waiting_to_draw_state, do_nothing_graph });
	drawing_state->push_back({Event_type::END_OF_TABLE, this->drawing_state, do_nothing_graph });

	this->actual_state = inactive_state;

	this->drawer = drawer;
	this->graphical_obj = graphical_obj;
	this->identifyer = identifyer;
}


GraphicObjectFSM::~GraphicObjectFSM()
{
	delete drawing_state;
	delete waiting_to_draw_state;
	delete inactive_state;
	delete graphical_obj;
}

void GraphicObjectFSM::is_able_to_die()
{
	waiting_to_draw_state->push_back({ Event_type::DIED, this->drawing_state, die });

	drawing_state->push_back({ Event_type::DIED, this->drawing_state, die });
}

Obj_Graf * GraphicObjectFSM::get_fsm_obj_graf()
{
	return graphical_obj;
}

void GraphicObjectFSM::is_able_to_attack()
{
	waiting_to_draw_state->push_back({ Event_type::ATTACK, this->drawing_state, attack });
}
void GraphicObjectFSM::is_able_to_move() {
	waiting_to_draw_state->push_back({ Event_type::MOVE, this->drawing_state, move });
}
void do_nothing_graph(void* data) {

}

void check_if_finished_moving_and_change(void * data) {
	//check if there's still another image to go to or if we should proceed to the waiting_to_draw_state state
}
void dissappear(void * data) {
	//change the graphic object's status to inactive.
}

void appear(void* data) {
	//change the graphic object's status to active.
}

void die(void * data) {
	//start destroying routine
}

void attack(void* data) {

}
void move(void* data) {

}