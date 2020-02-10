#include "DRAW.h"
#include <vector>

#define FOLDER_SCENARIO	("scenario")
#define FILE_FLOOR_BOTTOM	("floor_bottom")
#define FILE_FLOOR_TOP	("floor_top")
#define FILE_FLOOR_RIGHT	("floor_corner_right")
#define FILE_FLOOR_LEFT	("floor_corner_left")
#define FILE_BACKGROUND	("background_")

#define FOLDER_MAIN_SONG ("main song")
#define FILE_SONG ("one-punch-man-8-bit-cover.ogg")

#define AL_FONT_FILE ("Fonts/data-latin.ttf")
#define AL_FONT_SIZE (20)

#define TOTAL_LEVELS (10)


DRAW::DRAW()
{
	step_background = 0;

	ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));  // change the working directory
	al_destroy_path(path);

	load_scenario_bitmaps();
	load_score_font();

	images = new ImageContainer();
	audio = new AudioContainer();
}


DRAW::~DRAW()
{
	delete images;
	delete audio;
}

Obj_Graf_Player* DRAW::createObjGraf(unsigned int ID, PLAYER_TYPE type)
{
	Obj_Graf_Player *obj = new Obj_Graf_Player(ID, type, images, audio);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Enemy* DRAW::createObjGraf(unsigned int ID, ENEMY_TYPE type)
{
	Obj_Graf_Enemy *obj = new Obj_Graf_Enemy(ID, type, images, audio);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Projectile* DRAW::createObjGraf(unsigned int ID, PROYECTILE_TYPE type)
{
	Obj_Graf_Projectile *obj = new Obj_Graf_Projectile(ID, type, images, audio);
	this->mapObjGraf[ID] = obj;
	return obj;
}


void DRAW::draw()		
{
	drawLevel();

	vector<unsigned int> keys;

	for (map<unsigned int, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<unsigned int>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		if (this->mapObjGraf[*it]->isActive())										// si el objeto grafico esta activo
			this->mapObjGraf[*it]->draw();											// se dibuja

	al_flip_display();
}

void DRAW::destroyObj(unsigned int ID)
{
	this->mapObjGraf[ID]->destroy();
}

void DRAW::destroyAll()
{
	vector<unsigned int> keys;

	for (map<unsigned int, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<unsigned int>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		this->mapObjGraf[*it]->destroy();										// si el objeto grafico esta activo
}

void DRAW::setLevel(unsigned int level)
{
	this->level = level;
	this->screen_w = al_get_bitmap_width(backgrounds[level - 1]);
	this->screen_h = al_get_bitmap_height(backgrounds[level - 1]);
}

bool DRAW::secuenceOver(unsigned int ID)
{
	return mapObjGraf[ID]->secuenceOver();
}

void DRAW::reset(unsigned int ID)
{
	this->mapObjGraf[ID]->reset();
}

void DRAW::add_level(const unsigned char * level)
{
	levels.push_back(std::string((char *)level));
}

void DRAW::load_scenario_bitmaps(void)
{
	string carpeta1 = FOLDER_SCENARIO;
	string file = FILE_FLOOR_BOTTOM;

	string imageDir = carpeta1 + '/' + file + ".png";

	this->floor_bottom = al_load_bitmap(imageDir.c_str());

	file = FILE_FLOOR_TOP;
	imageDir = carpeta1 + '/' + file + ".png";
	this->floor_top = al_load_bitmap(imageDir.c_str());

	file = FILE_FLOOR_LEFT;
	imageDir = carpeta1 + '/' + file + ".png";
	this->floor_corner_left = al_load_bitmap(imageDir.c_str());

	file = FILE_FLOOR_RIGHT;
	imageDir = carpeta1 + '/' + file + ".png";
	this->floor_corner_right = al_load_bitmap(imageDir.c_str());

	file = FILE_BACKGROUND;
	this->backgrounds = new ALLEGRO_BITMAP * [TOTAL_LEVELS];
	for (int i = 0; i < TOTAL_LEVELS; i++)
	{
		imageDir = carpeta1 + '/' + file + to_string(i + 1) + ".png";
		this->backgrounds[i] = al_load_bitmap(imageDir.c_str());
		if (!this->backgrounds[i])
			cout << "ERROR: could not load scenario !" << endl;
	}

	if (!floor_bottom || !floor_top)
		cout << "ERROR: could not load scenario !" << endl;
}

void DRAW::load_score_font(void)
{
	score_font = al_load_ttf_font(AL_FONT_FILE, DISPLAY_W / 50 + DISPLAY_H / 50, 0);
	if (!score_font)
	{
		cout << "ERROR: score font unable to load" << endl;
	}
}

void DRAW::drawLevel()
{
	draw_dynamic_background();
	//al_draw_scaled_bitmap(backgrounds[level - 1], 0, 0, screen_w, screen_h, 0, 0, DISPLAY_W, DISPLAY_H, 0);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			char block_type = levels[level - 1].c_str()[i * 16 + j];

			if (i > 0 && j > 0 && j < 15 && block_type == 'F')
			{
				char upper_block_type = levels[level - 1].c_str()[(i - 1) * 16 + j];
				char left_block_type = levels[level - 1].c_str()[(i) * 16 + j - 1];
				char right_block_type = levels[level - 1].c_str()[(i) * 16 + j + 1];

				if(upper_block_type == 'F')
					al_draw_scaled_bitmap(floor_bottom, 0, 0, al_get_bitmap_width(floor_bottom), al_get_bitmap_height(floor_bottom), BLOCK_SIZE * j, BLOCK_SIZE * i, BLOCK_SIZE, BLOCK_SIZE, 0);
				else if(left_block_type != 'F')
					al_draw_scaled_bitmap(floor_corner_left, 0, 0, al_get_bitmap_width(floor_corner_left), al_get_bitmap_height(floor_corner_left), BLOCK_SIZE * j, BLOCK_SIZE * i, BLOCK_SIZE, BLOCK_SIZE, 0);
				else if (right_block_type != 'F')
					al_draw_scaled_bitmap(floor_corner_right, 0, 0, al_get_bitmap_width(floor_corner_right), al_get_bitmap_height(floor_corner_right), BLOCK_SIZE * j, BLOCK_SIZE * i, BLOCK_SIZE, BLOCK_SIZE, 0);
				else
					al_draw_scaled_bitmap(floor_top, 0, 0, al_get_bitmap_width(floor_top), al_get_bitmap_height(floor_top), BLOCK_SIZE * j, BLOCK_SIZE * i, BLOCK_SIZE, BLOCK_SIZE, 0);
			}
			else if(block_type == 'F')
				al_draw_scaled_bitmap(floor_bottom, 0, 0, al_get_bitmap_width(floor_bottom), al_get_bitmap_height(floor_bottom), BLOCK_SIZE * j, BLOCK_SIZE * i, BLOCK_SIZE, BLOCK_SIZE, 0);
		}
	}
	draw_game_score();
}

void DRAW::draw_dynamic_background()
{
	float disp_scale_factor;
	DISPLAY_W > DISPLAY_H ? disp_scale_factor = (float)DISPLAY_W / (float)DISPLAY_H : disp_scale_factor = (float)DISPLAY_H / (float)DISPLAY_W;

	float off_screen_percentage;
	if ((step_background + screen_h * disp_scale_factor) < screen_w)
		al_draw_scaled_bitmap(backgrounds[level - 1], step_background, 0, screen_h * disp_scale_factor, screen_h, 0, 0, DISPLAY_W, DISPLAY_H, 0);
	else
	{
		off_screen_percentage = (step_background + screen_h * disp_scale_factor - screen_w) / (screen_h * disp_scale_factor);
		al_draw_scaled_bitmap(backgrounds[level - 1], step_background, 0, screen_w - step_background, screen_h, 0, 0, DISPLAY_W - DISPLAY_W* off_screen_percentage, DISPLAY_H, 0);
		al_draw_scaled_bitmap(backgrounds[level - 1], 0, 0, screen_h * disp_scale_factor, screen_h, DISPLAY_W - DISPLAY_W * off_screen_percentage + 1, 0, DISPLAY_W, DISPLAY_H, 0);
	}
	step_background++;
	if (step_background >= screen_w)
		step_background = 0;
}

void DRAW::draw_game_score()
{
	string score = "SCORE: " + to_string(game_points.get_game_points());
	al_draw_text(score_font, al_map_rgb(0, 0, 0), BLOCK_SIZE * 6 / 5, DISPLAY_H / 50, 0, score.c_str());
}

void DRAW::activeObj(unsigned int ID)
{
	mapObjGraf[ID]->activeObj();
}

void DRAW::disactiveObj(unsigned int ID)
{
	mapObjGraf[ID]->disactiveObj();
}
bool DRAW::finished_drawing_step(unsigned int ID)
{
	return mapObjGraf[ID]->finished_drawing_step();
}
void DRAW::add_observer(unsigned int ID, Observer* observers) {
	mapObjGraf[ID]->add_observer(observers);
}

void DRAW::play_main_song(void)
{
	audio->play_main_song();
}

void DRAW::stop_main_song(void)
{
	audio->stop_main_song();
}
