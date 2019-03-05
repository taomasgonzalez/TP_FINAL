#pragma once
#include "Userdata.h"
#include "Package.h"
#include "EventPackage.h"
#include <iostream>

class PackageFactory
{
public:
	PackageFactory();
	 Package * event_package_2_package(EventPackage * info_received);
	 EventPackage * package_2_event_package(Package * package_recieved);
	
private: 

	EventPackage * my_event_package;
	Package * pac;
};

