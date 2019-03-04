#include "EventPackageFactory.h"

int main() {
	return 0;
	Userdata data = Userdata();
	PackageFactory factory = PackageFactory();
	NAME_IS_EventPackage* name_is = new NAME_IS_EventPackage(true, 6, "Eberto");
	EventPackage * ev_pack = name_is;
	Package* pack = factory.event_package_2_package(name_is);

}