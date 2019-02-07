#include "GraficObjectEnemy.h"
#include "EnemyDefines.h"

using namespace std;

Obj_Graf_Enemy::Obj_Graf_Enemy()
{
}

Obj_Graf_Enemy::Obj_Graf_Enemy(double ID, ENEMY_TYPE type) : Obj_Graf(ID)
{
	this->actualImage = 0;
	loadBitmap(type);
	this->type = type;

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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_PURPLE)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImage++;
					break;
				case enemy_IDLE:
					this->actualImage = 0;
					this->active = false;
					al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
						al_draw_scaled_bitmap(this->walkImages[this->actualImage], 0, 0, al_get_bitmap_height(this->walkImages[this->actualImage]), al_get_bitmap_width(this->walkImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), al_get_bitmap_height(this->walkImages[this->actualImage]) / 3, al_get_bitmap_width(this->walkImages[this->actualImage]) / 3, ALLEGRO_FLIP_HORIZONTAL);
						//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_PURPLE)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_PURPLE) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImage++;
					break;
				case enemy_IDLE:
					this->actualImage = 0;
					this->active = false;
					al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					}
					else
					{
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_FATTY)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					/*this->fallTicks++;
					this->jumpTicks = 0;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(fallTicks, 2));
					al_draw_bitmap(this->fallImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					break;*/
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_ATTACKING:
					if (this->actualImage < ATTACKING_PICS_FATTY)
					{
						al_draw_bitmap(this->attackImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->actualImage++;																									// termino la secuencia de disparo
					}
					else
					{
						this->state = enemy_IDLE;
						this->active = false;
					}
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImage++;
				case enemy_IDLE:
					this->actualImage = 0;
					this->active = false;
					al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_FATTY)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_ATTACKING:
					if (this->actualImage < ATTACKING_PICS_FATTY)
					{
						al_draw_bitmap(this->attackImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						this->actualImage++;																							// termino la secuencia de disparo
					}
					else
					{
						this->state = enemy_IDLE;
						this->active = false;
					}
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_FATTY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImage++;
					break;
				case enemy_IDLE:
					this->actualImage = 0;
					this->active = false;
					al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_CRAZY)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					/*this->fallTicks++;
					this->jumpTicks = 0;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(fallTicks, 2));
					al_draw_bitmap(this->fallImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					break;*/
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImage++;
				case enemy_IDLE:
					this->actualImage = 0;
					this->active = false;
					al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
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
						this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
						this->active = false;															// se pasiva el objeto
						this->state = enemy_IDLE;
						this->actualImage = 0;
					}
					else
					{
						al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
						this->actualImage++;																									// ubico el siguiente frame
						if (this->actualImage >= WALKING_PICS_CRAZY)																					// se reinicia la secuancia de dibujo
							this->actualImage = 0;
						this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}
					break;
				case enemy_JUMPING_FOWARD:
					if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
						//				this->active = false;															// se pasiva el objeto
						this->actualImage = 0;
						this->state = enemy_IDLE;
					}
					else
					{
						al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
						(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
						this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
					}

					if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
					{
						this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					}
					else
						this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
					break;
				case enemy_FALLING:
					al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < FALLING_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					break;
				case enemy_TRAPPED:
					(this->actualImage < TRAPPED_PICS_CRAZY) ? this->actualImage++ : this->actualImage = 0;
					al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImage++;
				}
			case enemy_IDLE:
				this->actualImage = 0;
				this->active = false;
				al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
				break;
			}
		}
		break;
	}
}

void Obj_Graf_Enemy::startDraw(Direction dir, void *state, POINT& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos.set_x_coord(pos.get_x_coord());
	this->pos.set_y_coord(pos.get_y_coord());
	this->InitalPos = pos;
	this->state = *(ENEMY_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
}

void Obj_Graf_Enemy::destroy()
{
	delete[] walkImages;
	delete[] jumpImages;
	delete[] idleImages;
	delete[] attackImages;
	delete[] fallImages;
	delete[] trapImages;
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
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_PURPLE_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_PURPLE];
		for (int i = 0; i < JUMPING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_PURPLE_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_PURPLE];
		for (int i = 0; i < IDLE_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_PURPLE_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_PURPLE];
		for (int i = 0; i < ATTACKING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_PURPLE_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_PURPLE];
		for (int i = 0; i < FALLING_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_PURPLE_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_PURPLE];
		for (int i = 0; i < TRAPPED_PICS_PURPLE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;

	case FATTY:
		carpeta1 = FOLDER_ENEMY;
		carpeta2 = FOLDER_FATTY;
		carpeta3 = FOLDER_WALKING;
		file = FILE_PURPLE_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_FATTY];
		for (int i = 0; i < WALKING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_FATTY_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_FATTY];
		for (int i = 0; i < JUMPING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_FATTY_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_FATTY];
		for (int i = 0; i < IDLE_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_FATTY_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_FATTY];
		for (int i = 0; i < ATTACKING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_FATTY_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_FATTY];
		for (int i = 0; i < FALLING_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_FATTY_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_FATTY];
		for (int i = 0; i < TRAPPED_PICS_FATTY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
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
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_CRAZY_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_CRAZY];
		for (int i = 0; i < JUMPING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_CRAZY_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_CRAZY];
		for (int i = 0; i < IDLE_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_CRAZY_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_CRAZY];
		for (int i = 0; i < ATTACKING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_CRAZY_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_CRAZY];
		for (int i = 0; i < FALLING_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_TRAPPED;
		file = FILE_CRAZY_TRAPPED;
		this->trapImages = new ALLEGRO_BITMAP *[TRAPPED_PICS_CRAZY];
		for (int i = 0; i < TRAPPED_PICS_CRAZY; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->trapImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;
	}
}
