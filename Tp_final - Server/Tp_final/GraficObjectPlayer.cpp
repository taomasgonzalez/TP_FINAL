#include "GraficObjectPlayer.h"
#include <iostream>
#include "PlayerActionsFSMDRAWObserver.h"

using namespace std;



Obj_Graf_Player::Obj_Graf_Player(double ID, PLAYER_TYPE type, ImageContainer* container) : Obj_Graf(ID)
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
		images = &container->my_character_images_container.nick;
		break;
	case TOM:
		images = &container->my_character_images_container.tom;
		break;
	}
}


Obj_Graf_Player::~Obj_Graf_Player()
{
	
}

void Obj_Graf_Player::draw()
{
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
			handle_iddle();
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

void Obj_Graf_Player::startDraw(Direction dir, void *state, POINT_& pos)
{
	active = true;
	this->dir = dir;
	this->pos = pos;
	InitalPos = pos;
	this->state = * (PLAYER_STATE *)state;
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


void Obj_Graf_Player::handle_walking() {

	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	if (reached_final_pos)		//veo si ya llego a la pos final 
	{
		if(!secuenceOver_)
			notify_finished_drawing_step();
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta* BLOCK_SIZE);
		actualImage = 0;
	}
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX);		// muevo la posicion del dibujo

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->walkImages[walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[walkActualImage / 2]), al_get_bitmap_width(images->walkImages[walkActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((walkActualImage + 1) < 2 * WALKING_PICS) ? walkActualImage++ : walkActualImage = 0;	// me ubico en el siguiente frame o se reinicia la secuancia
}
void Obj_Graf_Player::handle_jumping() {
	if (pos.get_y_coord() <= (InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		if (!secuenceOver_) {
			secuenceOver_ = true;
			notify_finished_drawing_step();
			notified_half_jump = false;
			pos.set_y_coord(InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
			actualImage = 0;
		}
	}
	else
	{
		(actualImage < (JUMPING_PICS - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
		if (!notified_half_jump && pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE)) {
			notify_finished_drawing_step();
			notified_half_jump = true;
		}
	}
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[actualImage]), al_get_bitmap_width(images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}
void Obj_Graf_Player::handle_jumping_forward() {

	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (pos.get_y_coord() < (InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		if (!secuenceOver_) {
			secuenceOver_ = true;
			notify_finished_drawing_step();
			notified_half_jump = false;
			pos.set_y_coord(InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
			actualImage = 0;
		}
	}
	else
	{
		(actualImage < (JUMPING_PICS - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
		if (!notified_half_jump && pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE)) {
			notify_finished_drawing_step();
			notified_half_jump = true;
		}
	}

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);


	if (reached_final_pos)
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX / 2);	// muevo la posicion del dibujo

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[actualImage]), al_get_bitmap_width(images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}
void Obj_Graf_Player::handle_iddle() {
	actualImage = 0;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->idleImages[idleActualImage / 2], 0, 0, al_get_bitmap_height(images->idleImages[idleActualImage / 2]), al_get_bitmap_width(images->idleImages[idleActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((idleActualImage + 1) < 2 * IDLE_PICS) ? idleActualImage++ : idleActualImage = 0;
}
void Obj_Graf_Player::handle_attacking() {
	if ((this->attackActualImage + 1) < 2 * ATTACKING_PICS)
		this->attackActualImage++;																									// termino la secuencia de disparo
	else
	{
		this->secuenceOver_ = true;
		this->attackActualImage = 0;
	}
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(images->attackImages[attackActualImage / 2], 0, 0, al_get_bitmap_height(images->attackImages[attackActualImage / 2]), al_get_bitmap_width(images->attackImages[attackActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}
void Obj_Graf_Player::handle_falling() {
	if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		if (!secuenceOver_) {
			notify_finished_drawing_step();
			secuenceOver_ = true;
			pos.set_y_coord(InitalPos.get_y_coord() + BLOCK_SIZE);
			actualImage = 0;
		}
	}
	else
	{
		(actualImage < (FALLING_PICS - 1)) ? actualImage++ : actualImage = 0;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() + velFall);															// muevo la posicion del dibujo
	}
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->fallImages[actualImage], 0, 0, al_get_bitmap_height(images->fallImages[actualImage]), al_get_bitmap_width(images->fallImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}
void Obj_Graf_Player::handle_pushing() {

	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() < (InitalPos.get_x_coord() + delta* BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	if (reached_final_pos)						// BLOCK_SIZE / 2 para que no atraviese el piso
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
		al_draw_scaled_bitmap(images->pushImages[actualImage], 0, 0, al_get_bitmap_height(images->pushImages[actualImage]), al_get_bitmap_width(images->pushImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	}
	else
	{
		al_draw_scaled_bitmap(images->pushImages[actualImage], 0, 0, al_get_bitmap_height(images->pushImages[actualImage]), al_get_bitmap_width(images->pushImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		pos.set_x_coord(pos.get_x_coord() + delta * VEL_PUSHED);
		((actualImage + 1) < PUSHING_PICS) ? actualImage++ : actualImage = 0;
	}
}
void Obj_Graf_Player::handle_dying() {
	if (this->dieActualImage < 2 * DYING_PICS)
	{
		int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		al_draw_scaled_bitmap(images->dieImages[dieActualImage / 2], 0, 0, al_get_bitmap_width(images->dieImages[dieActualImage / 2]), al_get_bitmap_height(images->dieImages[dieActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		dieActualImage++;
	}
	else
	{
		if (!secuenceOver_)
			notify_finished_drawing_step();
		secuenceOver_ = true;
		dieActualImage = 0;
	}
}
int Obj_Graf_Player::get_movement_delta() {
	int delta = 0;			//for quickly detecting errors (the enemy will not move).

	if (dir == Direction::Left)
		delta = -1;
	else if (dir == Direction::Right)
		delta = 1;

	return delta;
}