#include "Player.h"


Player::Player(unsigned int id):Character(id)
{
	printable = 'N';
}

Player::~Player()
{
}

bool Player::is_player() {
	return true;
}
