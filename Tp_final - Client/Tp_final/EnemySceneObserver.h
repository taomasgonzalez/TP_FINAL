#pragma once
#include "Observer.h"
#include "Scene.h"
#include "Enemy.h"
#include "CharacterSceneObserver.h"
#include "EnemyActionsFSM.h"

class EnemySceneObserver : public CharacterSceneObserver
{
public:
	EnemySceneObserver(Enemy* enemy, Scene* scene);
	~EnemySceneObserver();

	void update();
	virtual void perform_movement(Action_info action);

protected:
	Scene * scene;
private:
	ALLEGRO_EVENT_QUEUE* freezing_queue = 0;	//will get events from the timers of the enemies
	ALLEGRO_EVENT_QUEUE* froze_queue = 0;
	Enemy * enemy;
	EnemyActionsFSM* fsm = NULL;
};

