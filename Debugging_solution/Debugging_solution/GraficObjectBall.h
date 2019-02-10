#pragma once
#include "GraficObject.h"

enum BALL_STATE {ball_IDLE, ball_MOVING, ball_PUSHING, ball_FALLING, ball_DESTRUCTION};	// ball_PUSHING -> cuando la empuja un character

enum BALL_TYPE {BALL};

class Obj_Graf_Ball :
	public Obj_Graf
{
public:
	Obj_Graf_Ball();
	Obj_Graf_Ball(double ID, BALL_TYPE);
	~Obj_Graf_Ball();

	void draw();
	void startDraw(Direction dir, void *state, POINT& pos);
	void destroy();
	void reset();
	bool secuenceOver();

private:
	void loadBitmap();
	BALL_STATE state;
	ALLEGRO_BITMAP ** idleImages = NULL;
	ALLEGRO_BITMAP ** moveImages = NULL;
	ALLEGRO_BITMAP ** pushImages = NULL;
	ALLEGRO_BITMAP ** fallImages = NULL;
	ALLEGRO_BITMAP ** destructiontImages = NULL;
	unsigned int actualDestructionImage;
};

