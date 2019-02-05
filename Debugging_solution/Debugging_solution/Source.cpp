#include "LogicServerFSM.h"
#include "EventPackage.h"
#include <vector>

using namespace std;

int main(void) {
	Userdata data;
	LogicServerFSM fsm_logica(&data);
	LOCAL_QUIT_EventPackage my_pack = LOCAL_QUIT_EventPackage();
	fsm_logica.run_fsm(&my_pack);

	getchar();
	return 0;
}