#include "Allegroclass.h"

Allegro::Allegro()
{
	this->Display = NULL;
	this->music = NULL;
	this->al_queue = NULL;
	this->time_out_timers_queue = new std::queue<ALLEGRO_TIMER*>;
}


Allegro::~Allegro()
{
	al_uninstall_keyboard();
	al_destroy_display(this->Display);
	al_destroy_event_queue(this->al_queue);
	stopMusic();
	al_uninstall_audio();
}


bool Allegro::Init(Userdata& Userdata) {
	bool ret = false;

	if (al_init()) {
		if (al_init_image_addon()) {
			if (al_install_keyboard()) {
				if (this->Display = al_create_display(DISPLAY_W, DISPLAY_H)) {
					if (this->al_queue = al_create_event_queue()) {
						if (this->time_out_timers_queue = new std::queue<ALLEGRO_TIMER*>()) {
							ret = true;
						}
						else {
							al_destroy_display(this->Display);
							al_destroy_event_queue(this->al_queue);
						}
					}
					else {
						al_destroy_display(this->Display);
						al_destroy_event_queue(this->al_queue);
					}
				}
			}
			else {
				ret = false;
				al_destroy_display(this->Display);
			}
		}
		else {
			ret = false;
			al_destroy_display(this->Display);
		}
	}
	else
		ret = false;

	this->time_out_timers_queue->push(al_create_timer(60.0 * 2 + 30.0)); //this->time_out_timer = al_create_timer(60.0*2+30.0)


	if (al_install_audio()) //Inicializo los addons de audio
	{
		if (al_init_acodec_addon()) {
			al_reserve_samples(1);
		}
		else
			ret = false;
	}
	else
		ret = false;

	return ret;
}

void Allegro::loadPlayMusic(void)
{
	this->music = al_load_sample(BACKGROUND_MUSIC);
	if (this->music)
		al_play_sample(this->music, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	else
		fprintf(stderr, "Unable to load background music\n");

}

void Allegro :: stopMusic(void)
{
	al_stop_samples();
	al_destroy_sample(music);
}

ALLEGRO_EVENT_QUEUE*  Allegro::get_al_queue() {
	return al_queue;
}


ALLEGRO_TIMER * Allegro::get_front_time_out_timer() {

	if ((this->time_out_timers_queue->size()) >= 1)
		return this->time_out_timers_queue->front();
	else
		return NULL;
}

void Allegro::append_time_out_timer() {
	ALLEGRO_TIMER* new_timer = al_create_timer(2*60.0+30.0);
	al_register_event_source(this->al_queue, al_get_timer_event_source(new_timer));
}
void Allegro::start_front_timer() {
	ALLEGRO_TIMER* new_timer = this->time_out_timers_queue->front();
	//al_start_timer(new_timer);
}
void Allegro::dequeu_time_out_timer() {
	if(this->time_out_timers_queue->size() >= 1){
		ALLEGRO_TIMER* new_timer = this->time_out_timers_queue->front();
		this->time_out_timers_queue->pop();
		//al_stop_timer(new_timer);
		al_destroy_timer(new_timer);
	}
}

bool Allegro::no_time_outs() {
	return (time_out_timers_queue->size() == 0);
}

//const float FPS = 50.0;
//const float SCREEN_W = 1920;
//const float SCREEN_H = 696;