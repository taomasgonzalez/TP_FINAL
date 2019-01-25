#pragma once
#include "Observer.h"
#include "Communication.h"
#include "EventGenerator.h"
#include "PackageFactory.h"
#include "EventPackage.h"
#include "Scene.h"


class EventsCommunicationObserver : public Observer
{
public:
	EventsCommunicationObserver(EventGenerator * event_gen, Communication * com, Userdata* data, Scene * scenario);
	~EventsCommunicationObserver();

	virtual void update();

private:
	EventGenerator * event_gen;
	Communication * com;
	Userdata * my_user_data;
	Scene * my_scenario;

};

