#pragma once
#include "GraficObjectPlayer.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectProjectile.h"
#include "GraficObjectBall.h"
#include <iostream>
#include <map>
#include <vector>

#define SCREEN_W (16*BLOCK_SIZE)
#define SCREEN_H (12*BLOCK_SIZE)

using namespace std;

class DRAW
{
public:
	DRAW();
	~DRAW();
//	bool init();
	void createObjGraf(double ID, PLAYER_TYPE type);						// crea un objeto grafico del tipo deseado y se lo añade al mapa de objetos
	void createObjGraf(double ID, ENEMY_TYPE type);
	void createObjGraf(double ID, PROYECTILE_TYPE type);
	void createObjGraf(double ID, BALL_TYPE type);
	template <typename T> void startDraw(T state, double ID, Direction dir, int pos_x, int pos_y);		// inicia la secuencia de dibujo de un objeto grafico
	void draw();															// esta funcion refresca los objetos graficos activos
	void destroyObj(double ID);
	void destroyAll();														// destruye todos los objetos graficos
	void setLevel(unsigned int level);
	bool secuenceOver(double ID);
	void reset(unsigned int ID);

private:
	map<double, Obj_Graf*> mapObjGraf;									// mapa de objetos graficos
	ALLEGRO_BITMAP * floor = NULL;
	ALLEGRO_BITMAP * empty = NULL;
	ALLEGRO_BITMAP ** backgrounds = NULL;
	vector<string> levels;
	unsigned int level;
	void drawLevel();
};



template<typename T>
inline void DRAW::startDraw(T state, double ID, Direction dir, int x, int y)
{
	POINT_ pos;
	pos.set_x_coord(x*BLOCK_SIZE);
	pos.set_y_coord(y*BLOCK_SIZE);
	void *vp;
	vp = &state;
	mapObjGraf[ID]->startDraw(dir, vp, pos);
}