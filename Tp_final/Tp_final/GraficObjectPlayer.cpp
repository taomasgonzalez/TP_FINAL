#include "GraficObjectPlayer.h"
#include <iostream>

using namespace std;



Obj_Graf_Player::Obj_Graf_Player(double ID, PLAYER_TYPE type, ImageContainer* container) : Obj_Graf(ID)
{
	this->velX = VELOCITY_X;					// se setea la velocidad de desplazamiento de los jugadores
	this->type = type;
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->idleActualImage = 0;
	this->dieActualImage = 0;
	this->walkActualImage = 0;

	if (PLAYER_TYPE::NICK)
		images = &container->my_character_images_container.nick;
	else if(PLAYER_TYPE::TOM)
		images = &container->my_character_images_container.tom;
}


Obj_Graf_Player::~Obj_Graf_Player()
{
	
}

void Obj_Graf_Player::draw()
{
	switch (this->dir)														// segun la direccion voy a espejar o no
	{
	case Direction::Left:
	{
		switch (this->state)
		{
		case player_WALKING:
			if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->walkImages[this->walkActualImage/2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			((this->walkActualImage + 1) < 2*WALKING_PICS) ? this->walkActualImage++ : this->walkActualImage = 0;									// me ubico en el siguiente frame o se reinicia la secuancia
			break;
		case player_JUMPING:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2*BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1))? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			break;
		case player_ATTACKING:
			if ((this->attackActualImage + 1) < 2*ATTACKING_PICS)
			{
				//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				this->attackActualImage++;																									// termino la secuencia de disparo
			}
			else
			{
				this->secuenceOver_ = true;
				this->attackActualImage = 0;
				//this->state = player_IDLE;
//				this->active = false;
			}
			al_draw_scaled_bitmap(images->attackImages[this->attackActualImage/2], 0, 0, al_get_bitmap_height(images->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(images->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			break;
		case player_FALLING:
			if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (FALLING_PICS - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			break;
		case player_IDLE:
			this->actualImage = 0;
//			this->active = false;																										// por la dudas lo vuelvo a pasivar porque en la secuencia de caida no se desactiva por si solo
			al_draw_scaled_bitmap(images->idleImages[this->idleActualImage / 2], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage / 2]), al_get_bitmap_width(images->idleImages[this->idleActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			//al_draw_bitmap(images->idleImages[idleActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
			((this->idleActualImage + 1) < 2*IDLE_PICS) ? this->idleActualImage++ : this->idleActualImage = 0;
			break;
		case player_JUMPING_FOWARD:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}

			if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
			}
			else
				this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX)/2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
			al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
			break;																				// misma distancia en el doble de tiempo
		case player_PUSHING:
			if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
			{
				this->secuenceOver_ = true;
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				//this->active = false;
				al_draw_scaled_bitmap(images->pushImages[this->actualImage], 0, 0, al_get_bitmap_height(images->pushImages[this->actualImage]), al_get_bitmap_width(images->pushImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_scaled_bitmap(images->pushImages[this->actualImage], 0, 0, al_get_bitmap_height(images->pushImages[this->actualImage]), al_get_bitmap_width(images->pushImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED);
				((this->actualImage + 1) < PUSHING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case player_DYING:
			if (this->dieActualImage < 2*DYING_PICS)
			{
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage/2], 0, 0, al_get_bitmap_width(images->dieImages[this->dieActualImage / 2]), al_get_bitmap_height(images->dieImages[this->dieActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->dieActualImage++;
			}
			else
			{
				this->secuenceOver_ = true;
				this->dieActualImage = 0;
//				this->active = false;			// aca si se podria desactivar el objeto
			}
			break;
		}
	}
	break;

	case Direction::Right:
		switch (this->state)
		{
		case player_WALKING:
			if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la derecha, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
//				this->isActive = false;															// se pasiva el objeto
				//this->state = player_IDLE;
				this->actualImage = 0;
			}
			else
			{
				//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			((this->walkActualImage + 1) < 2*WALKING_PICS) ? this->walkActualImage++ : this->walkActualImage = 0;
			break;
		case player_JUMPING:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			break;
		case player_ATTACKING:
			if ((this->attackActualImage + 1) < 2*ATTACKING_PICS)
			{
				//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				this->attackActualImage++;																							// termino la secuencia de disparo
			}
			else
			{
				this->secuenceOver_ = true;
				this->attackActualImage = 0;
				//this->state = player_IDLE;
//				this->Active = false;
			}
			al_draw_scaled_bitmap(images->attackImages[this->attackActualImage/2], 0, 0, al_get_bitmap_height(images->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(images->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			break;
		case player_FALLING:
			if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (FALLING_PICS - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
			}
			al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			break;
		case player_IDLE:
			this->actualImage = 0;
//			this->active = false;
			al_draw_scaled_bitmap(images->idleImages[this->idleActualImage/2], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage / 2]), al_get_bitmap_width(images->idleImages[this->idleActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
			((this->idleActualImage + 1) < 2*IDLE_PICS) ? this->idleActualImage++ : this->idleActualImage = 0;
			break;
		case player_JUMPING_FOWARD:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->secuenceOver_ = true;
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				//this->state = player_IDLE;
			}
			else
			{
				//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}

			if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
			}
			else
				this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
			al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			break;
		case player_PUSHING:
			if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))
			{
				this->secuenceOver_ = true;
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
				//this->active = false;
				//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			}
			else
			{
				//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED);
				((this->actualImage + 1) < PUSHING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			al_draw_scaled_bitmap(images->pushImages[this->actualImage], 0, 0, al_get_bitmap_height(images->pushImages[this->actualImage]), al_get_bitmap_width(images->pushImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
			break;
		case player_DYING:
			if (this->dieActualImage < 2*DYING_PICS)
			{
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage/2], 0, 0, al_get_bitmap_width(images->dieImages[this->dieActualImage / 2]), al_get_bitmap_height(images->dieImages[this->dieActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->dieActualImage++;
			}
			else
			{
				this->secuenceOver_ = true;
				this->dieActualImage = 0;
//				this->active = false;			// aca si se podria desactivar el objeto
			}
			break;
		}
	}
}

void Obj_Graf_Player::startDraw(Direction dir, void *state, POINT_& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos = pos;
	this->InitalPos = pos;
	this->state = * (PLAYER_STATE *)state;
	this->actualImage = 0;								// comienza con la primera imagen
	this->secuenceOver_ = false;
}

void Obj_Graf_Player::destroy()
{
}

void Obj_Graf_Player::reset()
{
	this->attackActualImage = 0;
	this->dieActualImage = 0;
	this->idleActualImage = 0;
	this->walkActualImage = 0;
}

bool Obj_Graf_Player::secuenceOver()
{
	return this->secuenceOver_;
}
