#include "EventGenerator.h"
#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"


EventGenerator::EventGenerator(Allegro * al, Userdata* data)
{
	std::vector<std::vector<EventPackage*>> event_queues = std::vector<std::vector<EventPackage*>>();

}


EventGenerator::~EventGenerator()
{
}

void EventGenerator::empty_all_queues() {
	for (std::vector<std::queue<EventPackage*>>::iterator it = event_queues.begin(); it != event_queues.end(); ++it) 
		while ((*it).size() >= 1)
			(*it).pop();
}

void EventGenerator::append_all_queues(int total_number_of_queues)
{
	for(int i =0; i < total_number_of_queues; i++)
		event_queues.push_back(std::vector<std::queue<EventPackage*>>());
}



EventPackage * EventGenerator::fetch_event()
{
	static int actual_queue = 0;
	EventPackage * returned_package = NULL;

	if (event_queues.size() > 0) {
		returned_package = (event_queues.at(actual_queue)).front();
		(event_queues.at(actual_queue)).pop();

		actual_queue++;
		if (actual_queue >= event_queues.size())
			actual_queue = 0;
	}
	if(returned_package == NULL)
		returned_package = new NO_EVENT_EventPackage();

	return returned_package;
}

void EventGenerator::append_new_event(EventPackage * ev_pack, int queue_id)
{
	(event_queues.at(queue_id)).push(ev_pack);
}
