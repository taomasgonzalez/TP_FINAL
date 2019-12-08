#include "GraficObject.h"

Obj_Graf::Obj_Graf()
{

}

Obj_Graf::Obj_Graf(double ID)
{
	this->ID = ID;
	this->velFall = VEL_FALL;
	this->secuenceOver_ = false;
//	this->InitalPos = InitialPos;
}

Obj_Graf::~Obj_Graf()
{}

void Obj_Graf::setID(double ID)
{
	this->ID = ID;
}

void Obj_Graf::setPos(POINT_ p)
{
	this->pos = p;
}

void Obj_Graf::setPos(double x, double y)
{
	POINT_ p(x, y);
	this->pos = p;
}

void Obj_Graf::setInitalPos(POINT_ pos)
{
	this->InitalPos = pos;
}

bool Obj_Graf::isActive()
{
	return this->active;
}

void Obj_Graf::activeObj()
{
	this->active = true;
}

void Obj_Graf::disactiveObj()
{
	this->active = false;
}

bool Obj_Graf::finished_drawing_step() {
	return finished_step;
}


void Obj_Graf::notify_finished_drawing_step() {
	finished_step = true;
	notify_obs();
	finished_step = false;
}