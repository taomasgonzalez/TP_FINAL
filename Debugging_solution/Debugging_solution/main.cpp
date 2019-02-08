#include <iostream>
#include "DRAW.h"

#define SCREEN_W (16*BLOCK_SIZE)
#define SCREEN_H (12*BLOCK_SIZE)

int main(void)
{
	//Allegro Allegro;

	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_TIMER * timer = NULL;
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_EVENT_QUEUE	* queue = NULL;

	if (al_init())	//inicializo allegro
	{
		if (al_install_audio())	//inicializo los audios
		{
			if (al_init_acodec_addon())
			{
				if ((al_reserve_samples(1)))	//para la musica
				{
					if (al_init_image_addon())	//addon para las imagenes
					{
						if (al_install_keyboard())	//inicializo para que lea teclado
						{
							if ((queue = al_create_event_queue()))	//creo la cola de eventos
							{
								if ((display = al_create_display(SCREEN_W, SCREEN_H)))	//creo el display
								{
									al_register_event_source(queue, al_get_keyboard_event_source());	//hago que la cola de eventos registre el teclado
									al_register_event_source(queue, al_get_display_event_source(display));	//que registre cosas del display
																														//al_register_event_source(this->queue, al_get_timer_event_source(this->timer));	//y del timer
								}
							}
						}
					}
					else
						fprintf(stderr, "ERROR: Failed to load Image addon\n");
				}
				else
					fprintf(stderr, "ERROR: Failed to reserve sample\n");
			}
			else
				fprintf(stderr, "ERROR: Failed to install acodec addon\n");
		}
		else
			fprintf(stderr, "ERROR: Failed to install audio\n");
	}
	else
		fprintf(stderr, "ERROR: Failed to initialize allegro system\n");

	DRAW DRAW;

	PLAYER_TYPE type_player = TOM;
	PLAYER_STATE state_player = player_JUMPING_FOWARD;
	POINT pos_player(SCREEN_W / 2, SCREEN_H / 2);

	//ENEMY_TYPE type = PURPLE;
	//ENEMY_STATE state = enemy_WALKING;
	//POINT pos_enemy(SCREEN_W / 6, SCREEN_H / 6);

	/*PROYECTILE_TYPE type_proy = SNOW;
	PROYECTILE_STATE state_proy = proy_MOVING;
	POINT pos_proy(SCREEN_W / 6, SCREEN_H / 2);*/

	/*DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, pos_player);
	DRAW.createObjGraf(2, type);
	DRAW.startDraw<ENEMY_STATE>(state, 2, Right, pos_enemy);*/

	DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);

	for (int i = 0; i < 25; i++)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		DRAW.draw();
		al_flip_display();
		al_rest(1/FPS);
	}

	/*pos_proy.set_x_coord(pos_proy.get_x_coord() + BLOCK_SIZE);
	state_proy = proy_IMPACT;
	DRAW.startDraw<PROYECTILE_STATE>(state_proy, 1, Right, pos_proy);

	for (int i = 0; i < 70; i++)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		DRAW.draw();
		al_flip_display();
		al_rest(0.25);
	}*/

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_shutdown_image_addon();
	DRAW.destroyObj(1);
	//DRAW.destroyObj(2);

	return 0;
}