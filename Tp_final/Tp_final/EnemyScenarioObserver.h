#pragma once
#include "Observer.h"
#include "Scene.h"
#include "Enemy.h"

class EnemyScenarioObserver : public Observer
{
public:
	EnemyScenarioObserver(Enemy* enemy, Scene* scene);
	~EnemyScenarioObserver();

	void update();

protected:
	Scene * scene;
private:
	Enemy * enemy;
};

