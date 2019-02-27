#include "Character.h"
#include "CharacterActionsFSMDRAWObserver.h"
#include "CharacterActionsEventGenerator.h"
#include "DRAW.h"

Character::Character(unsigned int id, Sense_type sense) : MapThing(id, false, sense)
{
	CharacterActionsFSM* fsm = new CharacterActionsFSM();
	fsm->add_observer(new CharacterActionsFSMDRAWObserver(fsm));
	character_handler = new EventHandler(fsm, new CharacterActionsEventGenerator());
}


Character::~Character()
{
	delete character_handler;
}

void Character::die()
{
	dead = true;
}

bool Character::is_dead()
{
	return dead;
}



