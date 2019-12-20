#pragma once
#include "AllegroClass.h"
#include "FSM_Class.h"
#include "MapThing.h"

class MapThingFSM : public FSM
{
public:
	MapThingFSM(MapThing * thing);
	~MapThingFSM();

	unsigned int get_id();
	Direction_type get_current_action_direction();

protected:

	typedef std::vector<std::pair<Direction_type, double>> process_t;

	void set_curr_process(process_t* process);

	process_t::iterator current_moving_iteration;
	process_t* current_moving_vector = NULL;

	virtual void set_processes() = 0;
	virtual void create_all_timers() = 0;
	virtual void set_states() = 0;


private: 
	MapThing * thing = NULL;
};

