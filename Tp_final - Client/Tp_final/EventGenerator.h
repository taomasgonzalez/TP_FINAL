#pragma once
#include "FSM_Class.h"
#include "Allegroclass.h"
#include "EventPackage.h"
#include "Observable.h"
#include <queue> 
#include <stack>

class EventGenerator : public Observable
{
public:
	enum class LogicQueues { allegro, net, soft, TOTAL_QUEUES };
	enum class GraphicQueues {TOTAL_QUEUES };
	EventGenerator();
	~EventGenerator();
	
	virtual EventPackage * fetch_event();
	virtual void append_new_event(EventPackage* ev_pack, int queue_id);
	//In case an error ocurred and there are pending events to be run by the fsm
	virtual void empty_all_queues();
	void append_new_event_front(EventPackage* ev_pack);
protected:
	std::vector<std::queue<EventPackage*>> event_queues;

	///para ser llamado dentro del constructor hijo!!!
	virtual void append_all_queues(int total_number_of_queues);

private:
	std::stack<EventPackage*> aux_front_queue;
	Userdata * my_user_data = NULL;
	unsigned int actual_queue = 0;
};

