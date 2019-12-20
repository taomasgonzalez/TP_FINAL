#include "Player.h"
#include "PlayerActionsFSM.h"
#include "PlayerActionsFSMDRAWObserver.h"
#include "CharacterSceneObserver.h"
#include "EventGenerator.h"

//agrégo un bool para saber, desde scene que tiene el dato si es tom o nick

Player::Player(unsigned int id,bool is_nick, Sense_type sense) :Character(id, sense)
{
	if (is_nick)
		printable = Item_type::NICK;
	else
		printable = Item_type::TOM;

	PlayerActionsFSM* fsm = new PlayerActionsFSM(this);
	#pragma message("falta completar constructor con parametros!!")
	EventGenerator* ev_gen = new EventGenerator();
	fsm->add_observer(new PlayerActionsFSMDRAWObserver(fsm, ev_gen, this));
	
	ev_handler = new EventHandler(fsm, ev_gen);
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


void add_observer_to_fsm(Observer* observer) {

}
