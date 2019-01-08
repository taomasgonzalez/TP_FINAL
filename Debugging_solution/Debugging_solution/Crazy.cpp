#include "Crazy.h"

double Crazy::moving_speed = 300;

Crazy::Crazy(unsigned int id):Enemy(id)
{
	printable = 'C';
}

Crazy::~Crazy()
{
}