#include "GraficObjectEnemy.h"
#include "EnemyDefines.h"

using namespace std;

Obj_Graf_Enemy::Obj_Graf_Enemy()
{
}

Obj_Graf_Enemy::Obj_Graf_Enemy(double ID, ENEMY_TYPE type) : Obj_Graf(ID)
{
	this->actualImage = 0;
	this->type = type;
	loadBitmap(type);
	this->attackActualImage = 0;
	this->dieActualImage = 0;
	this->idleActualImage = 0;
	this->walkActualImage = 0;

	switch (type)
	{
	case PURPLE:
		this->velX = VEL_PURPLE;
		break;
	case FATTY:
		this->velX = VEL_FATTY;
		break;
	case CRAZY:
		this->velX = VEL_CRAZY;
		break;
	}
}


Obj_Graf_Enemy::~Obj_Graf_Enemy()
{
}

void Obj_Graf_Enemy::draw()
{
	switch (this->type)
	{
	case PURPLE:
		switch (this->dir)														// segun la direccion voy a espejar o no
		{
			case Direction::Left:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_PURPLE) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					al_draw_scaled_bitmap(this->trapImages[this->actualImage], 0, 0, al_get_bitmap_height(this->trapImages[this->actualImage]), al_get_bitmap_width(this->trapImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImage++;
					break;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_PURPLE)
					{
						//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
//					this->active = false;
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->idleActualImage + 1) < IDLE_PICS_PURPLE) ? this->idleActualImage++ : this->idleActualImage = 0;
					//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
					break;
				}
			}
			break;
			case Direction::Right:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la derecha, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						//this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
						//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_PURPLE) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImage++;
					break;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_PURPLE)
					{
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
//					this->active = false;
					//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->idleActualImage + 1) < IDLE_PICS_PURPLE) ? this->idleActualImage++ : this->idleActualImage = 0;
					break;
				}
			}
		}
		break;


	case FATTY:
		switch (this->dir)														// segun la direccion voy a espejar o no
		{
			case Direction::Left:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_FATTY) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_FATTY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_ATTACKING:
					if ((this->attackActualImage + 1) < 2*ATTACKING_PICS_FATTY)
					{
						//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->attackActualImage++;																									// termino la secuencia de disparo
					}
					else
					{
						this->secuenceOver_ = true;
						this->attackActualImage = 0;
						//this->state = enemy_IDLE;
//						this->active = false;
					}
					al_draw_scaled_bitmap(this->attackImages[this->attackActualImage/2], 0, 0, al_get_bitmap_height(this->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(this->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_scaled_bitmap(this->trapImages[this->actualImage], 0, 0, al_get_bitmap_height(this->trapImages[this->actualImage]), al_get_bitmap_width(this->trapImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					this->actualImage++;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_FATTY)
					{
						//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
//					this->active = false;
					//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->idleActualImage + 1) < IDLE_PICS_FATTY) ? this->idleActualImage++ : this->idleActualImage = 0;
					break;
				}
			}
			break;
			case Direction::Right:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la derecha, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						//this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
//						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_FATTY) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
//						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_FATTY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_ATTACKING:
					if ((this->attackActualImage + 1) < 2*ATTACKING_PICS_FATTY)
					{
						//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						this->attackActualImage++;																							// termino la secuencia de disparo
					}
					else
					{
						this->attackActualImage = 0;
						//this->state = enemy_IDLE;
//						this->active = false;
					}
					al_draw_scaled_bitmap(this->attackImages[this->attackActualImage/2], 0, 0, al_get_bitmap_height(this->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(this->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_scaled_bitmap(this->trapImages[this->actualImage], 0, 0, al_get_bitmap_height(this->trapImages[this->actualImage]), al_get_bitmap_width(this->trapImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					this->actualImage++;
					break;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_FATTY)
					{
						//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
//					this->active = false;
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->idleActualImage + 1) < IDLE_PICS_FATTY) ? this->idleActualImage++ : this->idleActualImage = 0;
					break;
				}
			}
		}
		break;



	case CRAZY:
		switch (this->dir)														// segun la direccion voy a espejar o no
		{
			case Direction::Left:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_CRAZY) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 3);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_CRAZY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_scaled_bitmap(this->trapImages[this->actualImage], 0, 0, al_get_bitmap_height(this->trapImages[this->actualImage]), al_get_bitmap_width(this->trapImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					this->actualImage++;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_CRAZY)
					{
						//al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
//					this->active = false;
					//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					((this->idleActualImage + 1) < IDLE_PICS_CRAZY) ? this->idleActualImage++ : this->idleActualImage = 0;
					break;
				}
			}
			break;
			case Direction::Right:
			{
				switch (this->state)
				{
				case enemy_WALKING:
					if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la derecha, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						//this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(this->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(this->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->walkActualImage + 1) < 2 * WALKING_PICS_FATTY) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						//this->state = enemy_IDLE;
					}
					else
					{
//						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 3);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					al_draw_scaled_bitmap(this->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(this->jumpImages[this->actualImage]), al_get_bitmap_width(this->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_FALLING:
					if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->secuenceOver_ = true;
						this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
//						this->state = enemy_IDLE;
					}
					else
					{
						//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (FALLING_PICS_CRAZY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
					}
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_TRAPPED:
					((this->actualImage + 1) < TRAPPED_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_scaled_bitmap(this->trapImages[this->actualImage], 0, 0, al_get_bitmap_height(this->trapImages[this->actualImage]), al_get_bitmap_width(this->trapImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					this->actualImage++;
				case enemy_DYING:
					if ((this->dieActualImage + 1) < DYING_PICS_CRAZY)
					{
//						al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
						this->dieActualImage++;
					}
					else
					{
						this->secuenceOver_ = true;
						//				this->active = false;			// aca si se podria desactivar el objeto
					}
					al_draw_scaled_bitmap(this->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(this->dieImages[this->dieActualImage]), al_get_bitmap_width(this->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					break;
				case enemy_IDLE:
					this->actualImage = 0;
					//					this->active = false;
					//al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
					al_draw_scaled_bitmap(this->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(this->idleImages[this->idleActualImage]), al_get_bitmap_width(this->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					((this->idleActualImage + 1) < IDLE_PICS_CRAZY) ? this->idleActualImage++ : this->idleActualImage = 0;
					break;
				}
			}
		}
		break;
	}
}

void Obj_Graf_Enemy::startDraw(Direction dir, void *state, POINT_& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos.set_x_coord(pos.get_x_coord());
	this->pos.set_y_coord(pos.get_y_coord());
	this->InitalPos = pos;
	this->state = *(ENEMY_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
	this->secuenceOver_ = false;
}

void Obj_Graf_Enemy::destroy()
{
	delete[] walkImages;
	delete[] jumpImages;
	delete[] idleImages;
	delete[] attackImages;
	delete[] fallImages;
	delete[] trapImages;
	delete[] dieImages;
}

void Obj_Graf_Enemy::reset()
{
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->idleActualImage = 0;
	this->dieActualImage = 0;
}

bool Obj_Graf_Enemy::secuenceOver()
{
	return this->secuenceOver_;
}

void Obj_Graf_Enemy::loadBitmap(ENEMY_TYPE type)
{
	string carpeta1;
	string carpeta2;
	string carpeta3;
	string file;
	string imageDir;

	switch (this->type)
	{
	case PURPLE:
		carpeta1 = FOLDER_ENEMY;
		carpeta2 = FOLDER_PURPLE;
		carpeta3 = FOLDER_WALKING;
		file = FILE_PURPLE_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_PURPLE];
		for (int i = 0; i < WALKING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_PURPLE_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_PURPLE];
		for (int i = 0; i < JUMPING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_PURPLE_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_PURPLE];
		for (int i = 0; i < IDLE_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_PURPLE_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_PURPLE];
		for (int i = 0; i < ATTACKING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_PURPLE_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_PURPLE];
		for (int i = 0; i < FALLING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_PURPLE_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_PURPLE];
		for (int i = 0; i < TRAPPED_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DYING;
		file = FILE_PURPLE_DYING;
		this->dieImages = new ALLEGRO_BITMAP *[DYING_PICS_PURPLE];
		for (int i = 0; i < DYING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->dieImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;

	case FATTY:
		carpeta1 = FOLDER_ENEMY;
		carpeta2 = FOLDER_FATTY;
		carpeta3 = FOLDER_WALKING;
		file = FILE_FATTY_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_FATTY];
		for (int i = 0; i < WALKING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_FATTY_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_FATTY];
		for (int i = 0; i < JUMPING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_FATTY_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_FATTY];
		for (int i = 0; i < IDLE_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_FATTY_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_FATTY];
		for (int i = 0; i < ATTACKING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_FATTY_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_FATTY];
		for (int i = 0; i < FALLING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_FATTY_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_FATTY];
		for (int i = 0; i < TRAPPED_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DYING;
		file = FILE_FATTY_DYING;
		this->dieImages = new ALLEGRO_BITMAP *[DYING_PICS_FATTY];
		for (int i = 0; i < DYING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->dieImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;

	case CRAZY:
		carpeta1 = FOLDER_ENEMY;
		carpeta2 = FOLDER_CRAZY;
		carpeta3 = FOLDER_WALKING;
		file = FILE_CRAZY_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_CRAZY];
		for (int i = 0; i < WALKING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_CRAZY_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_CRAZY];
		for (int i = 0; i < JUMPING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_CRAZY_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_CRAZY];
		for (int i = 0; i < IDLE_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_CRAZY_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_CRAZY];
		for (int i = 0; i < ATTACKING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_CRAZY_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_CRAZY];
		for (int i = 0; i < FALLING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_CRAZY_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_CRAZY];
		for (int i = 0; i < TRAPPED_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DYING;
		file = FILE_CRAZY_DYING;
		this->dieImages = new ALLEGRO_BITMAP *[DYING_PICS_CRAZY];
		for (int i = 0; i < DYING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
			this->dieImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;
	}
}
