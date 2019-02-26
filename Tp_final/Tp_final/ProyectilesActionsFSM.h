#pragma once
#include "FSM_Class.h"

class ProyectilesActionsFSM : public FSM
{
public:
	ProyectilesActionsFSM(Userdata* data);
	~ProyectilesActionsFSM();
private:
	enum PROYECTILE_STATE { proy_MOVING, proy_DECAYING, proy_IMPACT, proy_FALLING };		// el proyectil decae cuando se detiene a los 3 casilleros y se cae

	std::vector<edge_t>* moving_state = NULL;
	std::vector<edge_t>* decaying_state = NULL;
	std::vector<edge_t>* impact_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
};

