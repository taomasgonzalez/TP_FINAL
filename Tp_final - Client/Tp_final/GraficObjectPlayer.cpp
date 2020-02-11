#include "GraficObjectPlayer.h"
#include <iostream>
#include "PlayerActionsFSMDRAWObserver.h"

#define FPS_4_INMUNITY_TOGGLE (4)

using namespace std;

Obj_Graf_Player::Obj_Graf_Player(double ID, PLAYER_TYPE type, ImageContainer* container)
{
	velX = VELOCITY_X;					// se setea la velocidad de desplazamiento de los jugadores
	this->type = type;
	actualImage = 0;
	attackActualImage = 0;
	idleActualImage = 0;
	dieActualImage = 0;
	walkActualImage = 0;

	switch (type)
	{
	case NICK:
		chara_images = &container->my_character_images_container.nick;
		break;
	case TOM:
		chara_images = &container->my_character_images_container.tom;
		break;
	}

	walking_pics = WALKING_PICS;
	jumping_pics = JUMPING_PICS;
	jumping_forw_pics = JUMPING_PICS;
	idle_pics = IDLE_PICS;
	attacking_pics = ATTACKING_PICS;
	falling_pics = FALLING_PICS;
	dying_pics = DYING_PICS;
}


Obj_Graf_Player::~Obj_Graf_Player()
{

}

void Obj_Graf_Player::draw()
{
	if (!must_not_draw_player()) {
		switch (this->state)
		{
		case player_WALKING:
			handle_walking();
			break;
		case player_JUMPING:
			handle_jumping();
			break;
		case player_ATTACKING:
			handle_attacking();
			break;
		case player_FALLING:
			handle_falling();
			break;
		case player_IDLE:
			handle_idle();
			//std::cout << "Se imprimió un iddle de un jugador" << std::endl;

			break;
		case player_JUMPING_FOWARD:
			handle_jumping_forward();
			break;
		case player_PUSHING:
			handle_pushing();
			break;
		case player_DYING:
			handle_dying();
			break;
		}
	}
}

void Obj_Graf_Player::startDraw(Direction dir, void *state, POINT_& pos)
{
	active = true;
	this->dir = dir;
	this->pos = pos;
	InitalPos = pos;

	if (*(PLAYER_STATE *)state == PLAYER_STATE::player_RESPAWN)
		set_inmunity(true);

	else if (*(PLAYER_STATE *)state == PLAYER_STATE::player_STOP_INMUNITY)
		set_inmunity(false);

	else
		this->state = *(PLAYER_STATE *)state;

	actualImage = 0;								// comienza con la primera imagen
	secuenceOver_ = false;
	notified_half_jump = false;
}

void Obj_Graf_Player::destroy()
{
}

void Obj_Graf_Player::reset()
{
	attackActualImage = 0;
	dieActualImage = 0;
	idleActualImage = 0;
	walkActualImage = 0;
}

bool Obj_Graf_Player::secuenceOver()
{
	return secuenceOver_;
}

void Obj_Graf_Player::set_inmunity(bool inmunity)
{
	has_inmunity = inmunity;
}


bool Obj_Graf_Player::must_not_draw_player()
{
	bool ret = false;
	if (this->has_inmunity) {
		if (toggle_sprites < FPS_4_INMUNITY_TOGGLE)
			ret = true;
		toggle_sprites++;
		toggle_sprites %= 2 * FPS_4_INMUNITY_TOGGLE;
	}
	return ret;
}

void Obj_Graf_Player::handle_pushing() {

	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() < (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	if (reached_final_pos)						// BLOCK_SIZE / 2 para que no atraviese el piso
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
		al_draw_scaled_bitmap(chara_images->pushImages[actualImage], 0, 0, al_get_bitmap_height(chara_images->pushImages[actualImage]), al_get_bitmap_width(chara_images->pushImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	}
	else
	{
		al_draw_scaled_bitmap(chara_images->pushImages[actualImage], 0, 0, al_get_bitmap_height(chara_images->pushImages[actualImage]), al_get_bitmap_width(chara_images->pushImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		pos.set_x_coord(pos.get_x_coord() + delta * VEL_PUSHED);
		((actualImage + 1) < PUSHING_PICS) ? actualImage++ : actualImage = 0;
	}
}