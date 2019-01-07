#pragma once
#include "Observer.h"
#include "Communication.h"
#include "EventGenerator.h"

class EventsCommunicationObserver: public Observer
{
public:
	EventsCommunicationObserver(EventGenerator * event_gen, Communication * com);
	~EventsCommunicationObserver();

	virtual void update();

private:
	EventGenerator * event_gen;
	Communication * com;
};

