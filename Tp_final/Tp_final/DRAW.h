#pragma once
#include "GraficObjectPlayer.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectProjectile.h"
#include "GraficObjectBall.h"
#include <iostream>
#include <map>
#include <vector>

#include "AllegroClass.h"

/*

#define SCREEN_W (16*BLOCK_SIZE)
#define SCREEN_H (12*BLOCK_SIZE)

*/

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
	Obj_Graf_Ball* createObjGraf(unsigned int ID, BALL_TYPE type);

	template <typename T> void startDraw(T state, unsigned int ID, Direction dir, int pos_x, int pos_y);		// inicia la secuencia de dibujo de un objeto grafico
	void draw();															// esta funcion refresca los objetos graficos activos
	void destroyObj(unsigned int ID);
	void destroyAll();														// destruye todos los objetos graficos
	void setLevel(unsigned int level);
	void add_level(const char* level);
	bool secuenceOver(unsigned int ID);
	void reset(unsigned int ID);
	void activeObj(unsigned int ID);
	void disactiveObj(unsigned int ID);

private:
	map<unsigned int, Obj_Graf*> mapObjGraf;									// mapa de objetos graficos
	ALLEGRO_BITMAP * floor = NULL;
	ALLEGRO_BITMAP * empty = NULL;
	ALLEGRO_BITMAP ** backgrounds = NULL;
	vector<string> levels;
	unsigned int level;
	void drawLevel();
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
