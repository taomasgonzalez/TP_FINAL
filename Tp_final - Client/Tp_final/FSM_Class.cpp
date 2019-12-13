#include "FSM_Class.h"
#include <string>

using namespace std;

FSM::FSM() : Observable(){

}
string event_string[] =  //Events that are usde by the internal function of the program 
{
	"END_OF_TABLE",

	//ACK:
	"ACK",

	//LOCAL_QUIT:Evento de allegro de quit, tiene que ser enviado por networking al otro usuario
	"LOCAL_QUIT",

	//EXTERN_QUIT:Evento de networking de quit
	"EXTERN_QUIT",

	//LOCAL_ACTION: Evento generado por allegro pero no ejecutado por la maquina,falta analizar
	"MOVE",

	//EXTERN_ACTION   Es un MOVE/ATTACK del servidor que llega por networking siendo cliente
	"ATTACK",

	//ACTION_REQUEST   //action request generado por el cliente que no fue chequeado
	"ACTION_REQUEST",

	//ERROR: Evento de software cuando se produce un error interno, diversos origenes
	"ERROR1",

	//NAME_IS: 
	"NAME_IS",

	//NAME:
	"NAME",

	//MAP_IS:
	"MAP_IS",

	//ENEMY_ACTION: El servidor crea una enemy action
	"ENEMY_ACTION",

	//ENEMYS_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	"ENEMYS_LOADED",

	//GAME_START:
	"GAME_START",

	//WE_WON
	"WE_WON",

	//PLAY_AGAIN
	"PLAY_AGAIN",

	//FINISHED_LEVEL
	"FINISHED_LEVEL",

	//GAME_OVER
	"GAME_OVER",

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	"START_COMMUNICATION",

	"NO_EVENT",

	//graphic events
	"FPS_TICKED",
	"APPEARED",
	"DISAPPEARED",
	"FINISHED_DRAWING",
	"CHANGE_LEVEL",

	//character events
	"JUMPED",
	"JUMPED_FORWARD",
	"WALKED",
	"FELL",
	"PUSHED",
	"FINISHED_MOVEMENT",
	"FINISHED_ATTACK",
	"DIED",

	//player events
	"REVIVED",

	//enemy and proyectiles events
	"GOT_HIT",
	"GOT_SMASHED",

	//enemy events
	"FROZE",
	"UNFROZE",
	"PARTIALLY_UNFROZE",
	"BOUNCE",
	"ROLLING",
	"CHARGING",
	"FINISHED_GRAPH_STEP"
};

/******************************************************************************
*******************************************************************************
					PRIVATE METHODS DEFINITIONS
*******************************************************************************

/**************************************************************
					run_fsm
**************************************************************/
/*
*This function runs the FSM with a given input.
*
*INPUT:
*The event that is hold in the edge that contains the action routine.
*
*OUTPUT:
*Void
*/
void FSM:: run_fsm(EventPackage * ev_pack)
{
	if (ev_pack != NULL){

		Event_type event1 = ev_pack->give_me_your_event_type();
		cout << "LLego un evento " << event_string[(int) event1] << endl;
		set_fsm_ev_pack(ev_pack);

		int event_pos = 0;
		while ( ((actual_state->at(event_pos)).event != event1) && (event1!= Event_type::END_OF_TABLE) )
			event_pos++;

		//genera evento de software en caso de haber encontrado un evento que no debería ocurrir en ese estado.s MANDAR ERROR, NO PUEDE LLEGAR UN MOVE AL PRINICIPIO XEJ
		if (event1 == Event_type::END_OF_TABLE)
			std::cout << "ERROR, EVENTO RECIBIDO NO PERTENECE AL ESTADO" << std::endl;
		//	this->check_for_incorrect_event(event1);	AGREGAR DPS CARGAR ERROR SI ME LLEGA UN END_OF_TABLE QUE IMPLICA QUE EL EVENTO RECIBIDO NO PERTENECE AL ESTADO		

		//Runs the functions related to that event
		((actual_state->at(event_pos)).fun_trans)(this);
		this->actual_state = ((actual_state->at(event_pos)).nextstate);
	}
}

void FSM::check_for_incorrect_event(Event_type event) {
	//if(this->actual_state == this->Waiting..) {

	//}
}

void FSM::expand_state(std::vector<edge_t>* to_be_expanded, edge_t expansion)
{
	std::vector<edge_t>::iterator it = (to_be_expanded->end()-1);
	to_be_expanded->insert(it, expansion);
}

void FSM::change_action_routine(std::vector<edge_t>* state_to_be_changed,Event_type event1, void(*new_routine)(void*))
{
	
	for (std::vector<edge_t>::iterator it = state_to_be_changed->begin(); it == state_to_be_changed->end(); ++it) 
		if ((it->event) == event1)
			it->fun_trans = new_routine;
	
}


EventPackage* FSM::get_fsm_ev_pack() {
	return this->my_ev_pack;
}

void FSM::set_fsm_ev_pack(EventPackage * new_ev_pack)
{
	if (new_ev_pack != my_ev_pack) {
		delete my_ev_pack;
		my_ev_pack = new_ev_pack;
	}
}

std::vector<edge_t>* FSM::give_me_the_actual_state() {

	return actual_state;
}
void(*FSM::get_routine(std::vector<edge_t>* state, Event_type event1))(void*){
	for (std::vector<edge_t>::iterator it = state->begin(); it == state->end(); ++it)
		if ((it->event) == event1)
			return (it->fun_trans);
	return NULL;
}
