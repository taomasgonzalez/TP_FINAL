#include "Snowball.h"

double Snowball::moving_speed = 300;
int Snowball::life_of_use = 3;

Snowball::Snowball(unsigned int id, Sense_type proyectile_sense): Proyectile(id, proyectile_sense)
{
	printable = Item_type::SNOWBALL;
}


Snowball::~Snowball()
{
}
