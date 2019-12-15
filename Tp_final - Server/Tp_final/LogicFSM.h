#pragma once
#include "FSM_Class.h"
#include "Userdata.h"
#include "LogicEventGenerator.h"
#include "Scene.h"
#include "EventPackageFactory.h"
#include "Communication.h"
#include "PackageFactory.h"
/*******************************************************************************
CLASE TIME_OUT
******************************************************************************/
enum class time_out_type {
	Time_out_move,
	Time_out_quit,
	Time_out_i_am_ready

};

class LogicFSM : public FSM
{
public:
	LogicFSM(Userdata * data, LogicEventGenerator *event_gen, Scene* scene, Communication* com);
	~LogicFSM();

	virtual void run_fsm(EventPackage * ev_pack);

	
	//user decition flags
	bool want_to_play_again = false;


	//game conditions flags
	bool valid_action = false;
	bool we_won = false;
	bool we_lost = false;

	bool waiting_for_ack = false;
	bool reset_ack_timer = false;
	bool new_ack_time_out = false;
	bool end_game = false;
	bool receive_name = false;

	//execute falgs
	bool ex_action = false;
	bool ex_saved_enemy_actions = false;
	bool control_actions = false;
	bool control_enemies = false;

	bool start_game = false;

	//check flags
	bool check_map = false;
	bool valid_local_action = false;
	bool valid_extern_action = false;
	bool error_ocurred = false;

	//loading
	bool ld_enemy_action = false; //for client
	bool sv_enemy_action = false; //for server
	bool ld_new_map = false;
	bool ld_play_again = false;
	bool ld_game_over = false;

								 //analyze
	void analayze_error();
	void analyze_we_won(); //to do
	void analyze_we_lost(); //to do
	void check_action();
	void check_game_state();

	//send
	void send_map_is();
	void send_ack();
	void send_quit();
	void send_name_is();
	void send_ack_and_quit();
	void execute_and_send_enemy_action();
	void send_game_start();
	void send_error_and_finish_game();
	void send_action_and_set_ack_time_out();
	void send_next_map();  //to do
	void send_we_won();
	void send_we_lost();
	void send_game_over();
	void send_play_again();
	void send_enemy_action();
	void save_enemy_action_and_send_it();
	void send_action_request_and_set_ack_time_out(); //for client
	void send_action();

	//UI
	void tell_user_send_ack_and_finish_game(); //to do
	void ask_the_user_if_wants_to_play_again(); //to do
	void ask_user_being_client_and_send_decition(); //to do
	void ask_user_being_server_and_send_decition();

	//execute
	void execute_receive_action_and_send_ack(); //for client
	void execute_action_send_it_and_set_ack_time_out(); //for server
	void execute_receive_action_request_send_action_and_send_ack(); //for server
	void execute_saved_enemy_actions();
	void execute_local_action();
	void execute_extern_action();
	void execute_action_and_send_ack();
	//mapping
	void check_map_and_save_send_ack();
	void check_sum_and_send_ack();

	//timers
	void set_ack_time_out();
	void received_ack_routine();

	//others
	void ask_for_name();
	void finish_game();
	void start_game_and_send_ack();
	void receive_name_and_send_ack();
	void check_and_send_action_request();

	//loading
	void load_and_send_enemy_action(); //to do
	void load_enemy_action_and_send_ack();
	void load_action_and_send_it_back();
	void load_enemy_action();
	void save_enemy_action();


private:
	Userdata * user_data = NULL;
	LogicEventGenerator * ev_gen = NULL;
	Scene* scenario = NULL;
	Communication* com = NULL;

	EventPackageFactory ev_pack_factory;
	PackageFactory pack_factory;
	void execute_action();
};


void do_nothing_r(void* data);//Dummy for the debugging of the protocol structure

							  //analyze
void analayze_error_r(void* data);
void analyze_we_won_r(void* data); //to do
void analyze_we_lost_r(void* data); //to do
void check_action_r(void* data);
void check_game_state_r(void* data);

//send
void send_map_is_r(void* data);
void send_ack_r(void* data);
void send_quit_r(void* data);
void send_name_is_r(void* data);
void send_ack_and_quit_r(void* data);
void execute_and_send_enemy_action_r(void* data);
void send_game_start_r(void* data);
void send_error_and_finish_game_r(void* data);
void send_action_and_set_ack_time_out_r(void* data);
void send_next_map_r(void* data);  //to do
void send_we_won_r(void* data);
void send_we_lost_r(void* data);
void send_game_over_r(void* data);
void send_play_again_r(void* data);
void send_enemy_action_r(void* data);
void save_enemy_action_and_send_it_r(void* data);
void send_action_request_and_set_ack_time_out_r(void* data); //for client
void send_action_r(void* data);

//UI
void tell_user_send_ack_and_finish_game_r(void* data); //to do
void ask_the_user_if_wants_to_play_again_r(void* data); //to do
void ask_user_being_client_and_send_decition_r(void* data); //to do
void ask_user_being_server_and_send_decition_r(void* data);

//execute
void execute_receive_action_and_send_ack_r(void* data); //for client
void execute_action_send_it_and_set_ack_time_out_r(void* data); //for server
void execute_receive_action_request_send_action_and_send_ack_r(void* data); //for server
void execute_saved_enemy_actions_r(void* data);
void execute_local_action_r(void* data);
void execute_extern_action_r(void* data);

//mapping
void check_map_and_save_send_ack_r(void* data);
void check_sum_and_send_ack_r(void* data);

//timers
void set_ack_time_out_r(void* data);
void received_ack_routine_r(void* data);

//others
void ask_for_name_r(void* data);
void finish_game_r(void* data);
void start_game_and_send_ack_r(void* data);
void receive_name_and_send_ack_r(void* data);
void check_and_send_action_request_r(void* data);

//loading
void load_and_send_enemy_action_r(void* data); //to do
void load_enemy_action_and_send_ack_r(void* data);
void load_action_and_send_it_back_r(void* data);
void load_enemy_action_r(void* data);
void save_enemy_action_r(void* data);