#pragma once


void do_nothing(void* data);
void finish_game(void * data);
void set_ack_time_out(void* data);
void send_error_and_finish_game(void* data);
//analyze
void analayze_error(void*data);
//send
void send_ack(void * data);
void send_quit(void * data);
void send_ack_and_quit(void* data);
//others
void ask_for_name(void* data);

