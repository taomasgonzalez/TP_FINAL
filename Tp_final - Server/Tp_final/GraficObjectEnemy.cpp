#include "GraficObjectEnemy.h"

using namespace std;

Obj_Graf_Enemy::Obj_Graf_Enemy()
{
}

Obj_Graf_Enemy::Obj_Graf_Enemy(double ID, ENEMY_TYPE type, ImageContainer* container) : Obj_Graf(ID)
{
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->walkActualImage = 0;
	this->idleActualImage = 0;
	this->dieActualImage = 0;
	this->trap1ActualImage = 0;
	this->trap2ActualImage = 0;
	this->trap1ticks = 0;
	this->trap2ticks = 0;
	this->actualImageInball = 0;
	this->type = type;
	this->vel_x_inball = VEL_X_INBALL;

	switch (type)
	{
	case PURPLE:
		this->velX = VEL_PURPLE;
		images = &container->my_enemy_images_container.purple;
		break;
	case FATTY:
		this->velX = VEL_FATTY;
		images = &container->my_enemy_images_container.fatty;

		break;
	case CRAZY:
		this->velX = VEL_CRAZY;
		images = &container->my_enemy_images_container.crazy;
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
					//al_draw_bitmap(images->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				((this->walkActualImage + 1) < 2 * WALKING_PICS_PURPLE) ? this->walkActualImage++ : this->walkActualImage = 0;			// se pasa al siguiente sprite
				//break;
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}

				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				}
				else
					this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_PURPLE * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_PURPLE * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
				break;
			case enemy_DYING:
				if ((this->dieActualImage + 1) < DYING_PICS_PURPLE)
				{
					//al_draw_bitmap(images->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->dieActualImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					//				this->active = false;			// aca si se podria desactivar el objeto
				}
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				((this->idleActualImage + 1) < IDLE_PICS_PURPLE) ? this->idleActualImage++ : this->idleActualImage = 0;
				//al_draw_bitmap(images->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
				break;
			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < 2 * PUSHING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImageInball]), al_get_bitmap_width(images->fallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualDestructionImage++;
				}
				else
				{
					this->active = false;
					this->secuenceOver_ = true;
				}
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
					//al_draw_bitmap(images->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_PURPLE * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_PURPLE * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
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
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
									//al_draw_bitmap(images->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				((this->idleActualImage + 1) < IDLE_PICS_PURPLE) ? this->idleActualImage++ : this->idleActualImage = 0;
				break;

			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < PUSHING_PICS_BALL * 2) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->inballFallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballFallImages[this->actualImageInball]), al_get_bitmap_width(images->inballFallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualDestructionImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
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
					//al_draw_bitmap(images->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);																// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}

				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				}
				else
					this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_FATTY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_ATTACKING:
				if ((this->attackActualImage + 1) < 2 * ATTACKING_PICS_FATTY)
				{
					//al_draw_bitmap(images->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					this->attackActualImage++;																									// termino la secuencia de disparo
				}
				else
				{
					this->secuenceOver_ = true;
					this->attackActualImage = 0;
					//this->state = enemy_IDLE;
//						this->active = false;
				}
				al_draw_scaled_bitmap(images->attackImages[this->attackActualImage / 2], 0, 0, al_get_bitmap_height(images->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(images->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_FATTY * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_FATTY * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
				break;
			case enemy_DYING:
				if ((this->dieActualImage + 1) < DYING_PICS_FATTY)
				{
					//al_draw_bitmap(images->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->dieActualImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					//				this->active = false;			// aca si se podria desactivar el objeto
				}
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
									//al_draw_bitmap(images->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				((this->idleActualImage + 1) < IDLE_PICS_FATTY) ? this->idleActualImage++ : this->idleActualImage = 0;
				break;
			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < 2 * PUSHING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImageInball]), al_get_bitmap_width(images->fallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualDestructionImage++;
				}
				else
				{
					this->active = false;
					this->secuenceOver_ = true;
				}
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
					//						al_draw_bitmap(images->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//						al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}

				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				}
				else
					this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_FATTY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_ATTACKING:
				if ((this->attackActualImage + 1) < 2 * ATTACKING_PICS_FATTY)
				{
					//al_draw_bitmap(images->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					this->attackActualImage++;																							// termino la secuencia de disparo
				}
				else
				{
					this->attackActualImage = 0;
					//this->state = enemy_IDLE;
//						this->active = false;
				}
				al_draw_scaled_bitmap(images->attackImages[this->attackActualImage / 2], 0, 0, al_get_bitmap_height(images->attackImages[this->attackActualImage / 2]), al_get_bitmap_width(images->attackImages[this->attackActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_FATTY * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_FATTY * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
				break;
			case enemy_DYING:
				if ((this->dieActualImage + 1) < DYING_PICS_FATTY)
				{
					//al_draw_bitmap(images->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->dieActualImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					//				this->active = false;			// aca si se podria desactivar el objeto
				}
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				((this->idleActualImage + 1) < IDLE_PICS_FATTY) ? this->idleActualImage++ : this->idleActualImage = 0;
				break;
			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < PUSHING_PICS_BALL * 2) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->inballFallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballFallImages[this->actualImageInball]), al_get_bitmap_width(images->inballFallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualDestructionImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
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
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_FATTY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}

				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				}
				else
					this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX) / 3);				// se divide por 2 la velocidad ya que debera recorrer en x la 
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_CRAZY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_CRAZY * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_CRAZY * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
				break;
			case enemy_DYING:
				if ((this->dieActualImage + 1) < DYING_PICS_CRAZY)
				{
					//al_draw_bitmap(images->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->dieActualImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					//				this->active = false;			// aca si se podria desactivar el objeto
				}
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
									//al_draw_bitmap(images->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				((this->idleActualImage + 1) < IDLE_PICS_CRAZY) ? this->idleActualImage++ : this->idleActualImage = 0;
				break;
			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < 2 * PUSHING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImageInball]), al_get_bitmap_width(images->fallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualDestructionImage++;
				}
				else
				{
					this->active = false;
					this->secuenceOver_ = true;
				}
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
				al_draw_scaled_bitmap(images->walkImages[this->walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[this->walkActualImage / 2]), al_get_bitmap_width(images->walkImages[this->walkActualImage / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//						al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					(this->actualImage < (JUMPING_PICS_CRAZY - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
				}

				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				}
				else
					this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 3);				// se divide por 2 la velocidad ya que debera recorrer en x la 
				al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_CRAZY - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_TRAPPED_1:
				this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_CRAZY * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
				al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				this->trap1ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap1ticks = 0;
				}
				break;
			case enemy_TRAPPED_2:
				this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_CRAZY * 2)) / 2;
				al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				this->trap2ticks++;
				if (this->trap1ticks > TICKS_TRAPPED)
				{
					this->secuenceOver_ = true;
					this->trap2ticks = 0;
				}
				break;
			case enemy_DYING:
				if ((this->dieActualImage + 1) < DYING_PICS_CRAZY)
				{
					//						al_draw_bitmap(images->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->dieActualImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					//				this->active = false;			// aca si se podria desactivar el objeto
				}
				al_draw_scaled_bitmap(images->dieImages[this->dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[this->dieActualImage]), al_get_bitmap_width(images->dieImages[this->dieActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				break;
			case enemy_IDLE:
				this->actualImage = 0;
				//					this->active = false;
				//al_draw_bitmap(images->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
				al_draw_scaled_bitmap(images->idleImages[this->idleActualImage], 0, 0, al_get_bitmap_height(images->idleImages[this->idleActualImage]), al_get_bitmap_width(images->idleImages[this->idleActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
				((this->idleActualImage + 1) < IDLE_PICS_CRAZY) ? this->idleActualImage++ : this->idleActualImage = 0;
				break;
			case enemy_INBALL_IDLE:
				al_draw_scaled_bitmap(images->inballIdleImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[this->actualImageInball]), al_get_bitmap_width(images->inballIdleImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(images->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				((this->actualImageInball + 1) < IDLE_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				break;
			case enemy_INBALL_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
					((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_PUSHING:
				if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					//this->active = false;
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED_INBALL);
					((this->actualImageInball + 1) < PUSHING_PICS_BALL * 2) ? this->actualImageInball++ : this->actualImageInball = 0;
				}
				al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImageInball = 0;
					//this->state = player_IDLE;
				}
				else
				{
					//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImageInball < (FALLING_PICS_BALL - 1)) ? this->actualImageInball++ : this->actualImageInball = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->inballFallImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballFallImages[this->actualImageInball]), al_get_bitmap_width(images->inballFallImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			case enemy_INBALL_DESTRUCTION:
				if (this->actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->inballDestructiontImages[this->actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[this->actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[this->actualDestructionImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualDestructionImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
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
}

void Obj_Graf_Enemy::reset()
{
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->walkActualImage = 0;
	this->idleActualImage = 0;
	this->dieActualImage = 0;
	this->trap1ActualImage = 0;
	this->trap2ActualImage = 0;
	this->trap1ticks = 0;
	this->trap2ticks = 0;
	this->actualImageInball = 0;
}

bool Obj_Graf_Enemy::secuenceOver()
{
	return this->secuenceOver_;
}
