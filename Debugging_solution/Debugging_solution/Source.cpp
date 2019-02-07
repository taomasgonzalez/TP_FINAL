#include "LogicServerFSM.h"
#include "EventPackage.h"
#include <vector>

using namespace std;

int main(void) {
	Userdata data;
	LogicServerFSM fsm_logica(&data);
	//END_OF_TABLE_EventPackage my_pack = END_OF_TABLE_EventPackage();
	ERROR_EventPackage my_pack = ERROR_EventPackage(true);
	//LOCAL_QUIT_EventPackage my_pack = LOCAL_QUIT_EventPackage();
	fsm_logica.run_fsm(&my_pack);

	getchar();
	return 0;
}