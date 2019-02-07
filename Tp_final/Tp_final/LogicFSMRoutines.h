#pragma once


void do_nothing(void * data);//Dummy for the debugging of the protocol structure

							 //analyze
void analayze_error(void*data);
void analyze_we_won(void*data); //to do
void analyze_we_lost(void*data); //to do
void check_action(void* data);


//send
void send_map_is(void * data);
void send_ack(void * data);
void send_quit(void * data);
void send_name_is(void* data);
void send_ack_and_quit(void* data);
void execute_and_send_enemy_action(void* data);
void send_game_start(void* data);
void send_error_and_finish_game(void* data);
void send_action_and_set_ack_time_out(void* data);
void send_next_map(void*data);  //to do
void send_we_won(void*data);
void send_we_lost(void*data);
void send_game_over(void*data);
void send_play_again(void*data);
void send_enemy_action(void*data);
void save_enemy_action_and_send_it(void* data);
void send_action_request_and_set_ack_time_out(void* data); //for client
void send_action(void * data);

//UI
void tell_user_send_ack_and_finish_game(void*data); //to do
void ask_the_user_if_wants_to_play_again(void*data); //to do
void ask_user_being_client_and_send_decition(void*data); //to do
void ask_user_being_server_and_send_decition(void*data);

//execute
void execute_receive_action_and_send_ack(void*data); //for client
void execute_action_send_it_and_set_ack_time_out(void* data); //for server
void execute_receive_action_request_send_action_and_send_ack(void * data); //for server
void execute_saved_enemy_actions(void* data);
void execute_local_action(void* data);
void execute_extern_action(void* data);

//mapping
void check_map_and_save_send_ack(void* data);
void check_sum_and_send_ack(void* data);

//timers
void set_ack_time_out(void* data);
void received_ack_routine(void* data);

//others
void ask_for_name(void* data);
void finish_game(void * data);
void start_game_and_send_ack(void* data);
void receive_name_and_send_ack(void*data);
void check_and_send_action_request(void*data);

//loading
void load_and_send_enemy_action(void*data); //to do
void load_enemy_action_and_send_ack(void* data);
void load_action_and_send_it_back(void* data);
void load_enemy_action(void* data);
void save_enemy_action(void* data);
