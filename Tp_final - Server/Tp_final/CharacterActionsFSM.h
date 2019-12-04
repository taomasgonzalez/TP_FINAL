#pragma once
#include "Character.h"
#include "MapThingFSM.h"

class CharacterActionsFSM : public MapThingFSM
{
public:
	CharacterActionsFSM(Character* character);
	~CharacterActionsFSM();

	struct observer_info {
		bool start_pushing_graph = false;
		bool start_walking_graph = false;
		bool start_jumping_graph = false;
		bool start_jumping_forward_graph = false;
		bool start_falling_graph = false;
		bool start_attacking_graph = false;
		bool dying_graph = false;
		bool reset_graph = false;

		bool interrupt_movement = false;
		bool interrupt_attack = false;
		bool perform_logical_movement = false;
		bool perform_logical_attack = false;
	};

	observer_info obs_info;

	struct observer_QA {
		bool can_perform_movement = false;
		bool should_interrupt_movement = false;
		bool should_interrupt_attack = false;
	};
	observer_QA obs_questions;
	observer_QA obs_answers;

	void kill_character();

	void process_logical_movement();
	void process_logical_attack();

	void start_walking();
	void start_jumping();
	void start_jumping_forward();
	void start_attacking();
	void start_falling();

	void stop_action();

	ALLEGRO_TIMER* get_walking_timer();
	ALLEGRO_TIMER* get_jumping_timer();
	ALLEGRO_TIMER* get_jumping_forward_timer();
	ALLEGRO_TIMER* get_falling_timer();
	ALLEGRO_TIMER* get_attacking_timer();

protected:

	std::vector<edge_t>* walking_state = NULL;
	std::vector<edge_t>* jumping_state = NULL;
	std::vector<edge_t>* jumping_forward_state = NULL;
	std::vector<edge_t>* iddle_state = NULL;
	std::vector<edge_t>* attacking_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
	std::vector<edge_t>* dead_state = NULL;

	void set_processes();
	void create_all_timers();
	void set_states();

private:
	Character * character = NULL;

	process_t jumping_process;
	process_t falling_process;

	process_t jumping_left_process;
	process_t jumping_right_process;

	process_t walking_left_process;
	process_t walking_right_process;


	ALLEGRO_TIMER* walking_timer = NULL;
	ALLEGRO_TIMER* jumping_timer = NULL;
	ALLEGRO_TIMER* jumping_forward_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;
	ALLEGRO_TIMER* attacking_timer = NULL;

	bool finished_logical_movement();
	bool can_perform_logical_movement();
	void continue_logical_movement(); 
	void end_if_should_end_movement();
	void end_if_should_end_attack();


	void attack();
	bool has_attacked();

	bool attacked = false;

};


