#include "Player.h"
#include "PlayerActionsFSM.h"
#include "PlayerActionsEventGenerator.h"
#include "PlayerActionsFSMDRAWObserver.h"

//agrégo un bool para saber, desde scene que tiene el dato si es tom o nick
void get_and_set_timers(PlayerActionsEventGenerator* ev_gen, PlayerActionsFSM* fsm);

Player::Player(unsigned int id,bool is_nick, Sense_type sense) :Character(id, sense)
{
	if (is_nick)
		printable = Item_type::NICK;
	else
		printable = Item_type::TOM;

	PlayerActionsFSM* fsm = new PlayerActionsFSM(this);
	#pragma message("falta completar constructor con parametros!!")
	PlayerActionsEventGenerator* ev_gen = new PlayerActionsEventGenerator(fsm->get_all_timers());
	fsm->add_observer(new PlayerActionsFSMDRAWObserver(fsm, ev_gen, this));
	get_and_set_timers(ev_gen, fsm);
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

void get_and_set_timers(PlayerActionsEventGenerator* ev_gen, PlayerActionsFSM* fsm) {

	ev_gen->set_attacking_timer(fsm->get_attacking_timer());
	ev_gen->set_falling_timer(fsm->get_falling_timer());
	ev_gen->set_jumping_forward_timer(fsm->get_jumping_forward_timer());
	ev_gen->set_jumping_timer(fsm->get_jumping_timer());
	ev_gen->set_walking_timer(fsm->get_walking_timer());

	ev_gen->set_pushing_timer(fsm->get_pushing_timer());
}