#pragma once
/*******************************************************************************
					INCLUDED HEADERS
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Observable.h"
#include "EventPackage.h"
#include <vector>

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


/*******************************************************************************
							CLASE FSM
******************************************************************************/
class FSM : public  Observable{
public:
	 FSM(Userdata * data);
	 void run_fsm(EventPackage * ev_pack);
		
	 EventPackage* get_fsm_ev_pack();
	 void set_fsm_ev_pack(EventPackage* new_ev_pack);
	 std::vector<edge_t>* give_me_the_actual_state();

protected:
	std::vector<edge_t>* actual_state;
	void check_for_incorrect_event(Event_type event);
	Userdata * user_data;
	void expand_state(std::vector<edge_t>* to_be_expanded, edge_t expansion);		//for inheritance

private:
	EventPackage * my_ev_pack;
};


/*******************************************************************************
						ENUMS, STRUCTS Y TYPEDEFS
******************************************************************************/

typedef enum { OFF, ON } switch_t;

typedef unsigned int uint;

