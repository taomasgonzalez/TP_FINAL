#pragma once
#include "FSM_Class.h"
#include "Character.h"
#include "AllegroClass.h"

class CharacterActionsFSM : public FSM
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
		bool interrupt_movement = false;
		bool interrupt_attack = false;
		bool dying_graph = false;
		bool reset_graph = false;
		bool perform_logical_movement = false;
		bool perform_logical_attack = false;
	};

	observer_info obs_info;

	struct observer_QA {
		bool can_perform_movement = false;
		bool can_attack = false;
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

	Direction_type get_current_action_direction();
	unsigned int get_character_id();

	virtual std::vector<ALLEGRO_TIMER*> get_all_my_timers();

protected:

	std::vector<edge_t>* walking_state = NULL;
	std::vector<edge_t>* jumping_state = NULL;
	std::vector<edge_t>* jumping_forward_state = NULL;
	std::vector<edge_t>* iddle_state = NULL;
	std::vector<edge_t>* attacking_state = NULL;
	std::vector<edge_t>* falling_state = NULL;
	std::vector<edge_t>* dead_state = NULL;


private:
	Character * character = NULL;

	std::vector<std::pair<Direction_type, double>> jumping_process;
	std::vector<std::pair<Direction_type, double>> falling_process;

	std::vector<std::pair<Direction_type, double>> jumping_left_process;
	std::vector<std::pair<Direction_type, double>> jumping_right_process;

	std::vector<std::pair<Direction_type, double>> walking_left_process;
	std::vector<std::pair<Direction_type, double>> walking_right_process;

	std::vector<std::pair<Direction_type, double>>::iterator current_moving_iteration;
	std::vector<std::pair<Direction_type, double>>* current_moving_vector = NULL;

	ALLEGRO_TIMER* walking_timer = NULL;
	ALLEGRO_TIMER* jumping_timer = NULL;
	ALLEGRO_TIMER* jumping_forward_timer = NULL;
	ALLEGRO_TIMER* falling_timer = NULL;
	ALLEGRO_TIMER* attacking_timer = NULL;

	void start_walking_timer();
	void start_jumping_timer();
	void start_jumping_forward_timer();
	void start_falling_timer();
	void start_attacking_timer();

	ALLEGRO_TIMER* curr_timer = NULL;


	bool finished_logical_movement();
	bool can_perform_logical_movement();
	void continue_logical_movement(); 
	void continue_logical_attack();
	void end_if_should_end_movement();
	void end_if_should_end_attack();

	void set_processes();
	void create_all_timers();
	void set_states();

	void set_curr_timer_and_start();
	void set_curr_timer_speed(double speed);
};


