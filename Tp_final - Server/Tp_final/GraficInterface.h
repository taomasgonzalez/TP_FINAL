#pragma once

#include "AllegroClass.h"

#include <iostream>
#include <string>

using namespace std;



enum menu_options {PLAY, OPTIONS};													// lo que puede seleccionar el user en el menu

enum messaje {WE_WON, GAME_OVER, OTHER_PLAYER_YES, OTHER_PLAYER_NO, INTRO, CONNECTION_LOST};			// mensajes para imprimir en pantalla



string request_user_name(ALLEGRO_EVENT_QUEUE * event_queue, const float screen_w, const float screen_h);

string request_user_IP(ALLEGRO_EVENT_QUEUE * event_queue, const float screen_w, const float screen_h);

menu_options start_game_scenario(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_TIMER *fps, const float screen_w, const float screen_h);

bool request_2_play_again(ALLEGRO_EVENT_QUEUE * event_queue, const float screen_w, const float screen_h);

void print_messaje(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_TIMER *fps, messaje, const float screen_w, const float screen_h);
