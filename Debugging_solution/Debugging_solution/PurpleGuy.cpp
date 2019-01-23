#include "PurpleGuy.h"

double PurpleGuy::moving_speed = 300;

PurpleGuy::PurpleGuy(unsigned int id): Enemy(id)
{
	printable = 'P';
}


PurpleGuy::~PurpleGuy()
{
}
