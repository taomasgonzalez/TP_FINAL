#pragma once
#include "Userdata.h" //Data usage
#include "FSM_Class.h"
#include "Communication.h"
#include "Allegroclass.h"
#include "EventPackage.h"
#include <queue> 


class EventGenerator
{
public:

	EventGenerator(Allegro * al, Userdata* data);
	~EventGenerator();
	
	virtual EventPackage * fetch_event();
	virtual void append_new_event(EventPackage* ev_pack, int queue_id);
	//In case an error ocurred and there are pending events to be run by the fsm
	virtual void empty_all_queues();
protected:
	std::vector<std::queue<EventPackage*>> event_queues;

	//para ser llamado dentro del constructor hijo!!!
	virtual void append_all_queues(int total_number_of_queues);

private:
};

