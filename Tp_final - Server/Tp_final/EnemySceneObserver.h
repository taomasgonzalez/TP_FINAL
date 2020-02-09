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
	Enemy * enemy;
	EnemyActionsFSM* fsm = NULL;
};

