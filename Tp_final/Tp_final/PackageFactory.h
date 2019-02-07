#pragma once
#include "EventGenerator.h"
#include "Package.h"
#include "EventPackage.h"
#include <iostream>

class PackageFactory
{
public:
	PackageFactory();
	static Package * event_package_2_package(EventPackage * info_received);
	static EventPackage * package_2_event_package(Package * package_recieved);
	static EventPackage * refresh_event_package(Action_info * info_checked);
	
};

