#pragma once
#include "GraficObjectCharacter.h"


enum PLAYER_TYPE { TOM, NICK };

enum PLAYER_STATE { player_WALKING, player_JUMPING, player_JUMPING_FOWARD, player_IDLE, player_ATTACKING, player_FALLING , player_PUSHING, player_DYING};


class Obj_Graf_Player : public Obj_Graf_Character
{
public:
	Obj_Graf_Player(double ID, PLAYER_TYPE type, ImageContainer* imageContainer, AudioContainer* audioContainer);		// se setea la velorcidad del player
	~Obj_Graf_Player();

	void draw();
	void startDraw(Direction dir, void *estado, POINT_& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	PLAYER_STATE state;
	PLAYER_TYPE type;

	void handle_pushing();
};