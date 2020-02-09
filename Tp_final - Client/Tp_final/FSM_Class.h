#pragma once
/*******************************************************************************
					INCLUDED HEADERS
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Observable.h"
#include "EventPackage.h"
#include <vector>
#include <iostream>
#include <string>
#include "general.h"

using namespace std;
//changing fsm class!
/*****************************************************
*          DEFINITION OF EDGE
* **************************************************/
typedef struct edge edge_t;
struct edge
{
	Event_type event;
	std::vector<edge_t>* nextstate;
	void(*fun_trans)(void*);
};

std::string event_string[] =  //Events that are usde by the internal function of the program 
{ "END_OF_TABLE",

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
"ATTACKED",
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
//RESET(DEBUGGING)
"RESET",
"FINISHED_GRAPH_STEP"

};

/*******************************************************************************
							CLASE FSM
******************************************************************************/
class FSM : public  Observable{
public:
	 FSM();
	 virtual void run_fsm(EventPackage * ev_pack);
		
	 EventPackage* get_fsm_ev_pack();
	 void set_fsm_ev_pack(EventPackage* new_ev_pack);
	 std::vector<edge_t>* give_me_the_actual_state();

protected:
	std::vector<edge_t>* actual_state;
	void check_for_incorrect_event(Event_type event);
	void expand_state(std::vector<edge_t>* to_be_expanded, edge_t expansion);		//for inheritance
	void change_action_routine(std::vector<edge_t>* state_to_be_changed, Event_type event1, void(*new_routine)(void*));
	void(*get_routine(std::vector<edge_t>* state, Event_type event1))(void*);
	bool should_change_state = true;
private:
	EventPackage * my_ev_pack;
};


/*******************************************************************************
						ENUMS, STRUCTS Y TYPEDEFS
******************************************************************************/

typedef enum { OFF, ON } switch_t;

typedef unsigned int uint;

