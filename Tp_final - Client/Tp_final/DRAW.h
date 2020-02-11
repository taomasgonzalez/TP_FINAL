#pragma once
#include "GraficObjectPlayer.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectProjectile.h"
#include "PointsContainer.h"
#include <iostream>
#include <map>
#include <vector>
#include "ImageContainer.h"
#include "AllegroClass.h"
#include "Observer.h"


using namespace std;

class DRAW
{
public:
	DRAW();
	~DRAW();
//	bool init();
	Obj_Graf_Player* createObjGraf(unsigned int ID, PLAYER_TYPE type);						// crea un objeto grafico del tipo deseado y se lo añade al mapa de objetos
	Obj_Graf_Enemy* createObjGraf(unsigned int ID, ENEMY_TYPE type);
	Obj_Graf_Projectile* createObjGraf(unsigned int ID, PROYECTILE_TYPE type);

	template <typename T> void startDraw(T state, unsigned int ID, Direction dir, int pos_x, int pos_y);		// inicia la secuencia de dibujo de un objeto grafico
	void draw();															// esta funcion refresca los objetos graficos activos
	void destroyObj(unsigned int ID);
	void destroyAll();														// destruye todos los objetos graficos
	void setLevel(unsigned int level);
	void add_level(const unsigned char* level);
	bool secuenceOver(unsigned int ID);
	void reset(unsigned int ID);
	void activeObj(unsigned int ID);
	void disactiveObj(unsigned int ID);
	bool finished_drawing_step(unsigned int ID);
	void add_observer(unsigned int ID, Observer* observers);
	void play_main_song(void);
	void stop_main_song(void);

private:
	map<unsigned int, Obj_Graf*> mapObjGraf;									// mapa de objetos graficos
	//bitmaps for map drawing
	ALLEGRO_BITMAP* floor_bottom = NULL;
	ALLEGRO_BITMAP* floor_top = NULL;
	ALLEGRO_BITMAP* floor_corner_right = NULL;
	ALLEGRO_BITMAP* floor_corner_left = NULL;
	ALLEGRO_BITMAP** backgrounds = NULL;
	ALLEGRO_BITMAP* sub_bitmap = NULL;
	void load_scenario_bitmaps(void);
	void load_score_font(void);

	//font for score screen write
	ALLEGRO_FONT* score_font = 0;

	vector<string> levels;
	unsigned int level;
	unsigned int screen_w;
	unsigned int screen_h;
	unsigned int corner_right_h;
	unsigned int corner_right_w;
	unsigned int corner_left_h;
	unsigned int corner_left_w;
	unsigned int top_h;
	unsigned int top_w;
	unsigned int bottom_h;
	unsigned int bottom_w;
	unsigned int step_background;	//used for a dynamic background
	void drawLevel();
	void draw_dynamic_background();
	void draw_game_score();
	ImageContainer* images = NULL;
	AudioContainer* audio = NULL;
	PointsContainer game_points;
};



template<typename T>
inline void DRAW::startDraw(T state, unsigned int ID, Direction dir, int x, int y)
{
	POINT_ pos;
	pos.set_x_coord(x*BLOCK_SIZE);
	pos.set_y_coord(y*BLOCK_SIZE);
	void *vp;
	vp = &state;
	mapObjGraf[ID]->startDraw(dir, vp, pos);
}
