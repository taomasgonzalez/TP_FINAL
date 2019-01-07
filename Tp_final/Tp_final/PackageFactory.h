#pragma once
#include "EventGenerator.h"
#include "Package.h"
#include "PackageInfo.h"

class PackageFactory
{
public:
	PackageFactory();
	Package * create_package(Package_type my_package_type,EventPackage * EP_to_be_send =NULL);
	
};

