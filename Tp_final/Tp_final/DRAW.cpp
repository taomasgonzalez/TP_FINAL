#include "DRAW.h"
#include "csvReader.h"
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


	string level_1 = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFEEEEEEPEEEEEEEFFEEFFFFFFFFFFEEFFEEPEEEEEEEEPEEFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFETEEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_1);
	string level_2 = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFGEEEEEEEEEEEEGFFFFEEEEEEEEEEFFFFEEEEEEPEEEEEEEFFEFFFFFFFFFFFFEFFEEPEEEEEEEEPEEFFFFFFFEEEEFFFFFFFEEEEEEEEEEEEEEFFEEEEFFFFFFEEEEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_2);
	string level_3 = "FEEEEEEEEEEEEEEFFEEEEEEEEEEEEEEFFGEEEEEEEEEEEEGFFFFEEEEEEEEEEFFFFEEEEEEPEEEEEEEFFEFFFFFFFFFFFFEFFEEPEEEEEEEEPEEFFFFFFFEEEEFFFFFFFEEEEEEEEEEEEEEFFEEEEFFFFFFEEEEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_3);
	string level_4 = "FEEEEGEEEEGEEEEFFEEFFFFFFFFFFEEFFGEEEEEEEEEEEEGFFFFFFEEEEEEFFFFFFEEEEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEEPEEEEEEEEPEEFFFFFFFEEEEFFFFFFFEEEEEEEEEEEEEEFFEEEEFFFFFFEEEEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_4);
	string level_5 = "FEEEGEEGEEEEEEEFFEEFFFFFFFFEFEEFFEEEEEEEPEPEFEEFFEEFEFFFFFFFFEEFFEEFEPEPEEEEEEEFFEEFFFFFFFFEFEEFFEEEEEEEEEPEFEEFFEEFEFFFFFFFFEEFFEEFEEEEEEEEEEEFFEEFFFFFFFFFFEEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_5);
	string level_6 = "FEEEEEECEEEEEEEFFEEFFFFFFFFFFEEFFEEEEEEFFEEEEEEFFFFFEEFFFFEEFFFFFEEEGEFFFFEGEEEFFEFFFFFFFFFFFFEFFEPEEEFFFFEEEPEFFFFFEEFFFFEEFFFFFEEEPEEFFEEPEEEFFEEFFFFFFFFFFEEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_6);
	string level_7 = "FEEEEEGEEGEEEEEFFEEEEFFFFFFEEEEFFCEEEFEEEEFEEECFFFFEEFFFFFFEEFFFFFFEEEEEEEEEEFFFFFFFFFFEEFFFFFFFFEEEEEEEEEEEEEEFFFFFEEFFFFEEFFFFFFFPEEEEEEEEPFFFFFFFFFFEEFFFFFFFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_7);
	string level_8 = "FEEEEEEEEEGEGEEFFEEEEFFFFFFFFFEFFEEEEECECEEEEFEFFEFFFFFFFFFEEFEFFEFEEEEEEEEEEFEFFEFFEEFFFFFFFFEFFCEEEEEEEEEEEECFFFFFFFFEEFFFFFFFFFFEEPEEEEPEEFFFFFFFFFFEEFFFFFFFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_8);
	string level_9 = "FEEEEEEEEEEEEEEFFEEEEGEEEEGEEEEFFEEEFFFFFFFFEEEFFEEFFFFFFFFFFEEFFGEEEEEEEEEEEEGFFFFFFFFEEFFFFFFFFEEEECEEEECEEEEFFEEFFFFFFFFFFEEFFPEEEEECCEEEEEPFFFFFFEEFFEEFFFFFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_9);
	string level_10 = "FEECEEEGGEEECEEFFEEFFFFFFFFFFEEFFEEEEEEEEEEEEEEFFEFFFFFEEFFFFFEFFEEEEGFEEFGEEEEFFEFFFFFEEFFFFFEFFECEEEEEEEEEECEFFEFFFFFEEFFFFFEFFEFEEPEEEEPEEFEFFEFFFFFEEFFFFFEFFEETEEEEEEEENEEFFFFFFFFFFFFFFFFF";
	levels.push_back(level_10);
}


DRAW::~DRAW()
{
}

Obj_Graf_Player* DRAW::createObjGraf(double ID, PLAYER_TYPE type)
{
	Obj_Graf_Player *obj = new Obj_Graf_Player(ID, type);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Enemy* DRAW::createObjGraf(double ID, ENEMY_TYPE type)
{
	Obj_Graf_Enemy *obj = new Obj_Graf_Enemy(ID, type);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Projectile* DRAW::createObjGraf(double ID, PROYECTILE_TYPE type)
{
	Obj_Graf_Projectile *obj = new Obj_Graf_Projectile(ID, type);
	this->mapObjGraf[ID] = obj;
	return obj;
}

Obj_Graf_Ball* DRAW::createObjGraf(double ID, BALL_TYPE type)
{
	Obj_Graf_Ball *obj = new Obj_Graf_Ball(ID, type);
	this->mapObjGraf[ID] = obj;
	return obj;
}

void DRAW::draw()		
{
	this->drawLevel();

	vector<double> keys;

	for (map<double, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<double>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		if (this->mapObjGraf[*it]->isActive())										// si el objeto grafico esta activo
			this->mapObjGraf[*it]->draw();											// se dibuja
}

void DRAW::destroyObj(double ID)
{
	this->mapObjGraf[ID]->destroy();
}

void DRAW::destroyAll()
{
	vector<double> keys;

	for (map<double, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<double>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		this->mapObjGraf[*it]->destroy();										// si el objeto grafico esta activo
}

void DRAW::setLevel(unsigned int level)
{
	this->level = level;
}

bool DRAW::secuenceOver(double ID)
{
	return mapObjGraf[ID]->secuenceOver();
}

void DRAW::reset(unsigned int ID)
{
	this->mapObjGraf[ID]->reset();
}

void DRAW::drawLevel()
{
	const char* map;

	//map = give_me_the_CSV(level);

	char block_type;

	al_draw_scaled_bitmap(backgrounds[level - 1], 0, 0, al_get_bitmap_width(backgrounds[level - 1]), al_get_bitmap_height(backgrounds[level - 1]), 0, 0, SCREEN_W, SCREEN_H, 0);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			block_type = levels[level - 1].c_str()[i * 16 + j];
			switch (block_type)
			{
			case 'F':
				al_draw_scaled_bitmap(floor, 0, 0, al_get_bitmap_width(floor), al_get_bitmap_height(floor), BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE, 0);
				break;
			default:
//				al_draw_scaled_bitmap(empty, 0, 0, al_get_bitmap_width(empty), al_get_bitmap_height(empty), BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE, 0);
				break;
			}
		}
	}
}

