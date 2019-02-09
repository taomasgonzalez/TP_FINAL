#pragma once

#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "Userdata.h"
#include <queue>
#define BACKGROUND_MUSIC "Soundtracks/Super Mario Bros Soundtrack.wav"
#define JUMP_MUSIC "Soundtracks/Super Mario Bros - Jump Sound Effect.wav"

class Allegro
{
public:
	Allegro();
	~Allegro();
	bool Init(Userdata&);


	ALLEGRO_DISPLAY* Display;
	ALLEGRO_SAMPLE * music;

	const float FPS = 50.0;
	const float SCREEN_W = 1920;
	const float SCREEN_H = 696;

	void loadPlayMusic();
	void stopMusic();

	ALLEGRO_EVENT_QUEUE*  get_al_queue();
	ALLEGRO_TIMER * get_front_time_out_timer();
	void append_time_out_timer();
	void dequeu_time_out_timer();
	void start_front_timer();
	bool no_time_outs();
private:
	ALLEGRO_EVENT_QUEUE * al_queue;			//cola para eventos de allegro
	std::queue<ALLEGRO_TIMER*>* time_out_timers_queue;


};

