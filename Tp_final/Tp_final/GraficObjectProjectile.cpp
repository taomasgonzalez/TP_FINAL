#include "GraficObjectProjectile.h"

using namespace std;

Obj_Graf_Projectile::Obj_Graf_Projectile()
{
}


Obj_Graf_Projectile::Obj_Graf_Projectile(double ID, PROYECTILE_TYPE type, ImageContainer* container) : Obj_Graf(ID)
{
	this->actualImage = 0;
	this->actualImpactImage = 0;
	this->actualDecayImage = 0;
	this->type = type;
	switch (type)
	{
	case SNOW:
		this->velX = VEL_SNOW;
		container->my_projectile_images_container.snowball;
		break;
	case FIRE:
		this->velX = VEL_FIRE;
		container->my_projectile_images_container.fire;
		break;
	}

	
}

Obj_Graf_Projectile::~Obj_Graf_Projectile()
{
}

void Obj_Graf_Projectile::draw()
{
	switch (this->type)
	{
	case SNOW:
		switch (this->dir)														// segun la direccion voy a espejar o no
		{
		case Direction::Left:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_SNOW)
				{
					al_draw_scaled_bitmap(images->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(images->decayImages[this->actualDecayImage]), al_get_bitmap_height(images->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					this->actualDecayImage++;																									// termino la secuencia de disparo
				}
				else
				{
					this->secuenceOver_ = true;
					this->actualDecayImage = 0;
					this->active = false;
				}
				break;


				//if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE/2))						// BLOCK_SIZE / 2 para que no atraviese el piso
				//{
				//	this->active = false;
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//}
				//else
				//{
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(images->impactImages[this->actualImpactImage]), al_get_bitmap_height(images->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(images->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImpactImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
				break;
			case proy_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImage = 0;
				}
				else
				{
					al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_SNOW - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				break;
			}
			break;

		case Direction::Right:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					// this->active = false;
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					// al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_SNOW)
				{
					al_draw_scaled_bitmap(images->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(images->decayImages[this->actualDecayImage]), al_get_bitmap_height(images->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					this->actualDecayImage++;																									// termino la secuencia de disparo
				}
				else
				{
					this->secuenceOver_ = true;
					this->actualDecayImage = 0;
					this->active = false;
				}
				break;


				//if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))		
				//{
				//	this->active = false;
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//}
				//else
				//{
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(images->impactImages[this->actualImpactImage]), al_get_bitmap_height(images->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(images->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImpactImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
				break;
			case proy_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImage = 0;
				}
				else
				{
					al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_SNOW - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				break;
			}
			break;
		}
		break;
	case FIRE:
		switch (this->dir)														// segun la direccion voy a espejar o no
		{
		case Direction::Left:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_FIRE) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_FIRE)
				{
					al_draw_scaled_bitmap(images->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(images->decayImages[this->actualDecayImage]), al_get_bitmap_height(images->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					this->actualDecayImage++;																									// termino la secuencia de disparo
				}
				else
				{
					this->secuenceOver_ = true;
					this->actualDecayImage = 0;
					this->active = false;
				}
				break;


				//if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))						// BLOCK_SIZE / 2 para que no atraviese el piso
				//{
				//	this->active = false;
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//}
				//else
				//{
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(images->impactImages[this->actualImpactImage]), al_get_bitmap_height(images->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(images->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImpactImage++;
				}
				else
				{
					this->active = false;
					this->secuenceOver_ = true;
				}
				break;
			case proy_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImage = 0;
				}
				else
				{
					//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_FIRE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(images->fallImages[this->actualImage]), al_get_bitmap_height(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				break;
			}
			break;

		case Direction::Right:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->secuenceOver_ = true;
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					// this->active = false;
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(images->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_FIRE) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_FIRE)
				{
					al_draw_scaled_bitmap(images->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(images->decayImages[this->actualDecayImage]), al_get_bitmap_height(images->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
					this->actualDecayImage++;																									// termino la secuencia de disparo
				}
				else
				{
					this->secuenceOver_ = true;
					this->actualDecayImage = 0;
					this->active = false;
				}
				break;


				//if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))
				//{
				//	this->active = false;
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//}
				//else
				//{
				//	al_draw_bitmap(images->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_FIRE)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(images->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(images->impactImages[this->actualImpactImage]), al_get_bitmap_height(images->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(images->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImpactImage++;
				}
				else
				{
					this->secuenceOver_ = true;
					this->active = false;
				}
				break;
			case proy_FALLING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
				{
					this->secuenceOver_ = true;
					this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
					//				this->active = false;															// se pasiva el objeto
					this->actualImage = 0;
				}
				else
				{
					al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(images->fallImages[this->actualImage]), al_get_bitmap_height(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
					(this->actualImage < (FALLING_PICS_FIRE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
				}
				break;
			}
			break;
		}
		break;
	}
}

void Obj_Graf_Projectile::startDraw(Direction dir, void *state, POINT_& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos = pos;
	this->InitalPos = pos;
	this->state = *(PROYECTILE_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
	this->secuenceOver_ = false;
}

void Obj_Graf_Projectile::destroy()
{
}

void Obj_Graf_Projectile::reset()
{
	this->actualImage = 0;
	this->actualDecayImage = 0;
	this->actualImpactImage = 0;
}

bool Obj_Graf_Projectile::secuenceOver()
{
	return this->secuenceOver_;
}

