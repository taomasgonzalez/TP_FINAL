#pragma once
#include "Userdata.h" //Data usage
#include "Communication.h"
#include "Allegroclass.h"
#include <queue> 

enum class Event
{
	END_OF_TABLE,

	//ACK:
	ACK,

	//LOCAL_QUIT:Evento de allegro de quit
	LOCAL_QUIT,

	//EXTERN_QUIT: Evento que llega por networking del otro computador
	EXTERN_QUIT,

	//LOCAL_ACTION_REQUESTED: Evento generado por allegro pero no ejecutado por la maquina.
	LOCAL_ACTION_REQUESTED,

	//LOCAL_ACTION: Evento generado por allegro y ya ejecutado por la maquina.
	LOCAL_ACTION,

	//LOCAL_ACTION_DENIED: Accion local rechazada.
	LOCAL_ACTION_DENIED,

	//EXTERN_ACTION_RECEIVED
	EXTERN_ACTION_RECEIVED,

	//EXTERN_ACTION_REQUESTED: Evento que llega por networking
	EXTERN_ACTION_REQUESTED,

	//EXTERN_ACTION_DENIED
	EXTERN_ACTION_DENIED,

	//EXTERN_ACTION_ACCEPTED
	EXTERN_ACTION_ACCEPTED,

	//EXTERN_ERROR: Evento de net cuando recibo un paquete de error, diversos origenes
	EXTERN_ERROR,

	//LOCAL_ERROR: Evento de software cuando se produce un error interno, diversos origenes
	LOCAL_ERROR,

	//NAME_IS: 
	NAME_IS,

	//NAME:
	NAME,

	//MAP_IS:
	MAP_IS,

	//MAP_IS_OK:
	MAP_IS_OK,
	
	//LOCAL_ENEMY_ACTION: El servidor crea una enemy action
	LOCAL_ENEMY_ACTION,

	//EXTERN_ENEMY_ACTION: Recibi un enemy action del servidor
	EXTERN_ENEMY_ACTION,

	//ENEMY_ACTION_LOADED: Recibi todos los enemy  action como para poder empezar el juego
	ENEMY_ACTION_IS_OK,

	//GAME_START:
	GAME_START,

	//START_COMMUNICATION: Evento de software generado cuando se inicilizo todo correctamente, el servidor esta listo para inicilizar
	START_COMMUNICATION,

	NO_EVENT

};

class EventPackage
{
public:

	Event ev = Event::NO_EVENT;
	Action_type act;		
	Character_type my_character;
	unsigned int action_made_by_id;
	Direction dir;
	map_position destiny_position;


};


class EventGenerator
{
public:
	EventGenerator(Allegro * al);
	~EventGenerator();

	friend class CommunicationEventsObserver;
	friend class ScenarioEventsObserver;
	friend class FSMEventsObserver;

	bool get_should_check_for_new_messages();

	void set_should_check_for_new_messages(bool should_check);

	void append_new_net_event(EventPackage* new_ev_pack);
	void append_new_soft_event(EventPackage* new_ev_pack);

protected:
	
	ALLEGRO_EVENT_QUEUE * al_queue;			//cola para eventos de allegro
	std::queue<EventPackage*>* soft_queue;		//cola para eventos de software.
	std::queue<EventPackage*>* net_queue;		//cola para eventos de networking.
	ALLEGRO_TIMER * time_out_timer;

	EventPackage fetch_event_al();
	EventPackage fetch_event_net();
	EventPackage fetch_event_soft();

	static unsigned int time_out_count;

private:
	bool check_for_new_messages;

};

struct map_position
{
	char fil_de;
	char col_de;
}
};