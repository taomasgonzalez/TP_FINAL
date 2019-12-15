#pragma once
#include "GraficObject.h"


enum PLAYER_TYPE { TOM, NICK };

enum PLAYER_STATE { player_WALKING, player_JUMPING, player_JUMPING_FOWARD, player_IDLE, player_ATTACKING, player_FALLING , player_PUSHING, player_DYING};


class Obj_Graf_Player : public Obj_Graf
{
public:
	Obj_Graf_Player(double ID, PLAYER_TYPE type, ImageContainer* container);		// se setea la velorcidad del player
	~Obj_Graf_Player();

	void draw();
	void startDraw(Direction dir, void *estado, POINT_& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	PLAYER_STATE state;
	PLAYER_TYPE type;
	unsigned int idleActualImage;
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	unsigned int walkActualImage;

	void handle_walking();
	void handle_jumping();
	void handle_jumping_forward();
	void handle_iddle();
	void handle_attacking();
	void handle_falling();
	void handle_pushing();
	void handle_dying();

	int get_movement_delta();

	ImageContainer::character_images * images = NULL;
};