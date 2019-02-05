#include "GraficObjectPlayer.h"
#include <iostream>

using namespace std;


Obj_Graf_Player::Obj_Graf_Player()
{
}

Obj_Graf_Player::Obj_Graf_Player(double ID, PLAYER_TYPE type) : Obj_Graf(ID)
{
	this->velX = VELOCITY_X;					// se setea la velocidad de desplazamiento de los jugadores
	this->type = type;
	this->initialVelY = (2 * BLOCK_SIZE + (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(JUMP_TIME*FPS, 2)) / (JUMP_TIME * FPS);		// segun los calculos la velocidad inicial en px/frames es esa
	this->actualImage = 0;
	this->jumpTicks = 0;
//	this->fallTicks = 0;
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
//			this->fallTicks = 0;
			this->jumpTicks = 0;
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
//			this->fallTicks = 0;
			this->jumpTicks++;
			this->pos.set_y_coord(this->InitalPos.get_y_coord() - (this->initialVelY*this->jumpTicks - (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(jumpTicks, 2)));
			al_draw_bitmap(this->jumpImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			if (this->jumpTicks > JUMP_TIME*FPS)																						// si ya se completo la secuencia de salto se cambia el estado
				this->state = player_IDLE;
		case player_ATTACKING:
//			this->fallTicks = 0;
			this->jumpTicks = 0;
			if (this->actualImage < ATTACKING_PICS)
			{
				al_draw_bitmap(this->attackImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
				this->actualImage++;																									// termino la secuencia de disparo
			}
			else
			{
				this->actualImage = 0;
				this->state = player_IDLE;
//				this->active = false;
			}
			break;
		case player_FALLING:
			//this->fallTicks++;
			//this->jumpTicks = 0;
			//this->pos.set_y_coord(this->InitalPos.get_y_coord() + (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(fallTicks, 2));				// multiplico por (1/FPS)^2 para cambiar las unidades de la gravedad de 1/s^2 a 1/frames^2
			//al_draw_bitmap(this->fallImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);								// hago que la caida solo tenga una imagen		
			//break;
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case player_IDLE:
//			this->fallTicks = 0;
			this->jumpTicks = 0;
//			this->active = false;																										// por la dudas lo vuelvo a pasivar porque en la secuencia de caida no se desactiva por si solo
			al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja el personaje parado
			break;
		}
	}
	case Direction::Right:
	{
		switch (this->state)
		{
		case player_WALKING:
//			this->fallTicks = 0;
			this->jumpTicks = 0;
			if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))		// se desplaza a la derecha, veo si ya llego a la pos final 
			{
				this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
//				this->isActive = false;															// se pasiva el objeto
				this->state = player_IDLE;
				this->actualImage = 0;
			}
			else
			{
				al_draw_scaled_bitmap(this->walkImages[this->actualImage], 0, 0, al_get_bitmap_height(this->walkImages[this->actualImage]), al_get_bitmap_width(this->walkImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), al_get_bitmap_height(this->walkImages[this->actualImage]) / 6, al_get_bitmap_width(this->walkImages[this->actualImage]) / 6, ALLEGRO_FLIP_HORIZONTAL);
				//al_draw_bitmap(this->walkImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);		// se dibuja
				this->actualImage++;																									// ubico el siguiente frame
				if (this->actualImage >= WALKING_PICS)																					// se reinicia la secuancia de dibujo
					this->actualImage = 0;
				this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);																// muevo la posicion del dibujo
			}
			break;
		case player_JUMPING:
//			this->fallTicks = 0;
			this->jumpTicks++;
			this->pos.set_y_coord(this->InitalPos.get_y_coord() - (this->initialVelY*this->jumpTicks - (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(jumpTicks, 2)));
			al_draw_bitmap(this->jumpImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			if (this->jumpTicks > JUMP_TIME*FPS)																						// si ya se completo la secuencia de salto se cambia el estado
				this->state = player_IDLE;
			break;
		case player_ATTACKING:
//			this->fallTicks = 0;
			this->jumpTicks = 0;
			if (this->actualImage < ATTACKING_PICS)
			{
				al_draw_bitmap(this->attackImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja
				this->actualImage++;																							// termino la secuencia de disparo
			}
			else
			{
				this->actualImage = 0;
				this->state = player_IDLE;
//				this->Active = false;
			}
			break;
		case player_FALLING:
			/*this->jumpTicks = 0;
			this->fallTicks++;
			this->pos.set_y_coord(this->InitalPos.get_y_coord() + (0.5)*GRAVITY*(pow((1 / FPS), 2)) * pow(fallTicks, 2));
			al_draw_bitmap(this->fallImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);*/
			al_draw_bitmap(this->fallImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);
			(this->actualImage < FALLING_PICS) ? this->actualImage++ : this->actualImage = 0;
			break;
		case player_IDLE:
//			this->fallTicks = 0;
			this->jumpTicks = 0;
//			this->active = false;
			al_draw_bitmap(this->idleImages[0], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);			// se dibuja el personaje parado
			break;
		}
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
}
