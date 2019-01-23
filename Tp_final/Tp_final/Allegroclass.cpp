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
				if (this->Display = al_create_display(this->SCREEN_W, this->SCREEN_H)) {
					if ((Userdata.my_allegro_data.Background = al_create_bitmap(this->SCREEN_W, this->SCREEN_H))&&(Userdata.my_allegro_data.WindowsBackground = al_create_bitmap(this->SCREEN_W, this->SCREEN_H))) {
						if (this->al_queue = al_create_event_queue()) {
							if(this->time_out_timers_queue = new std::queue<ALLEGRO_TIMER*>()){
										if ((Userdata.my_allegro_data.Background = al_load_bitmap("Scenario.png"))&&(Userdata.my_allegro_data.WindowsBackground = al_load_bitmap("stars.png"))) {
											ret = true;
											al_draw_bitmap(Userdata.my_allegro_data.Background, 0, 0, NULL);
											al_draw_bitmap(Userdata.my_allegro_data.WindowsBackground, 0, 0, NULL);
										}
										else {
											ret = false;
											al_destroy_display(this->Display);
											al_destroy_bitmap(Userdata.my_allegro_data.Background);
											al_destroy_event_queue(this->al_queue);
											//al_destroy_timer(this->time_out_timer);
										}
							}
							else{
								al_destroy_display(this->Display);
								al_destroy_bitmap(Userdata.my_allegro_data.Background);
								al_destroy_event_queue(this->al_queue);
							}
						}
						else {
							al_destroy_display(this->Display);
							al_destroy_bitmap(Userdata.my_allegro_data.Background);
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
		}
	else{
		ret = false;
	}

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
	/*	
	for (int i = 0; i < 15; i++) {
		if (Userdata.WormWalk[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	for (int i = 0; i < 10; i++) {
		if (Userdata.WormJump[i] = al_create_bitmap(60, 60)) {}
		else ret = false;
	}

	if (ret) {
		al_register_event_source(this->al_queue, al_get_display_event_source(this->Display));
		al_register_event_source(this->al_queue, al_get_keyboard_event_source());
		al_register_event_source(this->soft_queue, al_get_timer_event_source(time_out_timer));
	}
	else {
		for (int i = 0; i < 15; i++) {
			al_destroy_bitmap(Userdata.WormWalk[i]);
		}
		for (int i = 0; i < 10; i++) {
			al_destroy_bitmap(Userdata.WormJump[i]);
		}
	}
	*/
	//loadPlayMusic();

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
	al_start_timer(new_timer);
}
void Allegro::dequeu_time_out_timer() {
	if(this->time_out_timers_queue->size() >= 1){
		ALLEGRO_TIMER* new_timer = this->time_out_timers_queue->front();
		this->time_out_timers_queue->pop();
		al_stop_timer(new_timer);
		al_destroy_timer(new_timer);
	}
}

bool Allegro::no_time_outs() {
	return (time_out_timers_queue->size() == 0);
}