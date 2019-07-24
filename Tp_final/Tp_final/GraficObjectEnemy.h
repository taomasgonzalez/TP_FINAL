#pragma once
#include "GraficObject.h"

enum ENEMY_TYPE {PURPLE, FATTY, CRAZY};

enum ENEMY_STATE { enemy_WALKING, enemy_JUMPING, enemy_JUMPING_FOWARD, enemy_IDLE, enemy_TRAPPED_1, enemy_TRAPPED_2, enemy_ATTACKING, enemy_FALLING, enemy_DYING, enemy_INBALL_IDLE, enemy_INBALL_MOVING, enemy_INBALL_PUSHING, enemy_INBALL_FALLING, enemy_INBALL_DESTRUCTION};				// algunos montruos no atacan

class Obj_Graf_Enemy :
	public Obj_Graf
{
public:
	Obj_Graf_Enemy();
	Obj_Graf_Enemy(double ID, ENEMY_TYPE type, ImageContainer* container);		// luego tengo que ver como arreglo que me entrenen con un ENEMY_TYPE
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

	unsigned int actualDestructionImage;

	ImageContainer::enemy_images * images;
};

