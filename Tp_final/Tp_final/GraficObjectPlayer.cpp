#include "GraficObjectPlayer.h"
#include "PlayerDefines.h"
#include <iostream>

using namespace std;


Obj_Graf_Player::Obj_Graf_Player()
{
}

Obj_Graf_Player::Obj_Graf_Player(double ID, PLAYER_TYPE type) : Obj_Graf(ID)
{
	this->velX = VELOCITY_X;					// se setea la velocidad de desplazamiento de los jugadores
	this->type = type;
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->dieActualImage = 0;
	loadBitmap(type);					// se cargan las imagenes de los personajes que corresponden
}


Obj_Graf_Player::~Obj_Graf_Player()
{
	
}


void Obj_Graf_Player::loadBitmap(PLAYER_TYPE type)
{
	string carpeta1;
	string carpeta2;
	string carpeta3;
	string file;
	string imageDir;

	switch (this->type)
	{
	case TOM:
		carpeta1 = FOLDER_CHARA;
		carpeta2 = FOLDER_TOM;
		carpeta3 = FOLDER_WALKING;
		file = FILE_TOM_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS];
		for (int i = 0; i < WALKING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_TOM_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS];
		for (int i = 0; i < JUMPING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_TOM_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS];
		for (int i = 0; i < IDLE_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_TOM_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS];
		for (int i = 0; i < ATTACKING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_TOM_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS];
		for (int i = 0; i < FALLING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_PUSHING;
		file = FILE_TOM_PUSHING;
		this->fallImages = new ALLEGRO_BITMAP *[PUSHING_PICS];
		for (int i = 0; i < PUSHING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->pushImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DYING;
		file = FILE_TOM_DYING;
		this->fallImages = new ALLEGRO_BITMAP *[DYING_PICS];
		for (int i = 0; i < DYING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->pushImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;

	case NICK:
		carpeta1 = FOLDER_CHARA;
		carpeta2 = FOLDER_NICK;
		carpeta3 = FOLDER_WALKING;
		file = FILE_NICK_WALKING;
		this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS];
		for (int i = 0; i < WALKING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->walkImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_JUMPING;
		file = FILE_NICK_JUMPING;
		this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS];
		for (int i = 0; i < JUMPING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_IDLE;
		file = FILE_NICK_IDLE;
		this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS];
		for (int i = 0; i < IDLE_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->idleImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_ATTACKING;
		file = FILE_NICK_ATTACKING;
		this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS];
		for (int i = 0; i < ATTACKING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->attackImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_FALLING;
		file = FILE_NICK_FALLING;
		this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS];
		for (int i = 0; i < FALLING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->fallImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_PUSHING;
		file = FILE_NICK_PUSHING;
		this->fallImages = new ALLEGRO_BITMAP *[PUSHING_PICS];
		for (int i = 0; i < PUSHING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->pushImages[i] = al_load_bitmap(imageDir.c_str());
		}
		carpeta3 = FOLDER_DYING;
		file = FILE_NICK_DYING;
		this->fallImages = new ALLEGRO_BITMAP *[DYING_PICS];
		for (int i = 0; i < DYING_PICS; i++)
		{
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
			this->pushImages[i] = al_load_bitmap(imageDir.c_str());
		}
		break;
	}
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
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				this->state = player_IDLE;
			}
			else
			{
				al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				this->actualImage++;																									// ubico el siguiente frame
				if (this->actualImage >= WALKING_PICS)																					// se reinicia la secuancia de dibujo
					this->actualImage = 0;
				this->pos.set_x_coord(this->pos.get_x_coord() - this->velX);															// muevo la posicion del dibujo
			}
			break;
		case player_JUMPING:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2*BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				this->state = player_IDLE;
			}
			else
			{
				al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1))? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}
			break;
		case player_ATTACKING:
			if (this->attackActualImage < ATTACKING_PICS)
			{
				al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				this->attackActualImage++;																									// termino la secuencia de disparo
			}
			else
			{
				this->attackActualImage = 0;
				this->state = player_IDLE;
//				this->active = false;
			}
			break;
		case player_FALLING:
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case player_IDLE:
			this->actualImage = 0;
//			this->active = false;																										// por la dudas lo vuelvo a pasivar porque en la secuencia de caida no se desactiva por si solo
			al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
			break;
		case player_JUMPING_FOWARD:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				this->state = player_IDLE;
			}
			else
			{
				al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}

			if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
			}
			else
				this->pos.set_x_coord(this->pos.get_x_coord() - (this->velX)/2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
			break;																				// misma distancia en el doble de tiempo
		case player_PUSHING:
			if (this->pos.get_x_coord() < (this->InitalPos.get_x_coord() - BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
				//this->active = false;
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->pos.set_x_coord(this->pos.get_x_coord() - VEL_PUSHED);
				(this->actualImage < PUSHING_PICS) ? this->actualImage++ : this->actualImage = 0;
			}
			break;
		case player_DYING:
			if (this->dieActualImage < DYING_PICS)
			{
				al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
				this->dieImages++;
			}
			else
			{
				this->dieImages = 0;
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
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
//				this->isActive = false;															// se pasiva el objeto
				this->state = player_IDLE;
				this->actualImage = 0;
			}
			else
			{
				//al_draw_scaled_bitmap(this->walkImages[this->actualImage], 0, 0, al_get_bitmap_height(this->walkImages[this->actualImage]), al_get_bitmap_width(this->walkImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), al_get_bitmap_height(this->walkImages[this->actualImage]) / 6, al_get_bitmap_width(this->walkImages[this->actualImage]) / 6, ALLEGRO_FLIP_HORIZONTAL);
				al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
				this->actualImage++;																									// ubico el siguiente frame
				if (this->actualImage >= WALKING_PICS)																					// se reinicia la secuancia de dibujo
					this->actualImage = 0;
				this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
			}
			break;
		case player_JUMPING:

			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				this->state = player_IDLE;
			}
			else
			{
				al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}
			break;
		case player_ATTACKING:
			if (this->attackActualImage < ATTACKING_PICS)
			{
				al_draw_bitmap(this->attackImages[this->attackActualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				this->attackActualImage++;																							// termino la secuencia de disparo
			}
			else
			{
				this->attackActualImage = 0;
				this->state = player_IDLE;
//				this->Active = false;
			}
			break;
		case player_FALLING:
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case player_IDLE:
			this->actualImage = 0;
//			this->active = false;
			al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
			break;
		case player_JUMPING_FOWARD:
			if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
				//				this->active = false;															// se pasiva el objeto
				this->actualImage = 0;
				this->state = player_IDLE;
			}
			else
			{
				al_draw_bitmap(this->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				(this->actualImage < (JUMPING_PICS - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
				this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
			}

			if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
				this->state = player_IDLE;
			}
			else
				this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
			break;
		case player_PUSHING:
			if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))
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
		case player_DYING:
			if (this->dieActualImage < DYING_PICS)
			{
				al_draw_bitmap(this->dieImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
				this->dieImages++;
			}
			else
			{
				this->dieImages = 0;
//				this->active = false;			// aca si se podria desactivar el objeto
			}
			break;
		}
	}
}

void Obj_Graf_Player::startDraw(Direction dir, void *state, POINT& pos)
{
	this->active = true;
	this->dir = dir;
	this->pos = pos;
	this->InitalPos = pos;
	this->state = * (PLAYER_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
}

void Obj_Graf_Player::destroy()
{
	delete[] walkImages;
	delete[] jumpImages;
	delete[] idleImages;
	delete[] attackImages;
	delete[] fallImages;
	delete[] pushImages;
	delete[] dieImages;
}
