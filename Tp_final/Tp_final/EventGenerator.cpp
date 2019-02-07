#include "EventGenerator.h"
#include "EventPackage.h"
#include "Package.h"
#include "FSM_Class.h"
#include "Scene.h"


EventGenerator::EventGenerator(Allegro * al, Userdata* data)
{
	std::vector<std::vector<EventPackage*>> event_queues = std::vector<std::vector<EventPackage*>>();
	my_user_data = data;
}


EventGenerator::~EventGenerator()
{
}
/******************************************
***************empty_all_queues************
*******************************************
*empty_all_queues empties all the event_queues the EventGenerator has so that no new events will come unless
*they are placed on any queue after the call to this function.
*	INPUT:
*		1) void.
*	OUTPUT:
*		void.
*/
void EventGenerator::empty_all_queues() {
	for (std::vector<std::queue<EventPackage*>>::iterator it = event_queues.begin(); it != event_queues.end(); ++it) 
		while ((*it).size() >= 1)
			(*it).pop();
}
/******************************************
***************append_all_queues*****************
*******************************************
*append_all_queues is an internal method for the EventGenerator initialization. 
*It creates the correct number of queues for the EventGenerator's application.
*	INPUT:
*		1) total_number_of_queues : total number of queues the EventGenerator has.
*	OUTPUT:
*		void.
*/
void EventGenerator::append_all_queues(int total_number_of_queues)
{
	for(int i =0; i < total_number_of_queues; i++)
		event_queues.push_back(std::vector<std::queue<EventPackage*>>());
}


/******************************************
***************fetch_event*****************
*******************************************
*fetch_event returns the new Event to be exectuted by an FSM.
*fetch_event returns one and only one EventPackage coming from one of the multiple event queues the EventGenerator may have.
*fetch_event is designed in such a way that the queues take turns as to which of them will return the EventPackage.
*	INPUT:
*		1) void.
*	OUTPUT:
*		the next EventPackage to be executed by an FSM.
*/
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
