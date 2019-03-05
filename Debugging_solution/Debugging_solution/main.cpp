#include "EventPackageFactory.h"
using namespace std;

void hola(EventPackage *name_is);
int main() {
	Userdata data = Userdata();
	NAME_IS_EventPackage* name_is = new NAME_IS_EventPackage(true, 6, "Eberto");
	EventPackage * ev_pack = name_is;
	hola(name_is);

	getchar();
	return 0;
}

void hola(EventPackage *name_is) {
	PackageFactory factory = PackageFactory();
	Package* pack = factory.event_package_2_package(name_is);
	NAME_IS_package * name_pack = dynamic_cast<NAME_IS_package *>(pack);
	std::cout << name_pack->give_me_your_name() << std::endl;
}