#include "point.h"

POINT_::POINT_(float x, float y)
{
	this->x = x;
	this->y = y;
}

POINT_::POINT_()
{
	this->x = 0;
	this->y = 0;
}

POINT_::~POINT_()
{
}

float
POINT_::get_x_coord()
{
	return x;
}

float
POINT_::get_y_coord()
{
	return y;
}

void
POINT_::set_x_coord(float x)
{
	this->x = x;
}

void
POINT_::set_y_coord(float y)
{
	this->y = y;
}