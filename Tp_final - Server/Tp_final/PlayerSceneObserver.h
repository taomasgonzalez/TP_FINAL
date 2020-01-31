#pragma once
#include "CharacterSceneObserver.h"

class PlayerSceneObserver : public CharacterSceneObserver
{
public:
	PlayerSceneObserver(Player* player, Scene * scene);
	~PlayerSceneObserver();

	void perform_movement(Action_info action);

private:

};

