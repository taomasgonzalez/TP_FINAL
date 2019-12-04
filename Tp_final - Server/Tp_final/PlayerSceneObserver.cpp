#include "PlayerSceneObserver.h"



PlayerSceneObserver::PlayerSceneObserver(Player* player, Scene* scene): CharacterSceneObserver(scene, player)
{
}


PlayerSceneObserver::~PlayerSceneObserver()
{
}
void PlayerSceneObserver::perform_movement(Action_info action) {
	bool should_die = false;
	scenario->execute_action(&action, should_die);
	if (should_die)
		ev_gen->append_new_event(new DIED_EventPackage(), 0);
}