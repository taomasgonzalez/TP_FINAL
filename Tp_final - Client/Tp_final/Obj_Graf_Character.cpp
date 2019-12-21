#include "Obj_Graf_Character.h"



Obj_Graf_Character::Obj_Graf_Character() : Obj_Graf(ID)
{
	walking_pics = 0;								//This variables must be inited with their respective value
	jumping_pics = 0;								//on the derived class
	jumping_forw_pics = 0;
	iddle_pics = 0;
	attacking_pics = 0;
	falling_pics = 0;
	dying_pics = 0;

	is_fatty = false;
}


Obj_Graf_Character::~Obj_Graf_Character()
{
}

void Obj_Graf_Character::handle_walking()
{
	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	if (reached_final_pos)		//veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
		actualImage = 0;
	}
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX);		// muevo la posicion del dibujo

	int flip;
	if(is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->walkImages[walkActualImage / 2], 0, 0, al_get_bitmap_height(chara_images->walkImages[walkActualImage / 2]), al_get_bitmap_width(chara_images->walkImages[walkActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((walkActualImage + 1) < 2 * walking_pics) ? walkActualImage++ : walkActualImage = 0;	// me ubico en el siguiente frame o se reinicia la secuancia
}

void Obj_Graf_Character::handle_jumping()
{
	if (pos.get_y_coord() < (InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		half_way_jumped_ = false;			//NUEVO
		secuenceOver_ = true;
		pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
		actualImage = 0;
	}
	else
	{
		half_way_jumped_ = (pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE)) ? true : false;			//NUEVO
		(actualImage < (jumping_pics - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
	}

	int flip;
	if (is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(chara_images->jumpImages[actualImage]), al_get_bitmap_width(chara_images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}

void Obj_Graf_Character::handle_jumping_forward()
{
	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (pos.get_y_coord() < (InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		half_way_jumped_ = false;			//NUEVO
		pos.set_y_coord(InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
		actualImage = 0;
	}
	else
	{
		half_way_jumped_ = (pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE)) ? true : false;			//NUEVO
		(actualImage < (jumping_forw_pics - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
	}

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);


	if (reached_final_pos)
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX / 2);	// muevo la posicion del dibujo

	int flip;
	if (is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(chara_images->jumpImages[actualImage]), al_get_bitmap_width(chara_images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Character::handle_iddle()
{
	actualImage = 0;

	int flip;
	if (is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->idleImages[idleActualImage / 2], 0, 0, al_get_bitmap_height(chara_images->idleImages[idleActualImage / 2]), al_get_bitmap_width(chara_images->idleImages[idleActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((idleActualImage + 1) < 2 * iddle_pics) ? idleActualImage++ : idleActualImage = 0;
}

void Obj_Graf_Character::handle_attacking()
{
	if ((this->attackActualImage + 1) < 2 * attacking_pics)
		this->attackActualImage++;																									// termino la secuencia de disparo
	else
	{
		this->secuenceOver_ = true;
		this->attackActualImage = 0;
	}

	int flip;
	if (is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->attackImages[attackActualImage / 2], 0, 0, al_get_bitmap_height(chara_images->attackImages[attackActualImage / 2]), al_get_bitmap_width(chara_images->attackImages[attackActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Character::handle_falling()
{
	if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		this->secuenceOver_ = true;
		this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
		this->actualImage = 0;
	}
	else
	{
		(this->actualImage < (falling_pics- 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
		this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
	}

	int flip;
	if (is_fatty)
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	else
		flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(chara_images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(chara_images->fallImages[this->actualImage]), al_get_bitmap_width(chara_images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}

void Obj_Graf_Character::handle_dying()
{
	if (this->dieActualImage < 2 * dying_pics)
	{

		int flip;
		if (is_fatty)
			flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		else
			flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		al_draw_scaled_bitmap(chara_images->dieImages[dieActualImage / 2], 0, 0, al_get_bitmap_width(chara_images->dieImages[dieActualImage / 2]), al_get_bitmap_height(chara_images->dieImages[dieActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		dieActualImage++;
	}
	else
	{
		secuenceOver_ = true;
		dieActualImage = 0;
	}
}

int Obj_Graf_Character::get_movement_delta()
{
	int delta = 0;			//for quickly detecting errors (the enemy will not move).

	if (dir == Direction::Left)
		delta = -1;
	else if (dir == Direction::Right)
		delta = 1;

	return delta;
}
