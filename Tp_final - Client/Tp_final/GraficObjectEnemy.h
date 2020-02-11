#pragma once
#include "GraficObjectCharacter.h"

enum ENEMY_TYPE { PURPLE, FATTY, CRAZY };

enum ENEMY_STATE { enemy_WALKING, enemy_JUMPING, enemy_JUMPING_FOWARD, enemy_IDLE, enemy_TRAPPED_1, enemy_TRAPPED_2, enemy_TRAPPED_3, enemy_ATTACKING, enemy_FALLING, enemy_DYING, enemy_INBALL_IDLE, enemy_INBALL_MOVING, enemy_INBALL_PUSHING, enemy_INBALL_FALLING, enemy_INBALL_DESTRUCTION };				// algunos montruos no atacan

class Obj_Graf_Enemy : public Obj_Graf_Character
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
	float vel_x_inball;
	unsigned int trap1ActualImage;
	unsigned int trap2ActualImage;
	unsigned int trap3ActualImage;
	unsigned int trap1ticks;
	unsigned int trap2ticks;
	unsigned int trap3ticks;
	unsigned int actualImageInball_idle;
	unsigned int actualImageInball_moving;
	unsigned int actualDestructionImage;


	void handle_trapped(ENEMY_TYPE, ENEMY_STATE trapped_state);			//ENEMY_STATE : enemy_TRAPPED_1 or enemy_TRAPPED_2
	void handle_inball_iddle();						//INBALL pics are common to all enemies
	void handle_inball_moving();
	void handle_inball_pushing();
	void handle_inball_falling();
	void handle_inball_destruction();

	void going_right();

	ImageContainer::enemy_images * this_images = NULL;
};