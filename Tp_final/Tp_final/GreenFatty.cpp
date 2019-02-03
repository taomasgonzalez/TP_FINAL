#include "GreenFatty.h"

double GreenFatty::moving_speed = 200;

GreenFatty::GreenFatty(unsigned int id) : Enemy(id)
{
	printable = Item_type::GREEN_FATTIE;
}


GreenFatty::~GreenFatty()
{
}
