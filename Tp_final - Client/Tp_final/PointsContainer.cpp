#include "PointsContainer.h"

PointsContainer::PointsContainer()
{
	actual_game_points = 0;
}

PointsContainer::~PointsContainer()
{
}

void PointsContainer::reset_game_points(void)
{
	actual_game_points;
}

void PointsContainer::grant_game_points(unsigned int game_points)
{
	actual_game_points += game_points;
}

unsigned int PointsContainer::get_game_points(void)
{
	return actual_game_points;
}
