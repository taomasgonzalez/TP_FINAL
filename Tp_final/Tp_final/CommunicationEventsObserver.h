#pragma once
#include "Observer.h"
#include "EventGenerator.h"

class CommunicationEventsObserver: public Observer
{
public:
	CommunicationEventsObserver(EventGenerator * event_gen, Communication * com);
	~CommunicationEventsObserver();

	EventGenerator * event_gen;
	Communication * network_com;

	virtual void update();
};

