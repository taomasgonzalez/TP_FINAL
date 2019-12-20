#include "MapThingFSM.h"



MapThingFSM::MapThingFSM(MapThing* thing)
{
	this->thing = thing;

}


MapThingFSM::~MapThingFSM()
{
}



unsigned int MapThingFSM::get_id() {
	return thing->id;
}


Direction_type MapThingFSM::get_current_action_direction()
{
	return (*current_moving_iteration).first;
}

void MapThingFSM::set_curr_process(process_t* process) {
	current_moving_vector = process;
	current_moving_iteration = process->begin();
}