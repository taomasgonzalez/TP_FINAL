#pragma once
#include "GraficObject.h"

enum ENEMY_TYPE {PURPLE, FATTY, CRAZY};

enum ENEMY_STATE { enemy_WALKING, enemy_JUMPING, enemy_JUMPING_FOWARD, enemy_IDLE, enemy_TRAPPED_1, enemy_TRAPPED_2, enemy_ATTACKING, enemy_FALLING, enemy_DYING, enemy_INBALL_IDLE, enemy_INBALL_MOVING, enemy_INBALL_PUSHING, enemy_INBALL_FALLING, enemy_INBALL_DESTRUCTION};				// algunos montruos no atacan

class Obj_Graf_Enemy :
	public Obj_Graf
{
public:
	Obj_Graf_Enemy();
	Obj_Graf_Enemy(double ID, ENEMY_TYPE type);		// luego tengo que ver como arreglo que me entrenen con un ENEMY_TYPE
	~Obj_Graf_Enemy();

	void draw();
	void startDraw(Direction dir, void *estado, POINT_& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	ENEMY_TYPE type;
	ENEMY_STATE state;
	unsigned int vel_x_inball;
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	unsigned int idleActualImage;
	unsigned int walkActualImage;
	unsigned int actualImageInball;
	void loadBitmap(ENEMY_TYPE type);										// dependiendo del enemigo se le cargan determinadas imagenes
	ALLEGRO_BITMAP ** walkImages = NULL;
	ALLEGRO_BITMAP ** jumpImages = NULL;
	ALLEGRO_BITMAP ** idleImages = NULL;
	ALLEGRO_BITMAP ** attackImages = NULL;
	ALLEGRO_BITMAP ** fallImages = NULL;
	ALLEGRO_BITMAP ** trap1Images = NULL;
	ALLEGRO_BITMAP ** trap2Images = NULL;
	ALLEGRO_BITMAP ** dieImages = NULL;
																// estas son la imagenes de la bola
	ALLEGRO_BITMAP ** inballIdleImages = NULL;
	ALLEGRO_BITMAP ** inballMoveImages = NULL;
	ALLEGRO_BITMAP ** inballPushImages = NULL;
	ALLEGRO_BITMAP ** inballFallImages = NULL;
	ALLEGRO_BITMAP ** inballDestructiontImages = NULL;
	unsigned int actualDestructionImage;
};

