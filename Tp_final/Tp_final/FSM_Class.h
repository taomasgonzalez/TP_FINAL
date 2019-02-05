#pragma once
/*******************************************************************************
					INCLUDED HEADERS
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Observable.h"
#include "EventPackage.h"

/*****************************************************
*          DEFINITION OF EDGE
* **************************************************/
typedef struct edge edge_t;
struct edge
{
		Event_type event;
		edge_t* nextstate;
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
	 edge_t * give_me_the_actual_state();

protected:
	static void copy_event(edge_t* to_copy, edge_t* to_be_copied, int length);
	edge_t * actual_state = NULL;
	void check_for_incorrect_event(Event_type event);
	Userdata * user_data;
	EventPackage * my_ev_pack;

private:

};


/*******************************************************************************
						ENUMS, STRUCTS Y TYPEDEFS
******************************************************************************/

typedef enum { OFF, ON } switch_t;

typedef unsigned int uint;

