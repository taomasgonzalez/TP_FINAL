#include "GraficObjectBall.h"
#include "BallDefines.h"

using namespace std;

Obj_Graf_Ball::Obj_Graf_Ball()
{
}


Obj_Graf_Ball::~Obj_Graf_Ball()
{
}

Obj_Graf_Ball::Obj_Graf_Ball(double ID) : Obj_Graf(ID)
{
	this->actualImage = 0;
	unsigned int actualDestructionImage = 0;
	loadBitmap();
}

void Obj_Graf_Ball::startDraw(Direction dir, void * state, POINT & pos)
{
	this->active = true;
	this->dir = dir;
	this->pos = pos;
	this->InitalPos = pos;
	this->state = *(BALL_STATE *)state;
	this->actualImage = 0;
}

void Obj_Graf_Ball::draw()
{
	switch (this->dir)														// segun la direccion voy a espejar o no
	{
	case Direction::Left:
		switch (this->state)
		{
		case ball_IDLE:
			al_draw_bitmap(this->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			(this->actualImage < MOVING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case ball_MOVING:
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
				(this->actualImage < MOVING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case ball_PUSHING:
			if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				//this->active = false;
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			}
			else
			{
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED);
				(this->actualImage < PUSHING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case ball_FALLING:
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case ball_DESTRUCTION:
			if (this->actualDestructionImage < DESTRUCTION_PICS)															// si todavia no termino la secuancia que siga
			{
				al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->actualDestructionImage++;
			}
			else
				this->active = false;
			break;
		}
		break;

	case Direction::Right:
		switch (this->state)
		{
		case ball_IDLE:
			al_draw_bitmap(this->idleImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			(this->actualImage < MOVING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case ball_MOVING:
			if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
				//this->active = false;
				al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
				(this->actualImage < MOVING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case ball_PUSHING:
			if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
				//this->active = false;
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED);
				(this->actualImage < PUSHING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case ball_FALLING:
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case ball_DESTRUCTION:
			if (this->actualDestructionImage < DESTRUCTION_PICS)															// si todavia no termino la secuancia que siga
			{
				al_draw_bitmap(this->destructiontImages[this->actualDestructionImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->actualDestructionImage++;
			}
			else
				this->active = false;
			break;
		}
		break;
	}
}

void Obj_Graf_Ball::loadBitmap()
{
	string carpeta1;
	string carpeta3;
	string file;
	string imageDir;


	carpeta1 = FOLDER_BALL;
	carpeta3 = FOLDER_IDLE;
	file = FILE_MOVING;
	this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS];
	for (int i = 0; i < IDLE_PICS; i++)
	{
		imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
		this->idleImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_MOVING;
	file = FILE_MOVING;
	this->moveImages = new ALLEGRO_BITMAP *[MOVING_PICS];
	for (int i = 0; i < MOVING_PICS; i++)
	{
		imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
		this->moveImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_PUSHING;
	file = FILE_PUSHING;
	this->pushImages = new ALLEGRO_BITMAP *[PUSHING_PICS];
	for (int i = 0; i < PUSHING_PICS; i++)
	{
	imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
		this->pushImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_FALLING;
	file = FILE_FALLING;
	this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS];
	for (int i = 0; i < FALLING_PICS; i++)
	{
		imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
		this->fallImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_DESTRUCTION;
	file = FILE_DESTRUCTION;
	this->destructiontImages = new ALLEGRO_BITMAP *[DESTRUCTION_PICS];
	for (int i = 0; i < DESTRUCTION_PICS; i++)
	{
		imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
		this->destructiontImages[i] = al_load_bitmap(imageDir.c_str());
	}
}

void Obj_Graf_Ball::destroy()
{
	delete[] idleImages;
	delete[] moveImages;
	delete[] pushImages;
	delete[] fallImages;
	delete[] destructiontImages;
}
