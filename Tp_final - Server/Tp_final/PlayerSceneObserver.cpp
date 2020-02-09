#include "PlayerSceneObserver.h"



PlayerSceneObserver::PlayerSceneObserver(Player* player, Scene* scene): CharacterSceneObserver(scene, player)
{
}


PlayerSceneObserver::~PlayerSceneObserver()
{
}

void PlayerSceneObserver::update()
{
	if (!scenario->avoid_character_scene_obs)
		CharacterSceneObserver::update();

	if (scenario->should_tom_die)
		if (character->get_printable() == Item_type::TOM)
			kill_character();

	if (scenario->should_nick_die)
		if (character->get_printable() == Item_type::NICK)
			kill_character();
}

void PlayerSceneObserver::perform_movement(Action_info action) {
	bool should_die = false;
	action.my_character = character->get_printable();
	scenario->execute_action(&action, should_die);

	if (should_die) 
		ev_gen->append_new_event(new DIED_EventPackage(), 0);
	
}
