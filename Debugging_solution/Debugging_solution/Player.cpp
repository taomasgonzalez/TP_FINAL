#include "Player.h"

//agrégo un bool para saber, desde scene que tiene el dato si es tom o nick

Player::Player(unsigned int id,bool is_nick, Sense_type sense) :Character(id, sense)
{
	if (is_nick)
		printable = Item_type::NICK;
	else
		printable = Item_type::TOM;
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
	if (lives > 0)
		lives--;
	
}

