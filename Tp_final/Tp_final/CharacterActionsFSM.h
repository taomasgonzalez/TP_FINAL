#pragma once
#include "FSM_Class.h"
#include "Character.h"


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
		bool dying_graph = false;
		bool reset_graph = false;
	};

	observer_info obs_info;

	void kill_character();
	void start_walking_timer();
	void start_jumping_timer();
	void start_jumping_forward_timer();
	void start_falling_timer();
	void start_attacking_timer();


	void start_jumping();
	bool finished_jumping();
	void start_jumping_forward();
	bool finished_jumping_forward();

	bool finished_walking();

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

	std::vector<Direction_type> jumping_process;
	std::vector<Direction_type> jumping_left_process;
	std::vector<Direction_type> jumping_right_process;
	std::vector<Direction_type>::iterator current_moving_iteration;

};


