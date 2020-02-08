#pragma once
#include "Allegroclass.h"
#include <iostream>
#include <string>

enum menu_options { PLAY, OPTIONS };				// lo que puede seleccionar el user en el menu

enum messaje { WE_WON, GAME_OVER, OTHER_PLAYER_YES, OTHER_PLAYER_NO, INTRO, CONNECTION_LOST };			// mensajes para imprimir en pantalla


using namespace std;

class GraphicInterface
{
public:
	GraphicInterface();
	~GraphicInterface();

	void Init();

	// methods provided by the graphic interface
	string request_user_name();
	string request_user_IP();
	menu_options start_game_scenario();
	void start_game_scenario_alt();
	bool request_2_play_again();
	void print_messaje(messaje msj);

private:

	bool inited;
	//private methods
	string make_request(const char* text);
	void update_display(string str);

	//allegro queue for the keyboard events
	ALLEGRO_EVENT_QUEUE* al_ev_queue = NULL;

	//allegro timer for the FPS
	ALLEGRO_TIMER* al_fps_timer = NULL;

	ALLEGRO_FONT* font1 = NULL;
	ALLEGRO_FONT* font2 = NULL;
	ALLEGRO_BITMAP* image = NULL;
};

