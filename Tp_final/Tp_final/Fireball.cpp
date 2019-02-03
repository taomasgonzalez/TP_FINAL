#include "Fireball.h"

double Fireball::moving_speed = 300;
int Fireball::life_of_use = 3; //in number of squares visited.

Fireball::Fireball(unsigned int id): Proyectile(id)
{
	printable = Item_type::FIREBALL;

}


Fireball::~Fireball()
{
}
