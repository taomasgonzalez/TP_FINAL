#include "GraficObjectProjectile.h"
#include "ProjectileDefine.h"

using namespace std;

Obj_Graf_Projectile::Obj_Graf_Projectile()
{
}


Obj_Graf_Projectile::Obj_Graf_Projectile(double ID, PROYECTILE_TYPE type) : Obj_Graf(ID)
{
	this->actualImage = 0;
	this->actualImpactImage = 0;
	this->actualDecayImage = 0;
	this->type = type;
	loadBitmap(type);
	switch (type)
	{
	case SNOW:
		this->velX = VEL_SNOW;
		break;
	case FIRE:
		this->velX = VEL_FIRE;
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
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_SNOW)
				{
					al_draw_scaled_bitmap(this->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(this->decayImages[this->actualDecayImage]), al_get_bitmap_height(this->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//}
				//else
				//{
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(this->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(this->impactImages[this->actualImpactImage]), al_get_bitmap_height(this->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
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
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					// al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_SNOW)
				{
					al_draw_scaled_bitmap(this->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(this->decayImages[this->actualDecayImage]), al_get_bitmap_height(this->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//}
				//else
				//{
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(this->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(this->impactImages[this->actualImpactImage]), al_get_bitmap_height(this->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
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
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(this->fallImages[this->actualImage]), al_get_bitmap_width(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_FIRE) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_FIRE)
				{
					al_draw_scaled_bitmap(this->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(this->decayImages[this->actualDecayImage]), al_get_bitmap_height(this->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//}
				//else
				//{
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(this->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(this->impactImages[this->actualImpactImage]), al_get_bitmap_height(this->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
					//al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
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
				al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(this->fallImages[this->actualImage]), al_get_bitmap_height(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
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
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(this->moveImages[this->actualImage]), al_get_bitmap_height(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
				}
				((this->actualImage + 1) < MOVING_PICS_FIRE) ? this->actualImage++ : this->actualImage = 0;
				break;
			case proy_DECAYING:
				if (this->actualDecayImage < DECAYING_PICS_FIRE)
				{
					al_draw_scaled_bitmap(this->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(this->decayImages[this->actualDecayImage]), al_get_bitmap_height(this->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//}
				//else
				//{
				//	al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				//	this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
				//	(this->actualImage < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				//}
				//break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_FIRE)															// si todavia no termino la secuancia que siga
				{
					al_draw_scaled_bitmap(this->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(this->impactImages[this->actualImpactImage]), al_get_bitmap_height(this->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
					//al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
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
					al_draw_scaled_bitmap(this->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(this->fallImages[this->actualImage]), al_get_bitmap_height(this->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
	delete[] moveImages;
	delete[] decayImages;
	delete[] impactImages;
	delete[] fallImages;
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

void Obj_Graf_Projectile::loadBitmap(PROYECTILE_TYPE type) 
{
	string carpeta1;
	string carpeta2;
	string carpeta3;
	string file;
	string imageDir;

	switch (this->type)
	{
	case SNOW:
		carpeta1 = FOLDER_PROYECTILES;
		carpeta2 = FOLDER_SNOW;
		carpeta3 = FOLDER_MOVING;
		file = FILE_SNOW_MOVING;
		this->moveImages = new ALLEGRO_BITMAP *[MOVING_PICS_SNOW];
		for (int i = 0; i < MOVING_PICS_SNOW; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
			this->moveImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DECAYING;
		file = FILE_SNOW_DECAYING;
		this->decayImages = new ALLEGRO_BITMAP *[DECAYING_PICS_SNOW];
		for (int i = 0; i < DECAYING_PICS_SNOW; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
			this->decayImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IMPACT;
		file = FILE_SNOW_IMPACT;
		this->impactImages = new ALLEGRO_BITMAP *[IMPACT_PICS_SNOW];
		for (int i = 0; i < IMPACT_PICS_SNOW; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->impactImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_SNOW_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_SNOW];
		for (int i = 0; i < FALLING_PICS_SNOW; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;

	case FIRE:
		carpeta1 = FOLDER_PROYECTILES;
		carpeta2 = FOLDER_FIRE;
		carpeta3 = FOLDER_MOVING;
		file = FILE_FIRE_MOVING;
		this->moveImages = new ALLEGRO_BITMAP *[MOVING_PICS_FIRE];
		for (int i = 0; i < MOVING_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 6) + ".png";
			this->moveImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DECAYING;
		file = FILE_FIRE_DECAYING;
		this->decayImages = new ALLEGRO_BITMAP *[DECAYING_PICS_FIRE];
		for (int i = 0; i < DECAYING_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
			this->decayImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IMPACT;
		file = FILE_FIRE_IMPACT;
		this->impactImages = new ALLEGRO_BITMAP *[IMPACT_PICS_FIRE];
		for (int i = 0; i < IMPACT_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
			this->impactImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_FIRE_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_FIRE];
		for (int i = 0; i < FALLING_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 6) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;
	}
}
