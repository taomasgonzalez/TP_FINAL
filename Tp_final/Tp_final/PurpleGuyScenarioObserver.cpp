#include "PurpleGuyScenarioObserver.h"

PurpleGuyScenarioObserver::PurpleGuyScenarioObserver(PurpleGuy* purple_guy, Scene* scene ): EnemyScenarioObserver(purple_guy, scene)
{
	this->purple_guy = purple_guy;
}


PurpleGuyScenarioObserver::~PurpleGuyScenarioObserver()
{

}

void PurpleGuyScenarioObserver::update()
{
	EnemyScenarioObserver::update();

	if (purple_guy->purple_questions_4_observer.calculate_shortest_distance) 
		purple_guy->set_next_movement_2_nearest_player(scene->shortest_movement_2_nearest_player(purple_guy));
	
}
