#include <iostream>
#include "DRAW.h"

int simulation(void)
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
	DRAW.setLevel(1);

	PLAYER_TYPE type_player = TOM;
	PLAYER_STATE state_player = player_WALKING;

	DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 2,10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 3, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 4, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING_FOWARD;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 5, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 6, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 7, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_ATTACKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 8, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 8, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 6);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 7);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_PUSHING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_DYING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 10, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}



	//PLAYER_TYPE type_player2 = NICK;
	//PLAYER_STATE state_player2 = player_JUMPING_FOWARD;
	//POINT pos_player2(SCREEN_W / 6, SCREEN_H - BLOCK_SIZE * 6);

	//ENEMY_TYPE type_enemy = PURPLE;
	//ENEMY_STATE state_enemy = enemy_FALLING;
	//POINT pos_enemy(SCREEN_W / 6, SCREEN_H / 2);

	//ENEMY_TYPE type_enemy2 = FATTY;
	//ENEMY_STATE state_enemy2 = enemy_FALLING;
	//POINT pos_enemy2(SCREEN_W / 2, SCREEN_H / 2);

	//ENEMY_TYPE type_enemy3 = CRAZY;
	//ENEMY_STATE state_enemy3 = enemy_FALLING;
	//POINT pos_enemy3(2*SCREEN_W / 3, 2*SCREEN_H / 3);

	//PROYECTILE_TYPE type_proy = SNOW;
	//PROYECTILE_STATE state_proy = proy_MOVING;
	//POINT pos_proy(SCREEN_W / 6, SCREEN_H / 2);

	//PROYECTILE_TYPE type_proy2 = FIRE;
	//PROYECTILE_STATE state_proy2 = proy_MOVING;
	//POINT pos_proy2(SCREEN_W / 6, SCREEN_H / 3);

	//BALL_TYPE type_ball = BALL;
	//BALL_STATE state_ball = ball_MOVING;
	//POINT pos_ball(SCREEN_W / 6, SCREEN_H / 3);

	/*DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, pos_player);
	DRAW.createObjGraf(2, type);
	DRAW.startDraw<ENEMY_STATE>(state, 2, Right, pos_enemy);*/

	//DRAW.createObjGraf(1, type_player);
	//DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	//DRAW.createObjGraf(2, type_player2);
	//DRAW.startDraw<PLAYER_STATE>(state_player2, 2, Right, pos_player2);

	//DRAW.createObjGraf(1, type_enemy);
	//DRAW.startDraw<ENEMY_STATE>(state_enemy, 1, Left, pos_enemy);
	//DRAW.createObjGraf(2, type_enemy2);
	//DRAW.startDraw<ENEMY_STATE>(state_enemy2, 2, Right, pos_enemy2);
	//DRAW.createObjGraf(3, type_enemy3);
	//DRAW.startDraw<ENEMY_STATE>(state_enemy3, 3, Right, pos_enemy3);

	//DRAW.createObjGraf(2, type_proy2);
	//DRAW.startDraw<PROYECTILE_STATE>(state_proy2, 2, Right, pos_proy2);

	//DRAW.createObjGraf(3, type_enemy3);
	//DRAW.startDraw<ENEMY_STATE>(state_enemy3, 3, Right, pos_enemy3);

	//DRAW.createObjGraf(2, type_ball);
	//DRAW.startDraw<BALL_STATE>(state_ball, 2, Left, pos_ball);

	//for (int j = 0; j < 100; j++)
	//{
	//	for (int i = 0; i < 40; i++)
	//	{
	//		al_clear_to_color(al_map_rgb(0, 0, 0));
	//		DRAW.draw();
	//		al_flip_display();
	//		al_rest(1 / FPS);
	//	}
	//	DRAW.startDraw<ENEMY_STATE>(state_enemy, 1, Left, pos_enemy);
	//	DRAW.startDraw<ENEMY_STATE>(state_enemy2, 2, Right, pos_enemy2);
	//	DRAW.startDraw<ENEMY_STATE>(state_enemy3, 3, Right, pos_enemy3);
	//}

	//pos_proy.set_x_coord(pos_proy.get_x_coord() + BLOCK_SIZE);
	//state_proy = proy_IMPACT;
	//DRAW.startDraw<PROYECTILE_STATE>(state_proy, 1, Right, pos_proy);

	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//DRAW.loadLevel(1);
	//al_flip_display();

	//al_rest(2);
//	getchar();

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_shutdown_image_addon();
	DRAW.destroyObj(1);
	//DRAW.destroyObj(2);
	//DRAW.destroyObj(3);

	return 0;
}










/******************************     SIMULACION DEL PLAYER *******************************


		DRAW DRAW;
	DRAW.setLevel(1);

	PLAYER_TYPE type_player = TOM;
	PLAYER_STATE state_player = player_WALKING;

	DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 2,10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 3, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 4, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING_FOWARD;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 5, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 6, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 7, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_ATTACKING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 8, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 8, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 6);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 7);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_PUSHING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 9, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_DYING;
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Right, 10, 8);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}


	**************************** PARA LA IZQUIERDA ******************************

	DRAW DRAW;
	DRAW.setLevel(1);

	PLAYER_TYPE type_player = NICK;
	PLAYER_STATE state_player = player_WALKING;
	POINT pos_player(SCREEN_W - 2*BLOCK_SIZE, SCREEN_H - BLOCK_SIZE * 2);

	DRAW.createObjGraf(1, type_player);
	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING_FOWARD;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);
	pos_player.set_y_coord(pos_player.get_y_coord() - 2 * BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_ATTACKING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_WALKING;

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_JUMPING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	pos_player.set_y_coord(pos_player.get_y_coord() - 2 * BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_FALLING;
	pos_player.set_y_coord(pos_player.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_PUSHING;
	pos_player.set_y_coord(pos_player.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw<PLAYER_STATE>(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_player = player_DYING;
	pos_player.set_x_coord(pos_player.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_player, 1, Left, pos_player);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	****************************************************************************/




















/******************************** SIMULACION DE LOS ENEMIGOS *************************


	DRAW DRAW;
	DRAW.setLevel(1);

	ENEMY_TYPE type_enemy = CRAZY;
	ENEMY_STATE state_enemy = enemy_WALKING;
	POINT pos_enemy(BLOCK_SIZE, SCREEN_H - BLOCK_SIZE * 2);

	DRAW.createObjGraf(1, type_enemy);
	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	 state_enemy = enemy_WALKING;
	 pos_enemy.set_x_coord(2 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(3 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_JUMPING_FOWARD;
	pos_enemy.set_x_coord(4 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(5 * BLOCK_SIZE);
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() - 2*BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(6 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	//state_enemy = enemy_ATTACKING;
	//pos_enemy.set_x_coord(pos_enemy.get_x_coord() + BLOCK_SIZE);

	//DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	//while (!DRAW.secuenceOver(1))
	//{
	//	DRAW.draw();
	//	al_flip_display();
	//	al_rest(1 / FPS);
	//}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() +  BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_JUMPING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_FALLING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() - 2*BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_FALLING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_DYING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Right, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	*************************************************************************************


	********************************* PARA LA IZQUIERDA *********************************

		DRAW DRAW;
	DRAW.setLevel(1);

	ENEMY_TYPE type_enemy = CRAZY;
	ENEMY_STATE state_enemy = enemy_WALKING;
	POINT pos_enemy(SCREEN_W - 2*BLOCK_SIZE, SCREEN_H - BLOCK_SIZE * 2);

	DRAW.createObjGraf(1, type_enemy);
	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_JUMPING_FOWARD;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() - 2 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	//state_enemy = enemy_;
	//pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	//DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	//while (!DRAW.secuenceOver(1))
	//{
	//	DRAW.draw();
	//	al_flip_display();
	//	al_rest(1 / FPS);
	//}

	state_enemy = enemy_WALKING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_JUMPING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_FALLING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() - 2 * BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_FALLING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_WALKING;
	pos_enemy.set_y_coord(pos_enemy.get_y_coord() + BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_enemy = enemy_DYING;
	pos_enemy.set_x_coord(pos_enemy.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_enemy, 1, Left, pos_enemy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	**********************************************************************************/



















/******************************** SIMULACION DE PROYECTIL*********************************

	DRAW DRAW;
	DRAW.setLevel(10);

	PROYECTILE_TYPE type_proy = SNOW;
	PROYECTILE_STATE state_proy = proy_MOVING;
	POINT pos_proy(BLOCK_SIZE, SCREEN_H - BLOCK_SIZE * 2);

	DRAW.createObjGraf(1, type_proy);
	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	 state_proy = proy_MOVING;
	 pos_proy.set_x_coord(2 * BLOCK_SIZE);

	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_proy = proy_MOVING;
	pos_proy.set_x_coord(3 * BLOCK_SIZE);

	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_proy = proy_MOVING;
	pos_proy.set_x_coord(4 * BLOCK_SIZE);

	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_proy = proy_DECAYING;
	pos_proy.set_x_coord(5 * BLOCK_SIZE);

	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_proy = proy_IMPACT;
	pos_proy.set_x_coord(6 * BLOCK_SIZE);

	DRAW.startDraw(state_proy, 1, Right, pos_proy);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}


	***********************************************************************************/


/**************************** SIMULACION DE LA BOLA**********************************

		DRAW DRAW;
	DRAW.setLevel(10);

	BALL_TYPE type_ball = BALL;
	BALL_STATE state_ball = ball_MOVING;

	DRAW.createObjGraf(1, type_ball);
	DRAW.startDraw(state_ball, 1, Right, 2,10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;

	DRAW.startDraw(state_ball, 1, Right, 3, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;

	DRAW.startDraw(state_ball, 1, Right, 4, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;

	DRAW.startDraw(state_ball, 1, Right, 5, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_PUSHING;

	DRAW.startDraw(state_ball, 1, Right, 6, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_PUSHING;

	DRAW.startDraw(state_ball, 1, Right, 7, 10);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_DESTRUCTION;
	DRAW.startDraw(state_ball, 1, Right, 8, 10);

	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	**********************************************************************************/

/******************************* PARA LA IZQUIERDA ***********************************
	DRAW DRAW;
	DRAW.setLevel(10);

	BALL_TYPE type_ball = BALL;
	BALL_STATE state_ball = ball_MOVING;
	POINT_ pos_ball(SCREEN_W - 2*BLOCK_SIZE, SCREEN_H - BLOCK_SIZE * 2);

	DRAW.createObjGraf(1, type_ball);
	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_MOVING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_PUSHING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_PUSHING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	state_ball = ball_PUSHING;
	pos_ball.set_x_coord(pos_ball.get_x_coord() - BLOCK_SIZE);

	DRAW.startDraw(state_ball, 1, Left, pos_ball);
	while (!DRAW.secuenceOver(1))
	{
		DRAW.draw();
		al_flip_display();
		al_rest(1 / FPS);
	}

	****************************************************************************************/