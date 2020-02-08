#pragma once
class PointsContainer
{
public:
	PointsContainer();
	~PointsContainer();
	void reset_game_points(void);
	void grant_game_points(unsigned int game_points);
	unsigned int get_game_points(void);

private:
	unsigned int actual_game_points;
};

