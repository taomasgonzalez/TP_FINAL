#include "Player.h"
#include "PlayerActionsFSM.h"
#include "PlayerActionsFSMDRAWObserver.h"
#include "CharacterSceneObserver.h"
#include "MapThingEventGenerator.h"

//agr�go un bool para saber, desde scene que tiene el dato si es tom o nick

Player::Player(unsigned int id, bool is_nick, Sense_type sense) :Character(id, sense)
{
	if (is_nick)
		printable = Item_type::NICK;
	else
		printable = Item_type::TOM;

	PlayerActionsFSM* fsm = new PlayerActionsFSM(this);
	MapThingEventGenerator* ev_gen = new MapThingEventGenerator();
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
	if (lives > 0)
	{
		dead = false;
	}
}

bool Player::has_lives() {

	return !run_out_of_lives;
}

bool Player::is_inmune() {

	return being_inmuned;
}

void Player::set_the_player_inmunity(bool is_inmuned) {

	being_inmuned = is_inmuned;
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

	if (printable == Item_type::TOM)
		std::cout << "TOM perdio una vida, le quedan: " << lives << std::endl;
	else
		std::cout << "NICK perdio una vida, le quedan: " << lives << std::endl;

	if (lives == 0)
		run_out_of_lives = true;
	
}


void add_observer_to_fsm(Observer* observer) {

}
