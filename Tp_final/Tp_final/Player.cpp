#include "Player.h"



Player::Player(unsigned int id) :Character(id)
{
	printable = 'N';
}


Player::~Player()
{
}

bool Player::is_player() {
	return true;
}
void Player::revive() {
	if(lives > 0)
		dead = false;
}
void Player::die()
{
	lose_life();
	dead = true;
}
void Player::lose_life()
{
	if(lives > 0)
		lives--;
}

