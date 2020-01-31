#include "CharacterActionsFSM.h"
#include "Player.h"
#include "Enemy.h"

void do_nothing_char(void* data);

void start_walking_r(void* data);
void check_walking_and_walk(void* data);
void reset_walking(void* data);
void append_action_r(void* data);
void append_action_moving_state_r(void* data);




void start_jumping_r(void* data);
void check_jumping_and_jump(void* data);
void reset_jumping(void* data);

void start_jumping_forward_r(void* data);
void check_jumping_forward_and_jump(void* data);
void reset_jumping_forward(void* data);

void start_falling_r(void* data);
void check_fall_and_fall(void* data);
void reset_fall(void* data);

void start_attacking_r(void* data);
void check_attack_and_attack(void* data);
void reset_attack(void* data);

void iddle_graph(void* data);
void disappear_graph_r(void* data);

CharacterActionsFSM::CharacterActionsFSM(Character * character) : MapThingFSM(character)
{
	this->character = character;
	set_states();
	set_processes();
	create_all_timers();
	char_ev_queue = al_create_event_queue();

	this->saved_character_events = new queue<EventPackage *>();

	al_register_event_source(char_ev_queue, al_get_timer_event_source(falling_timer));
	actual_state = iddle_state;
	al_start_timer(falling_timer);
}


CharacterActionsFSM::~CharacterActionsFSM()
{
	delete walking_state;
	delete jumping_state;
	delete jumping_forward_state;
	delete iddle_state;
	delete attacking_state;
	delete falling_state;
	delete dead_state;
}


void CharacterActionsFSM::set_processes() {

	jumping_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));
	jumping_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));

	jumping_left_process.push_back(std::make_pair(Direction_type::Jump_Straight,0));
	jumping_left_process.push_back(std::make_pair(Direction_type::Jump_Left,0));

	jumping_right_process.push_back(std::make_pair(Direction_type::Jump_Straight, 0));
	jumping_right_process.push_back(std::make_pair(Direction_type::Jump_Right, 0));

	falling_process.push_back(std::make_pair(Direction_type::Down, 0));

	walking_left_process.push_back(std::make_pair(Direction_type::Left, 1/120.0));
	walking_right_process.push_back(std::make_pair(Direction_type::Right, 1 / 120.0));

}

void CharacterActionsFSM::create_all_timers() {
	falling_timer = al_create_timer(1/50.0);
}

void CharacterActionsFSM::set_states() {

	iddle_state = new std::vector<edge_t>();

	walking_state = new std::vector<edge_t>();
	jumping_state = new std::vector<edge_t>();
	jumping_forward_state = new std::vector<edge_t>();
	falling_state = new std::vector<edge_t>();

	attacking_state = new std::vector<edge_t>();

	dead_state = new std::vector<edge_t>();

	//Tengo que validar lo chequeos logicos de cada uno de estos casos para cada estado
	//recién ahí el juego va a andar bien y fluido
	iddle_state->push_back({ Event_type::ATTACK, attacking_state, start_attacking_r });
	iddle_state->push_back({ Event_type::WALKED, walking_state, start_walking_r });
	iddle_state->push_back({ Event_type::JUMPED, jumping_state, start_jumping_r });
	iddle_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, start_jumping_forward_r });
	iddle_state->push_back({ Event_type::FELL, falling_state, start_falling_r });
	iddle_state->push_back({ Event_type::END_OF_TABLE, iddle_state, do_nothing_char });

	//CAMBIAR::Cada movimiento distinto al de su propio estado debe ir al estado asociado a dicho movimiento
	//y appendearse al saved_events(append_action_r) asi se levanta cuando termine dicho movimiento
	walking_state->push_back({ Event_type::JUMPED, jumping_state, append_action_moving_state_r });
	walking_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, append_action_moving_state_r });
	walking_state->push_back({ Event_type::WALKED, walking_state, append_action_r });
	walking_state->push_back({ Event_type::FELL, falling_state, do_nothing_char });
	walking_state->push_back({ Event_type::FINISHED_GRAPH_STEP, walking_state, check_walking_and_walk });
	walking_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_walking });
	walking_state->push_back({ Event_type::END_OF_TABLE, walking_state, do_nothing_char });

	jumping_state->push_back({ Event_type::JUMPED, jumping_state, append_action_r });
	jumping_state->push_back({ Event_type::WALKED, walking_state, append_action_r });
	jumping_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, append_action_r });
	jumping_state->push_back({ Event_type::FELL, falling_state, do_nothing_char });
	jumping_state->push_back({ Event_type::FINISHED_GRAPH_STEP, jumping_state, check_jumping_and_jump });
	jumping_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping });
	jumping_state->push_back({ Event_type::END_OF_TABLE, jumping_state, do_nothing_char });

	jumping_forward_state->push_back({ Event_type::FELL, falling_state, do_nothing_char });
	jumping_forward_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, append_action_r });
	jumping_forward_state->push_back({ Event_type::WALKED, walking_state, append_action_r });
	jumping_forward_state->push_back({ Event_type::JUMPED, jumping_state, append_action_r });
	jumping_forward_state->push_back({ Event_type::FINISHED_GRAPH_STEP, jumping_forward_state, check_jumping_forward_and_jump });
	jumping_forward_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_jumping_forward });
	jumping_forward_state->push_back({ Event_type::END_OF_TABLE, jumping_forward_state, do_nothing_char });

	falling_state->push_back({ Event_type::JUMPED, jumping_state, append_action_r });
	falling_state->push_back({ Event_type::WALKED, walking_state, append_action_r });
	falling_state->push_back({ Event_type::JUMPED_FORWARD, jumping_forward_state, append_action_r });
	falling_state->push_back({ Event_type::FINISHED_GRAPH_STEP, falling_state, check_fall_and_fall });
	falling_state->push_back({ Event_type::FELL, falling_state, do_nothing_char });
	falling_state->push_back({ Event_type::FINISHED_MOVEMENT, iddle_state, reset_fall });
	falling_state->push_back({ Event_type::END_OF_TABLE, falling_state, do_nothing_char });

	attacking_state->push_back({ Event_type::ATTACK, attacking_state, check_attack_and_attack });
	attacking_state->push_back({ Event_type::FINISHED_ATTACK, iddle_state, reset_attack });
	attacking_state->push_back({ Event_type::END_OF_TABLE, attacking_state, do_nothing_char });

	dead_state->push_back({ Event_type::FINISHED_GRAPH_STEP, dead_state, disappear_graph_r });
	dead_state->push_back({ Event_type::END_OF_TABLE, dead_state, do_nothing_char });
	
}

void CharacterActionsFSM::kill_character() {
	character->die();
}
void CharacterActionsFSM::disappear_char() {
	obs_info.disappear_graph = true;
	notify_obs();
	obs_info.disappear_graph = false;
}

bool CharacterActionsFSM::is_moving() {
	return actual_state == walking_state || actual_state == jumping_forward_state || actual_state == jumping_state;
}

bool CharacterActionsFSM::is_walking() {
	return actual_state == walking_state;
}

bool CharacterActionsFSM::is_falling() {
	return actual_state == falling_state;
}
bool CharacterActionsFSM::is_iddle() {
	return actual_state == iddle_state;
}

bool CharacterActionsFSM::is_finishing_the_movement() {

	return actual_state == iddle_state;

}

bool CharacterActionsFSM::is_attacking() {
	return actual_state == attacking_state;
}

/*
Reminder:
Por como está codeado el primer movimiento no lo chequea como válido, porque asume que ya se chequeo
previamente en check_action(). Se chequea recién el segundo process, que si llega a estar mal es un problema
porque dicho chequeo sucede después de haber ejecutado el process gráfico.
Caso Salto:
En salto no chequea el primer process porque ya lo chequeo check_move() pero recien hace el primer chequeo
al terminar el segundo process por lo que en el caso de un salto "corto" lo hace en medio de un bloque ya.
Cosa que está mal. Se debería chequear antes de realizar el procedimiento lógico. Se va a implementar sólo 
para el caso del salto por miedo a cagarla en otros casos, pero tener en cuenta.
*/
void CharacterActionsFSM::process_logical_movement()
{
	bool can_perform = true;
	if(!finished_logical_movement()){			//do i have any more sub-movements to perform?
		
		//can i perform this sub-movement? Do the game conditions enable me to do so?
		if(!first_logical_movement())
			can_perform = can_perform_logical_movement();
		

		if (!moving_between_states)
		{
			//Chequeo para salto "corto" o "largo", se harcodeo para chequear el primer salto por si es "corto"
			if (actual_state == jumping_state || actual_state == jumping_forward_state)
			{
				continue_logical_movement();		//if so, perform the movement.
				can_perform = can_perform_logical_movement();
			}
			moving_between_states = false;
		}

		if (can_perform)
			continue_logical_movement();		//if so, perform the movement.
		else {			
			obs_info.interrupt_movement = true;		//append a movement finished event to the queue.
			notify_obs();
			obs_info.interrupt_movement = false;
		}
	}
	//appends a movement finished event to the queue if the graphic part has finished its sequence. 
	end_if_should_end_movement();
}

void CharacterActionsFSM::process_logical_attack(){
	if (!has_attacked()) 
		attack();

	end_if_should_end_attack();
}

void CharacterActionsFSM::start_attacking(){
	al_stop_timer(falling_timer);
	attacked = false;
}
void CharacterActionsFSM::start_falling() {
	al_stop_timer(falling_timer);
	set_curr_process(&falling_process);
	obs_info.start_falling_graph = true;
	notify_obs();
	obs_info.start_falling_graph = false;
}

void CharacterActionsFSM::stop_action(){
}

bool CharacterActionsFSM::has_to_fall()
{
	ALLEGRO_EVENT  allegroEvent;
	bool returnable = false;
	if (al_get_next_event(char_ev_queue, &allegroEvent))
		if (allegroEvent.type == ALLEGRO_EVENT_TIMER) {
			returnable = allegroEvent.timer.source == falling_timer;
			while (al_get_next_event(char_ev_queue, &allegroEvent));		//empties all timer events
		}
				 
	return returnable;
}

void CharacterActionsFSM::dont_fall()
{
	al_stop_timer(falling_timer);
}

void CharacterActionsFSM::continue_logical_movement(){

	obs_info.perform_logical_movement = true;
	notify_obs();						//CharacterSceneObserver
	obs_info.perform_logical_movement = false;

	++current_moving_iteration;
}

void CharacterActionsFSM::end_if_should_end_movement(){


	obs_questions.should_interrupt_movement = true;
	notify_obs();						//PlayerActionsFSMDRAWObserver
	obs_questions.should_interrupt_movement = false;


	if (actual_state == falling_state || (actual_state == jumping_forward_state && obs_answers.should_interrupt_movement) || (actual_state == jumping_state && obs_answers.should_interrupt_movement))
	{
		obs_questions.should_keep_falling = true;
		notify_obs();						//PlayerActionsFSMDRAWObserver
		obs_questions.should_keep_falling = false;
	}

	if (obs_answers.should_interrupt_movement) {

		
		//Estoy en medio de una caida y tengo que seguir cayendo
		if (obs_answers.should_keep_falling)
		{
			std::cout << "Se sigue cayendo, se appendea un FELL" << std::endl;
			character->ev_handler->get_ev_gen()->append_new_event_front(new FELL_EventPackage());
			start_falling();

			//The pending actions are erased because the player has to fall
			if(!saved_character_events->empty())
				saved_character_events->pop();

		}
		//Chequeo si hay algun evento guardado que tenga que ser appendeado
		else if (!this->saved_character_events->empty())
		{
			EventPackage * saved_event = saved_character_events->front();

			if (saved_event->give_me_your_event_type() == Event_type::WALKED)
			{
				//CAPAZ QUE SE PUEDE HACER UN SOLO CHEQUEO SIEMPRE HABER SI TENGO QUE CAER, CHEQUEAR QUE NO SE ROMPA
				//caso excepción mitad del salto en un salto largo
				//Check if should fall instead of walk again
				obs_questions.should_keep_falling = true;
				notify_obs();						//PlayerActionsFSMDRAWObserver
				obs_questions.should_keep_falling = false;

				if (obs_answers.should_keep_falling)
				{
					std::cout << "Hay que caer no caminar, se appendea un FELL,vacio la cola de eventos" << std::endl;
					character->ev_handler->get_ev_gen()->append_new_event_front(new FELL_EventPackage());
					start_falling();
				}
				else
				{
					std::cout << "Se ejecuta un WALKED guardado" << std::endl;
					set_fsm_ev_pack(saved_event);
					start_walking();
				}
			}
			else if (saved_event->give_me_your_event_type() == Event_type::JUMPED)
			{
				//CAPAZ QUE SE PUEDE HACER UN SOLO CHEQUEO SIEMPRE HABER SI TENGO QUE CAER, CHEQUEAR QUE NO SE ROMPA
				//caso excepción mitad del salto en un salto largo
				//Check if should fall instead of walk again
				obs_questions.should_keep_falling = true;
				notify_obs();						//PlayerActionsFSMDRAWObserver
				obs_questions.should_keep_falling = false;

				if (obs_answers.should_keep_falling)
				{
					std::cout << "Hay que caer no caminar, se appendea un FELL,vacio la cola de eventos" << std::endl;
					character->ev_handler->get_ev_gen()->append_new_event_front(new FELL_EventPackage());
					start_falling();
				}
				else
				{
					std::cout << "Se ejecuta un JUMPED guardado" << std::endl;
					set_fsm_ev_pack(saved_event);
					start_jumping();
				}

				//std::cout << "Se ejecuta un JUMPED guardado" << std::endl;
				//set_fsm_ev_pack(saved_event);
				//start_jumping();
			}
			else if (saved_event->give_me_your_event_type() == Event_type::JUMPED_FORWARD)
			{
				std::cout << "Se ejecuta un JUMPED_FORWARD guardado" << std::endl;
				set_fsm_ev_pack(saved_event);
				start_jumping_forward();
			}

			if (!saved_character_events->empty())
				saved_character_events->pop();
		}
		//If there´s not any event pending, we append a FINISHED_MOVEMENT and the FSM goes to iddle state
		else
		{
			obs_info.interrupt_movement = true;
			notify_obs();
			obs_info.interrupt_movement = false;
		}

		////The FSM asks to the observer if there are pending packages to be executed
		//obs_questions.should_continue_moving = true;
		//notify_obs();						//PlayerActionsFSMDRAWObserver
		//obs_questions.should_continue_moving = false;

		////To avoid going iddle when there´s another MOVE coming in, we append a new WALKED
		//if (obs_answers.should_continue_moving)
		//{
		//	obs_info.keep_moving = true;
		//	notify_obs();
		//	obs_info.keep_moving = false;

		//	obs_answers.should_continue_moving=false;
		//}
	}
}

void CharacterActionsFSM::end_if_should_end_attack(){
	obs_questions.should_interrupt_attack = true;
	notify_obs();
	obs_questions.should_interrupt_attack = false;

	if (obs_answers.should_interrupt_attack) {
		obs_info.interrupt_attack = true;
		notify_obs();
		obs_info.interrupt_attack = false;
	}
}
//Checks if the iterator is pointing to the "past-the-end" element, known as the next element from the last element
//in the queue. 
//Will return true after the last call to continue_logical_movement()
bool CharacterActionsFSM::finished_logical_movement() {
	return (current_moving_vector->end() == current_moving_iteration);
}

bool CharacterActionsFSM::first_logical_movement() {
	return (current_moving_vector->begin() == current_moving_iteration);
}
bool CharacterActionsFSM::can_perform_logical_movement(){

	obs_questions.can_perform_movement = true;
	notify_obs();				//CharacterSceneObserver
	obs_questions.can_perform_movement = false;
	return obs_answers.can_perform_movement;
}

bool CharacterActionsFSM::has_attacked() {
	return attacked;
}
void CharacterActionsFSM::attack() {

	obs_info.perform_logical_attack = true;
	notify_obs();
	obs_info.perform_logical_attack = false;

	//to prevent other attack timers from being executed.
	attacked = true;
}

void CharacterActionsFSM::append_action() {

	//Only one event can be appended at the same time
	if (this->saved_character_events->empty())
	{
		Event_type event_to_be_appended = get_fsm_ev_pack()->give_me_your_event_type();

		switch (event_to_be_appended)
		{
		case Event_type::WALKED:
			//Se llama a constructor copiador para evitar que se pierda el WALKED a guardar
			this->saved_character_events->push(new WALKED_EventPackage((WALKED_EventPackage *)get_fsm_ev_pack()));
			std::cout << "Se appendeo un WALKED" << std::endl;
			break;

		case Event_type::JUMPED:
			//Se llama a constructor copiador para evitar que se pierda el JUMPED a guardar
			this->saved_character_events->push(new JUMPED_EventPackage((JUMPED_EventPackage *)get_fsm_ev_pack()));
			std::cout << "Se appendeo un JUMPED" << std::endl;
			break;

		case Event_type::JUMPED_FORWARD:
			//Se llama a constructor copiador para evitar que se pierda el JUMPED_FORWARD a guardar
			this->saved_character_events->push(new JUMPED_FORWARD_EventPackage((JUMPED_FORWARD_EventPackage *)get_fsm_ev_pack()));
			std::cout << "Se appendeo un JUMPED_FORWARD" << std::endl;
			break;

		default:
			break;

		}
	}
	else
		std::cout << "Ya habia un evento guardado en la cola de CharacterActionsFSM, no se guarda evento" << std::endl;

}

void do_nothing_char(void * data) {

}


void start_walking_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*) data;
	fsm->start_walking();
}

void append_action_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->append_action();
}

void append_action_moving_state_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->moving_between_states = true;
	fsm->append_action();
}


void CharacterActionsFSM::start_walking() {
	al_stop_timer(falling_timer);

	WALKED_EventPackage * curr_walk = (WALKED_EventPackage*)get_fsm_ev_pack();
	
	if (curr_walk->walking_direction == Direction_type::Right)
		set_curr_process(&walking_right_process);
	else if (curr_walk->walking_direction == Direction_type::Left)
		set_curr_process(&walking_left_process);

	obs_info.start_walking_graph = true;
	notify_obs();
	obs_info.start_walking_graph = false;
}
void check_walking_and_walk(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;

	/*the character doesn t need to check if the movement is possible
	* as this is a walking movement and takes only one step, which has been previously checked before
	* changing the state of the character. If checking the movement is necessary due to changes in the code,
	* can_perform_logical_movement() should be called before executing the next lines (start_walking_graph) */

	fsm->process_logical_movement();
}
void reset_walking(void* data) {
	iddle_graph(data);
}

void start_jumping_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_jumping();

}
void CharacterActionsFSM::start_jumping() {
	al_stop_timer(falling_timer);
	set_curr_process(&jumping_process);

	obs_info.start_jumping_graph = true;
	notify_obs();
	obs_info.start_jumping_graph = false;
}


void CharacterActionsFSM::start_iddle() {
	obs_info.reset_graph = true;
	notify_obs();
	obs_info.reset_graph = false;
	al_start_timer(falling_timer);
}
void check_jumping_and_jump(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
	
}
void reset_jumping(void* data) {
	iddle_graph(data);
}

void start_jumping_forward_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_jumping_forward();
}
void CharacterActionsFSM::start_jumping_forward(){
	al_stop_timer(falling_timer);
	JUMPED_FORWARD_EventPackage * curr_jump = (JUMPED_FORWARD_EventPackage*) get_fsm_ev_pack();

	if (curr_jump->jumping_direction == Direction_type::Jump_Right)
		set_curr_process(&jumping_right_process);
	else if (curr_jump->jumping_direction == Direction_type::Jump_Left)
		set_curr_process(&jumping_left_process);

	obs_info.start_jumping_forward_graph = true;
	notify_obs();
	obs_info.start_jumping_forward_graph = false;
}
void check_jumping_forward_and_jump(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
}
void reset_jumping_forward(void* data) {
	iddle_graph(data);
}

void start_falling_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_falling();
}
void check_fall_and_fall(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->process_logical_movement();
}
void reset_fall(void* data) {
	iddle_graph(data);
}

void start_attacking_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->obs_info.start_attacking_graph = true;
	fsm->notify_obs();
	fsm->obs_info.start_attacking_graph = false;
	fsm->start_attacking();

}

void check_attack_and_attack(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_attacking();
}

void reset_attack(void* data) {
	iddle_graph(data);
}

void iddle_graph(void * data)
{
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->start_iddle();
}


void disappear_graph_r(void* data) {
	CharacterActionsFSM* fsm = (CharacterActionsFSM*)data;
	fsm->disappear_char();
}