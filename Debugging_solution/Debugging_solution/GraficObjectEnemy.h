#pragma once
#include "GraficObject.h"

enum ENEMY_TYPE {PURPLE, FATTY, CRAZY};

enum ENEMY_STATE { enemy_WALKING, enemy_JUMPING, enemy_JUMPING_FOWARD, enemy_IDLE, enemy_TRAPPED, enemy_ATTACKING, enemy_FALLING, enemy_DYING};				// algunos montruos no atacan

class Obj_Graf_Enemy :
	public Obj_Graf
{
public:
	Obj_Graf_Enemy();
	Obj_Graf_Enemy(double ID, ENEMY_TYPE type);		// luego tengo que ver como arreglo que me entrenen con un ENEMY_TYPE
	~Obj_Graf_Enemy();

	void draw();
	void startDraw(Direction dir, void *estado, POINT& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	ENEMY_TYPE type;
	ENEMY_STATE state;
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	unsigned int idleActualImage;
	void loadBitmap(ENEMY_TYPE type);										// dependiendo del enemigo se le cargan determinadas imagenes
	ALLEGRO_BITMAP ** walkImages = NULL;
	ALLEGRO_BITMAP ** jumpImages = NULL;
	ALLEGRO_BITMAP ** idleImages = NULL;
	ALLEGRO_BITMAP ** attackImages = NULL;
	ALLEGRO_BITMAP ** fallImages = NULL;
	ALLEGRO_BITMAP ** trapImages = NULL;
	ALLEGRO_BITMAP ** dieImages = NULL;
};

