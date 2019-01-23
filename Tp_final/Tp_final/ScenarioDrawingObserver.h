#pragma once
#include "Observer.h"
#include "EventHandler.h"
#include "Scene.h"
#include "EventPackage.h"
#include "Drawer.h"

class ScenarioDrawingObserver : public Observer
{
public:
		ScenarioDrawingObserver(Scene* scenario, Drawer* my_drawer);
		~ScenarioDrawingObserver();

		virtual void update();
private:
		EventHandler * my_event_handler;
		Scene * scenario;
		Drawer * drawer;
};



