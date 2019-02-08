#include "GraphicCharacterFSM.h"

void attack(void* data);
void move(void* data);

GraphicCharacterFSM::GraphicCharacterFSM(Userdata* data, DRAW* drawer, unsigned int id) : GraphicObjectFSM(data, drawer, id)
{
	
	expand_state(waiting_to_draw_state, {Event_type::ATTACK, this->drawing_state, attack});
	//tiene que detectar la clase de movimiento que es y luego ejecutarlo!
	expand_state(waiting_to_draw_state, {Event_type::MOVE, this->drawing_state, move});
}




GraphicCharacterFSM::~GraphicCharacterFSM()
{

}


