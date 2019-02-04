#include "Enemy.h"


std::uniform_real_distribution<double> Enemy::acting_probabilities = std::uniform_real_distribution<double>(0.0, 1.0);
unsigned Enemy::seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Enemy::generator = std::default_random_engine(seed);

Enemy::Enemy(unsigned  int id) : Character(id)
{
	acting_timer = al_create_timer(1.0);
}


Enemy::~Enemy()
{
	al_destroy_timer(acting_timer);
}

bool Enemy::is_enemy() {
	return true;
}

ALLEGRO_TIMER * Enemy::get_acting_timer() {
	return this->acting_timer;
}