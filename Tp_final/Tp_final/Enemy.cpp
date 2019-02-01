#include "Enemy.h"



Enemy::Enemy(unsigned  int id) : Character(id)
{
}


Enemy::~Enemy()
{
}

bool Enemy::is_enemy() {
	return true;
}