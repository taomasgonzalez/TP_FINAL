#pragma once
#include "Observer.h"
#include "Communication.h"
#include "LogicEventGenerator.h"
#include "PackageFactory.h"
#include "EventPackage.h"
#include "Scene.h"


class EventsCommunicationObserver : public Observer
{
public:
	EventsCommunicationObserver(LogicEventGenerator * event_gen, Communication * com, Userdata* data, Scene * scenario);
	~EventsCommunicationObserver();

	virtual void update();

private:
	LogicEventGenerator * event_gen;
	Communication * com;
	Userdata * my_user_data;
	Scene * my_scenario;

};

