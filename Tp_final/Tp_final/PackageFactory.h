#pragma once
#include "EventGenerator.h"
#include "Package.h"
#include "EventPackage.h"

class PackageFactory
{
public:
	PackageFactory();
	static Package * event_package_2_package(EventPackage * info_to_be_send);
	static EventPackage * package_2_event_package(Package * package_recieved);

	
};

