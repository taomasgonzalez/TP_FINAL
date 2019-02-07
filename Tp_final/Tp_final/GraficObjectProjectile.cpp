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
	loadBitmap(type);
	this->type = type;
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
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
					(this->actualImage < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_DECAYING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE/2))						// BLOCK_SIZE / 2 para que no atraviese el piso
				{
					this->active = false;
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImpactImage++;
				}
				else
					this->active = false;
				break;
			}
			break;

		case Direction::Right:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					// this->active = false;
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_height(this->moveImages[this->actualImage]), al_get_bitmap_width(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), al_get_bitmap_height(this->moveImages[this->actualImage]) / 6, al_get_bitmap_width(this->moveImages[this->actualImage]) / 6, ALLEGRO_FLIP_HORIZONTAL);
					// al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_scaled_bitmap(this->moveImages[this->actualImage], 0, 0, al_get_bitmap_height(this->moveImages[this->actualImage]), al_get_bitmap_width(this->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), al_get_bitmap_height(this->moveImages[this->actualImage]) / 6, al_get_bitmap_width(this->moveImages[this->actualImage]) / 6, ALLEGRO_FLIP_HORIZONTAL);
					// al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
					(this->actualImage <= MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_DECAYING :
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))		
				{
					this->active = false;
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImpactImage++;
				}
				else
					this->active = false;
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
					this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
					//this->active = false;
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);
					(this->actualImage < MOVING_PICS_FIRE) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_DECAYING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))						// BLOCK_SIZE / 2 para que no atraviese el piso
				{
					this->active = false;
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				}
				else
				{
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < DECAYING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
					this->actualImpactImage++;
				}
				else
					this->active = false;
				break;
			}
			break;

		case Direction::Right:
			switch (this->state)
			{
			case proy_MOVING:
				if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
				{
					this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
					// this->active = false;
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
					(this->actualImage <= MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_DECAYING:
				if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE / 2))
				{
					this->active = false;
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				}
				else
				{
					al_draw_bitmap(this->decayImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
					(this->actualImage < MOVING_PICS_SNOW) ? this->actualImage++ : this->actualImage = 0;
				}
				break;
			case proy_IMPACT:
				if (this->actualImpactImage < IMPACT_PICS_SNOW)															// si todavia no termino la secuancia que siga
				{
					al_draw_bitmap(this->impactImages[this->actualImpactImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
					this->actualImpactImage++;
				}
				else
					this->active = false;
				break;
			}
			break;
		}
		break;
	}
}

void Obj_Graf_Projectile::startDraw(Direction dir, void *state, POINT& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos = pos;
	this->InitalPos = pos;
	this->state = *(PROYECTILE_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
}

void Obj_Graf_Projectile::destroy()
{
	delete[] moveImages;
	delete[] decayImages;
	delete[] impactImages;
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
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->moveImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DECAYING;
		file = FILE_SNOW_DECAYING;
		this->decayImages = new ALLEGRO_BITMAP *[DECAYING_PICS_SNOW];
		for (int i = 0; i < DECAYING_PICS_SNOW; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
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
		break;

	case FIRE:
		carpeta1 = FOLDER_PROYECTILES;
		carpeta2 = FOLDER_FIRE;
		carpeta3 = FOLDER_MOVING;
		file = FILE_FIRE_MOVING;
		this->moveImages = new ALLEGRO_BITMAP *[MOVING_PICS_FIRE];
		for (int i = 0; i < MOVING_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->moveImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DECAYING;
		file = FILE_FIRE_DECAYING;
		this->decayImages = new ALLEGRO_BITMAP *[DECAYING_PICS_FIRE];
		for (int i = 0; i < DECAYING_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->decayImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IMPACT;
		file = FILE_FIRE_IMPACT;
		this->impactImages = new ALLEGRO_BITMAP *[IMPACT_PICS_FIRE];
		for (int i = 0; i < IMPACT_PICS_FIRE; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->impactImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;
	}
}
