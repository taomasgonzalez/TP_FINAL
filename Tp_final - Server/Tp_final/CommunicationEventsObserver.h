#pragma once
#include "Observer.h"
#include "Communication.h"
#include "LogicEventGenerator.h"
#include "PackageFactory.h"
#include "EventPackage.h"
#include "Scene.h"


class CommunicationEventsObserver : public Observer
{
public:
	CommunicationEventsObserver(LogicEventGenerator * event_gen, Communication * com, Userdata* data);
	~CommunicationEventsObserver();

	virtual void update();

private:
	LogicEventGenerator * event_gen;
	Communication * com;
	Userdata * my_user_data;

};

