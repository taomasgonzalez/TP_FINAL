#include "DRAW.h"
#include <vector>

#define FOLDER_SCENARIO	("scenario")
#define FILE_FLOOR	("Basic_Ground_Filler_Pixel")
#define FILE_EMPTY	("empty")
#define FILE_BACKGROUND	("background_")
#define TOTAL_LEVELS (10)


DRAW::DRAW()
{
	string carpeta1 = FOLDER_SCENARIO;
	string file = FILE_FLOOR;
	string imageDir = carpeta1 + '/' + file + ".png";
	this->floor = al_load_bitmap(imageDir.c_str());

	file = FILE_EMPTY;
	imageDir = carpeta1 + '/' + file + ".png";
	this->empty = al_load_bitmap(imageDir.c_str());

	file = FILE_BACKGROUND;
	this->backgrounds = new ALLEGRO_BITMAP *[TOTAL_LEVELS];
	for (int i = 0; i < TOTAL_LEVELS; i++)
	{
		imageDir = carpeta1 + '/' + file + to_string(i + 1) + ".png";
		this->backgrounds[i] = al_load_bitmap(imageDir.c_str());
		if(!this->backgrounds[i])
			cout << "ERROR: could not load scenario !" << endl;
	}

	if (!floor || !empty)
		cout << "ERROR: could not load scenario !" << endl;

	images = new ImageContainer();
}


DRAW::~DRAW()
{
	delete images;
}

Obj_Graf_Player* DRAW::createObjGraf(unsigned int ID, PLAYER_TYPE type)
{
	Obj_Graf_Player *obj = new Obj_Graf_Player(ID, type, images);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Enemy* DRAW::createObjGraf(unsigned int ID, ENEMY_TYPE type)
{
	Obj_Graf_Enemy *obj = new Obj_Graf_Enemy(ID, type, images);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Projectile* DRAW::createObjGraf(unsigned int ID, PROYECTILE_TYPE type)
{
	Obj_Graf_Projectile *obj = new Obj_Graf_Projectile(ID, type, images);
	this->mapObjGraf[ID] = obj;
	return obj;
}


void DRAW::draw()		
{
	this->drawLevel();

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
}

bool DRAW::secuenceOver(unsigned int ID)
{
	return mapObjGraf[ID]->secuenceOver();
}

void DRAW::reset(unsigned int ID)
{
	this->mapObjGraf[ID]->reset();
}

void DRAW::add_level(const char * level)
{
	levels.push_back(std::string(level));
}

void DRAW::drawLevel()
{

	al_draw_scaled_bitmap(backgrounds[level - 1], 0, 0, al_get_bitmap_width(backgrounds[level - 1]), al_get_bitmap_height(backgrounds[level - 1]), 0, 0, SCREEN_W, SCREEN_H, 0);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			char block_type = levels[level - 1].c_str()[i * 16 + j];
			std::cout << block_type;
			switch (block_type)
			{
			case 'F':
				al_draw_scaled_bitmap(floor, 0, 0, al_get_bitmap_width(floor), al_get_bitmap_height(floor), BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE, 0);
				break;
			default:
				al_draw_scaled_bitmap(empty, 0, 0, al_get_bitmap_width(empty), al_get_bitmap_height(empty), BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE, 0);
				break;
			}
		}
	}
}

void DRAW::activeObj(unsigned int ID)
{
	this->mapObjGraf[ID]->activeObj();
}

void DRAW::disactiveObj(unsigned int ID)
{
	this->mapObjGraf[ID]->disactiveObj();
}
