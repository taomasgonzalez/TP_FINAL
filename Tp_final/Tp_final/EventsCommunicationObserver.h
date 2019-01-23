#pragma once
#include "Observer.h"
#include "Communication.h"
#include "EventGenerator.h"
#include "PackageFactory.h"
#include "EventGenerator.h"


class EventsCommunicationObserver: public Observer
{
public:
	EventsCommunicationObserver(EventGenerator * event_gen, Communication * com, Userdata* data);
	~EventsCommunicationObserver();

	virtual void update();

private:
	EventGenerator * event_gen;
	Communication * com;
	Userdata * my_user_data;

};

