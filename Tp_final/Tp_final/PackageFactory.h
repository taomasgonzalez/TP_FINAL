#pragma once
#include "EventGenerator.h"
#include "Package.h"
#include "PackageInfo.h"

class PackageFactory
{
public:
	PackageFactory();
	static Package * create_package(PackageInfo * info_to_be_send);
	static unsigned char give_me_name_length(char * my_name);

	
};

