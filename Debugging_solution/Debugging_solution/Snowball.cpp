#include "Snowball.h"

double Snowball::moving_speed = 300;
int Snowball::life_of_use = 3;

Snowball::Snowball(unsigned int id):Proyectile(id)
{
	printable = 'S';
}

Snowball::~Snowball()
{
}
