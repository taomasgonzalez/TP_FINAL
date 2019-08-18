#pragma once
#include "EventPackage.h"
#include "PackageFactory.h"
class EventPackageFactory
{
public:
	EventPackageFactory();
	~EventPackageFactory();

	EventPackage* create_event_package(Action_info * create_from);

};

