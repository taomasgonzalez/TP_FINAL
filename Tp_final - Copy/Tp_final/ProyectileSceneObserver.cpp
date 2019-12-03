#include "ProyectileSceneObserver.h"


ProyectileSceneObserver::ProyectileSceneObserver(Proyectile* proy, Scene * scenario)
{
	this->proy = proy;
	this->scenario = scenario;
	this->fsm = static_cast<ProyectilesActionsFSM*>(proy->get_my_fsm());
	this->ev_gen = proy->get_my_ev_gen();
}


ProyectileSceneObserver::~ProyectileSceneObserver()
{
}

void ProyectileSceneObserver::update(){
	if (fsm->obs_info.perform_logical_movement) 
		perform_logical_movement();

}
void ProyectileSceneObserver::perform_logical_movement() {
		bool should_be_hit = false;
		Action_info info = fsm->get_fsm_ev_pack()->to_Action_info();
		info.id = fsm->get_id();
		scenario->execute_action(&info, should_be_hit);
		if (should_be_hit)
			ev_gen->append_new_event(new GOT_HIT_EventPackage(), 0);

}