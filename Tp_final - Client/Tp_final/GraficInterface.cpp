#include "GraficInterface.h"

#define AL_FONT_FILE ("Fonts/data-latin.ttf")
#define AL_FONT_SIZE (20)
#define IMAGE_DIR ("images/menu title 2.png")
#define REQUEST_USER_NAME_TEXT ("ENTER YOUR NAME")
#define REQUEST_USER_ID_TEXT ("ENTER YOUR ID")
#define REQUEST_2_PLAY_AGAIN ("PLAY AGAIN?")
#define WE_WON_MSJ ("WE WON!")
#define GAME_OVER_MSJ ("GAME OVER")
#define OTHER_PLAYER_YES_MSJ ("OTHER PLAYER WANTS ANOTHER ROUND")
#define OTHER_PLAYER_NO_MSJ ("OTHER PLAYER DOES NOT WANT ANOTHER ROUND")
#define CONNECTION_LOST_MSJ ("CONNECTION LOST !")
#define PLAY_TEXT ("press P to PLAY")
#define OPTIONS_TEXT ("press O to OPTIONS")
#define INTRO_TITLE_1 ("Estructura de algoritmos y datos (22.08)")
#define PROFES ("Profesores a cargo:")
#define AGUSTIN ("Agustin ...")
#define MARK ("MARK ...")
#define INTRO_TITLE_2 ("Trabajo practico final by:")
#define GUIDO ("Guido Panaggio 56214")
#define GERMAN ("German Bertachini 58750")
#define TOMI ("Tomas Orlando 57090")
#define TICKS_MARK (30)


void update_display(string str);

string make_request(ALLEGRO_EVENT_QUEUE * event_queue, const char * text);

string request_user_name(ALLEGRO_EVENT_QUEUE * event_queue)
{
	string name;

	name = make_request(event_queue, REQUEST_USER_NAME_TEXT);

	return name;
}

string request_user_IP(ALLEGRO_EVENT_QUEUE * event_queue)
{
	string ID;

	ID = make_request(event_queue, REQUEST_USER_ID_TEXT);

	return ID;
}

bool request_2_play_again(ALLEGRO_EVENT_QUEUE * event_queue)
{
	bool playAgain;


	ALLEGRO_FONT * font = NULL;
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, REQUEST_2_PLAY_AGAIN);
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 100 + SCREEN_W / 100, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "Y for YES, N for NO");
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 30 + SCREEN_W / 30, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "YES");
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "NO");
	al_flip_display();

	bool taken = false;
	ALLEGRO_EVENT event;
	unsigned int ticks = 0;

	while (!taken)
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_Y:
					taken = true;
					playAgain = true;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, REQUEST_2_PLAY_AGAIN);
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 100 + SCREEN_W / 100, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "Y for YES, N for NO");
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 30 + SCREEN_W / 30, 0);
					al_draw_text(font, al_map_rgb(0, 255, 0), SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "YES");
					al_draw_text(font, al_map_rgb(255, 255, 255), 3 * SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "NO");
					al_flip_display();
					break;
				case ALLEGRO_KEY_N:
					taken = true;
					playAgain = false;;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, REQUEST_2_PLAY_AGAIN);
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 100 + SCREEN_W / 100, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "Y for YES, N for NO");
					font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 30 + SCREEN_W / 30, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "YES");
					al_draw_text(font, al_map_rgb(0, 255, 0), 3 * SCREEN_W / 4, SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "NO");
					al_flip_display();
					break;
				default:
					break;
				}
			}
		}
	}

	while (ticks < TICKS_MARK*1.8)								// le damos un tiempo para que dure la pantalla actual
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_TIMER)
				ticks++;
		}
	}

	return playAgain;
}


void print_messaje(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_TIMER *fps, messaje msj)
{
	ALLEGRO_FONT * font1 = NULL;
	ALLEGRO_FONT * font2 = NULL;
	ALLEGRO_FONT * font_intro = NULL;
	ALLEGRO_FONT * font_name = NULL;

	font1 = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 20 + SCREEN_W / 20, 0);
	font2 = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
	font_intro = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
	font_name = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 40 + SCREEN_W / 40, 0);

	if (!font1  || !font2 || !font_intro || !font_name)
	{
		cout << "ERROR: font unable to load" << endl;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	ALLEGRO_EVENT event;

	bool ok = false;
	int ticks1 = 254;
	int ticks2 = 0;
	int ticks3 = 0;

	float x_WE_WON = SCREEN_W;
	float y_WE_WON = SCREEN_H / 3;
	float x_GAME_OVER = 0;
	float y_GAME_OVER = SCREEN_H / 2;
	float x_OTHER_PLAYER_YES = SCREEN_W / 2;
	float y_OTHER_PLAYER_YES = 0;
	float x_OTHER_PLAYER_NO = SCREEN_W / 2;
	float y_OTHER_PLAYER_NO = SCREEN_H;
	float x_CONN_LOST = SCREEN_W / 2;
	float y_CONN_LOST = SCREEN_H / 3;

	float x_INTRO_1 = SCREEN_W / 6;
	float y_INTRO_1 = SCREEN_H / 6;
	float x_PROFES = SCREEN_W / 6;
	float y_PROFES = 1.5*SCREEN_H / 6;
	float x_AGUS = SCREEN_W / 6;
	float y_AGUS = 3 * SCREEN_H / 6;
	float x_MARK = SCREEN_W / 6;
	float y_MARK = 4 * SCREEN_H / 6;
	float x_INTRO_2 = SCREEN_W / 6;
	float y_INTRO_2 = 1.5*SCREEN_H / 6;
	float x_GUIDO = SCREEN_W / 6;
	float y_GUIDO = 1.5*SCREEN_H;
	float x_GERMAN = -SCREEN_W;
	float y_GERMAN = 4*SCREEN_H / 6;
	float x_TOMI = SCREEN_W;
	float y_TOMI = 3*SCREEN_H / 6;

	float short_step = SCREEN_W / 700 + SCREEN_W / 700;
	float long_step = SCREEN_W / 400 + SCREEN_W / 400;

	while (!ok)
	{
		if (al_get_next_event(event_queue, &event)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
		{
			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				switch (msj)
				{
				case WE_WON:
					if (x_WE_WON > SCREEN_W / 2)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						x_WE_WON = x_WE_WON - short_step;
						al_draw_text(font1, al_map_rgb(255, 255, 0), x_WE_WON, y_WE_WON, ALLEGRO_ALIGN_CENTRE, WE_WON_MSJ);
						al_flip_display();
					}
					else
					{
						if (ticks3 < TICKS_MARK)
						{
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_draw_text(font1, al_map_rgb(255, 255, 255), x_WE_WON, y_WE_WON, ALLEGRO_ALIGN_CENTRE, WE_WON_MSJ);
							al_flip_display();
							ticks3++;
						}
						else if (ticks3 < 2 * TICKS_MARK)
						{
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_draw_text(font1, al_map_rgb(255, 255, 0), x_WE_WON, y_WE_WON, ALLEGRO_ALIGN_CENTRE, WE_WON_MSJ);
							al_flip_display();
							ticks3++;
						}
						else
							ticks3 = 0;
					}
					break;
				case GAME_OVER:
					if (x_GAME_OVER < SCREEN_W / 2)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						x_GAME_OVER = x_GAME_OVER + short_step;
						al_draw_text(font1, al_map_rgb(255, 0, 0), x_GAME_OVER, y_GAME_OVER, ALLEGRO_ALIGN_CENTRE, GAME_OVER_MSJ);
						al_flip_display();
					}
					break;
				case OTHER_PLAYER_YES:
					if (y_OTHER_PLAYER_YES < SCREEN_H / 2)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						y_OTHER_PLAYER_YES = y_OTHER_PLAYER_YES + short_step;
						al_draw_text(font2, al_map_rgb(255, 255, 255), x_OTHER_PLAYER_YES, y_OTHER_PLAYER_YES, ALLEGRO_ALIGN_CENTRE, OTHER_PLAYER_YES_MSJ);
						al_flip_display();
					}
					break;
				case OTHER_PLAYER_NO:
					if (y_OTHER_PLAYER_NO > SCREEN_H / 2)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						y_OTHER_PLAYER_NO = y_OTHER_PLAYER_NO - short_step;
						al_draw_text(font2, al_map_rgb(255, 255, 255), x_OTHER_PLAYER_NO, y_OTHER_PLAYER_NO, ALLEGRO_ALIGN_CENTRE, OTHER_PLAYER_NO_MSJ);
						al_flip_display();
					}
					break;
				case INTRO:
					if (ticks2 < 255)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
						al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_PROFES, y_PROFES, 0, PROFES);
						al_draw_text(font_name, al_map_rgb(ticks2, ticks2, ticks2), x_AGUS, y_AGUS, 0, AGUSTIN);
						al_draw_text(font_name, al_map_rgb(ticks2, ticks2, ticks2), x_MARK, y_MARK, 0, MARK);
						al_flip_display();
						ticks2 += 1;
					}
					else
					{
						if (ticks1 > 0)
						{
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_draw_text(font_intro, al_map_rgb(ticks1, ticks1, ticks1), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
							al_draw_text(font_intro, al_map_rgb(ticks1, ticks1, ticks1), x_PROFES, y_PROFES, 0, PROFES);
							al_draw_text(font_name, al_map_rgb(ticks1, ticks1, ticks1), x_AGUS, y_AGUS, 0, AGUSTIN);
							al_draw_text(font_name, al_map_rgb(ticks1, ticks1, ticks1), x_MARK, y_MARK, 0, MARK);
							al_flip_display();
							ticks1 -= 1;
						}
						else
							{
							if (x_TOMI > SCREEN_W / 6)
							{
								x_TOMI = x_TOMI - long_step;
								al_clear_to_color(al_map_rgb(0, 0, 0));
								al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
								al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_2, y_INTRO_2, 0, INTRO_TITLE_2);
								al_draw_text(font_name, al_map_rgb(255, 255, 255), x_TOMI, y_TOMI, 0, TOMI);
								al_flip_display();
							}
							else
							{
								if (x_GERMAN < SCREEN_W / 6)
								{
									x_GERMAN = x_GERMAN + long_step;
									al_clear_to_color(al_map_rgb(0, 0, 0));
									al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
									al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_2, y_INTRO_2, 0, INTRO_TITLE_2);
									al_draw_text(font_name, al_map_rgb(255, 255, 255), x_TOMI, y_TOMI, 0, TOMI);
									al_draw_text(font_name, al_map_rgb(255, 255, 255), x_GERMAN, y_GERMAN, 0, GERMAN);
									al_flip_display();
								}
								else
								{
									if (y_GUIDO > 5 * SCREEN_H / 6)
									{
										y_GUIDO -= short_step;
										al_clear_to_color(al_map_rgb(0, 0, 0));
										al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
										al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_2, y_INTRO_2, 0, INTRO_TITLE_2);
										al_draw_text(font_name, al_map_rgb(255, 255, 255), x_TOMI, y_TOMI, 0, TOMI);
										al_draw_text(font_name, al_map_rgb(255, 255, 255), x_GERMAN, y_GERMAN, 0, GERMAN);
										al_draw_text(font_name, al_map_rgb(255, 255, 255), x_GUIDO, y_GUIDO, 0, GUIDO);
										al_flip_display();
									}
									else
									{
										if (ticks3 < TICKS_MARK)
										{
											al_clear_to_color(al_map_rgb(0, 0, 0));
											al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
											al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_2, y_INTRO_2, 0, INTRO_TITLE_2);
											al_draw_text(font_name, al_map_rgb(255, 255, 255), x_TOMI, y_TOMI, 0, TOMI);
											al_draw_text(font_name, al_map_rgb(255, 255, 255), x_GERMAN, y_GERMAN, 0, GERMAN);
											al_draw_text(font_name, al_map_rgb(255, 255, 255), x_GUIDO, y_GUIDO, 0, GUIDO);
											al_flip_display();
											ticks3++;
										}
										else if (ticks3 < 2 * TICKS_MARK)
										{
											al_clear_to_color(al_map_rgb(0, 0, 0));
											al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_1, y_INTRO_1, 0, INTRO_TITLE_1);
											al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_INTRO_2, y_INTRO_2, 0, INTRO_TITLE_2);
											al_draw_text(font_name, al_map_rgb(200, 0, 0), x_TOMI, y_TOMI, 0, TOMI);
											al_draw_text(font_name, al_map_rgb(200, 0, 0), x_GERMAN, y_GERMAN, 0, GERMAN);
											al_draw_text(font_name, al_map_rgb(200, 0, 0), x_GUIDO, y_GUIDO, 0, GUIDO);
											al_flip_display();
											ticks3++;
										}
										else
											ticks3 = 0;
									}
								}
							}
						}
					}
					break;
				case CONNECTION_LOST:
					if (ticks2 < TICKS_MARK * 2)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_CONN_LOST, y_CONN_LOST, ALLEGRO_ALIGN_CENTER, CONNECTION_LOST_MSJ);
						al_flip_display();
						ticks2++;
					}
					else if (ticks2 < TICKS_MARK * 3)
					{
					al_clear_to_color(al_map_rgb(0, 0, 0));
//					al_draw_text(font_intro, al_map_rgb(255, 255, 255), x_CONN_LOST, y_CONN_LOST, ALLEGRO_ALIGN_CENTER, CONNECTION_LOST_MSJ);
					al_flip_display();
					ticks2++;
					}
					else
						ticks2 = 0;
					break;
				default:
					break;
				}
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
				ok = true;
		}
	}
}

menu_options start_game_scenario(ALLEGRO_EVENT_QUEUE * event_queue, ALLEGRO_TIMER *fps)
{
	ALLEGRO_FONT * font = NULL;
	ALLEGRO_BITMAP  *image = NULL;

	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 30 + SCREEN_W / 30, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;
	}

	image = al_load_bitmap(IMAGE_DIR);
	if (!image) 
	{
		fprintf(stderr, "failed to load image !\n");
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	ALLEGRO_EVENT event;
	menu_options op;

	bool taken = false;
	int ticks = 0;

	float x_play = SCREEN_W / 6;
	float y_play = 4*SCREEN_H/6;
	float x_options = SCREEN_W / 6;
	float y_options = 5 * SCREEN_H / 6;

	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), (SCREEN_W - al_get_bitmap_width(image)) / 2, SCREEN_H / 10, al_get_bitmap_width(image) / 1, al_get_bitmap_height(image) / 1, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), x_play, y_play, 0, PLAY_TEXT);
	al_draw_text(font, al_map_rgb(255, 255, 255), x_options, y_options, 0, OPTIONS_TEXT);
	al_flip_display();

	while (!taken)
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_P:
					taken = true;
					op = PLAY;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), (SCREEN_W - al_get_bitmap_width(image)) / 2, SCREEN_H / 10, al_get_bitmap_width(image) / 1, al_get_bitmap_height(image) / 1, 0);
					al_draw_text(font, al_map_rgb(0, 255, 0), x_play, y_play, 0, PLAY_TEXT);
					al_draw_text(font, al_map_rgb(255, 255, 255), x_options, y_options, 0, OPTIONS_TEXT);
					al_flip_display();
//					al_rest(0.9);
					break;
				case ALLEGRO_KEY_O:
					taken = true;
					op = OPTIONS;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), (SCREEN_W - al_get_bitmap_width(image)) / 2, SCREEN_H / 10, al_get_bitmap_width(image) / 1, al_get_bitmap_height(image) / 1, 0);
					al_draw_text(font, al_map_rgb(255, 255, 255), x_play, y_play, 0, PLAY_TEXT);
					al_draw_text(font, al_map_rgb(0, 255, 0), x_options, y_options, 0, OPTIONS_TEXT);
					al_flip_display();
//					al_rest(0.9);
					break;
				default:
					break;
				}
			}
		}
	}

	while (ticks < TICKS_MARK*1.8)
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_TIMER)
				ticks++;
		}
	}
	return op;

	al_destroy_bitmap(image);
}











string make_request(ALLEGRO_EVENT_QUEUE * event_queue, const char * text)
{
	string name;


	ALLEGRO_FONT * font = NULL;
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W/50 + SCREEN_W/50, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, text);
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 75 + SCREEN_W / 75, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "press ENTER to continue");
	al_flip_display();

	bool nameSet = false;
	ALLEGRO_EVENT event;
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);

	while (!nameSet)
	{
		if (al_get_next_event(event_queue, &event))
		{
			if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (event.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					name.push_back('a');
					al_flip_display();
					break;
				case ALLEGRO_KEY_B:
					name.push_back('b');
					break;
				case ALLEGRO_KEY_C:
					name.push_back('c');
					break;
				case ALLEGRO_KEY_D:
					name.push_back('d');
					break;
				case ALLEGRO_KEY_E:
					name.push_back('e');
					break;
				case ALLEGRO_KEY_F:
					name.push_back('f');
					break;
				case ALLEGRO_KEY_G:
					name.push_back('g');
					break;
				case ALLEGRO_KEY_H:
					name.push_back('h');
					break;
				case ALLEGRO_KEY_I:
					name.push_back('i');
					break;
				case ALLEGRO_KEY_J:
					name.push_back('j');
					break;
				case ALLEGRO_KEY_K:
					name.push_back('k');
					break;
				case ALLEGRO_KEY_L:
					name.push_back('l');
					break;
				case ALLEGRO_KEY_M:
					name.push_back('m');
					break;
				case ALLEGRO_KEY_N:
					name.push_back('n');
					break;
				case ALLEGRO_KEY_O:
					name.push_back('o');
					break;
				case ALLEGRO_KEY_P:
					name.push_back('p');
					break;
				case ALLEGRO_KEY_Q:
					name.push_back('q');
					break;
				case ALLEGRO_KEY_R:
					name.push_back('r');
					break;
				case ALLEGRO_KEY_S:
					name.push_back('s');
					break;
				case ALLEGRO_KEY_T:
					name.push_back('t');
					break;
				case ALLEGRO_KEY_U:
					name.push_back('u');
					break;
				case ALLEGRO_KEY_V:
					name.push_back('v');
					break;
				case ALLEGRO_KEY_W:
					name.push_back('w');
					break;
				case ALLEGRO_KEY_X:
					name.push_back('x');
					break;
				case ALLEGRO_KEY_Y:
					name.push_back('y');
					break;
				case ALLEGRO_KEY_Z:
					name.push_back('z');
					break;
				case ALLEGRO_KEY_1:
					name.push_back('1');
					break;
				case ALLEGRO_KEY_2:
					name.push_back('2');
					break;
				case ALLEGRO_KEY_3:
					name.push_back('3');
					break;
				case ALLEGRO_KEY_4:
					name.push_back('4');
					break;
				case ALLEGRO_KEY_5:
					name.push_back('5');
					break;
				case ALLEGRO_KEY_6:
					name.push_back('6');
					break;
				case ALLEGRO_KEY_7:
					name.push_back('7');
					break;
				case ALLEGRO_KEY_8:
					name.push_back('8');
					break;
				case ALLEGRO_KEY_9:
					name.push_back('9');
					break;
				case ALLEGRO_KEY_0:
					name.push_back('0');
					break;
				case ALLEGRO_KEY_SPACE:
					name.push_back(' ');
					break;
				case ALLEGRO_KEY_ENTER:
					nameSet = true;
					break;
				case ALLEGRO_KEY_BACKSPACE:
					if(name.length() > 0)
						name.pop_back();
				default:
					break;
				}
				update_display(name);
			}
		}
	}

	return name;
}

void update_display(string name)
{
	ALLEGRO_FONT * font = NULL;

	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 50 + SCREEN_W / 50, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, REQUEST_USER_NAME_TEXT);
	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 75 + SCREEN_W / 75, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;;
	}
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 2 * SCREEN_H / 3, ALLEGRO_ALIGN_CENTRE, "press ENTER to continue");

	font = al_load_ttf_font(AL_FONT_FILE, SCREEN_W / 30 + SCREEN_W / 30, 0);
	if (!font)
	{
		cout << "ERROR: font unable to load" << endl;;
	}
	al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_W / 2, 2 * SCREEN_H / 6, ALLEGRO_ALIGN_CENTRE, name.c_str());
	al_flip_display();
}