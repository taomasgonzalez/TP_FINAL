#include "ImageContainer.h"

using namespace std;

ImageContainer::ImageContainer()
{
	

}
ImageContainer::~ImageContainer()
{
}
//void ImageContainer::load_enemy_bitmaps() {
//		string carpeta1;
//		string carpeta2;
//		string carpeta3;
//		string file;
//		string imageDir;
//
//
//		case FATTY:
//			carpeta1 = FOLDER_ENEMY;
//			carpeta2 = FOLDER_FATTY;
//			carpeta3 = FOLDER_WALKING;
//			file = FILE_FATTY_WALKING;
//			this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_FATTY];
//			for (int i = 0; i < WALKING_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->walkImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_JUMPING;
//			file = FILE_FATTY_JUMPING;
//			this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_FATTY];
//			for (int i = 0; i < JUMPING_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_IDLE;
//			file = FILE_FATTY_IDLE;
//			this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_FATTY];
//			for (int i = 0; i < IDLE_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->idleImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_ATTACKING;
//			file = FILE_FATTY_ATTACKING;
//			this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_FATTY];
//			for (int i = 0; i < ATTACKING_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->attackImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_FALLING;
//			file = FILE_FATTY_FALLING;
//			this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_FATTY];
//			for (int i = 0; i < FALLING_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->fallImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_TRAPPED_1;
//			file = FILE_FATTY_TRAPPED_1;
//			this->trap1Images = new ALLEGRO_BITMAP *[TRAPPED_1_PICS_FATTY];
//			for (int i = 0; i < TRAPPED_1_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->trap1Images[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_TRAPPED_2;
//			file = FILE_FATTY_TRAPPED_2;
//			this->trap1Images = new ALLEGRO_BITMAP *[TRAPPED_2_PICS_FATTY];
//			for (int i = 0; i < TRAPPED_2_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->trap2Images[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_DYING;
//			file = FILE_FATTY_DYING;
//			this->dieImages = new ALLEGRO_BITMAP *[DYING_PICS_FATTY];
//			for (int i = 0; i < DYING_PICS_FATTY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->dieImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			break;
//
//		case CRAZY:
//			carpeta1 = FOLDER_ENEMY;
//			carpeta2 = FOLDER_CRAZY;
//			carpeta3 = FOLDER_WALKING;
//			file = FILE_CRAZY_WALKING;
//			this->walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_CRAZY];
//			for (int i = 0; i < WALKING_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->walkImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_JUMPING;
//			file = FILE_CRAZY_JUMPING;
//			this->jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_CRAZY];
//			for (int i = 0; i < JUMPING_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->jumpImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_IDLE;
//			file = FILE_CRAZY_IDLE;
//			this->idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_CRAZY];
//			for (int i = 0; i < IDLE_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->idleImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_ATTACKING;
//			file = FILE_CRAZY_ATTACKING;
//			this->attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_CRAZY];
//			for (int i = 0; i < ATTACKING_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->attackImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_FALLING;
//			file = FILE_CRAZY_FALLING;
//			this->fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_CRAZY];
//			for (int i = 0; i < FALLING_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->fallImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_TRAPPED_1;
//			file = FILE_CRAZY_TRAPPED_1;
//			this->trap1Images = new ALLEGRO_BITMAP *[TRAPPED_1_PICS_CRAZY];
//			for (int i = 0; i < TRAPPED_1_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->trap1Images[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_TRAPPED_2;
//			file = FILE_CRAZY_TRAPPED_2;
//			this->trap2Images = new ALLEGRO_BITMAP *[TRAPPED_2_PICS_CRAZY];
//			for (int i = 0; i < TRAPPED_2_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->trap2Images[i] = al_load_bitmap(imageDir.c_str());
//			}
//			carpeta3 = FOLDER_DYING;
//			file = FILE_CRAZY_DYING;
//			this->dieImages = new ALLEGRO_BITMAP *[DYING_PICS_CRAZY];
//			for (int i = 0; i < DYING_PICS_CRAZY; i++)
//			{
//				imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
//				this->dieImages[i] = al_load_bitmap(imageDir.c_str());
//			}
//			break;
//		}
//
//		carpeta1 = FOLDER_BALL;
//		carpeta3 = FOLDER_IDLE_BALL;
//		file = FILE_IDLE_BALL;
//		this->inballIdleImages = new ALLEGRO_BITMAP *[IDLE_PICS_BALL];
//		for (int i = 0; i < IDLE_PICS_BALL; i++)
//		{
//			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i /* + 1*/) + ".png";			// /* + 1*/
//			this->inballIdleImages[i] = al_load_bitmap(imageDir.c_str());
//		}
//		carpeta3 = FOLDER_MOVING_BALL;
//		file = FILE_MOVING_BALL;
//		this->inballMoveImages = new ALLEGRO_BITMAP *[MOVING_PICS_BALL];
//		for (int i = 0; i < MOVING_PICS_BALL; i++)
//		{
//			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i /* + 1*/) + ".png";
//			this->inballMoveImages[i] = al_load_bitmap(imageDir.c_str());
//		}
//		carpeta3 = FOLDER_PUSHING_BALL;
//		file = FILE_PUSHING_BALL;
//		this->inballPushImages = new ALLEGRO_BITMAP *[PUSHING_PICS_BALL];
//		for (int i = 0; i < PUSHING_PICS_BALL; i++)
//		{
//			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i /* + 1*/) + ".png";
//			this->inballPushImages[i] = al_load_bitmap(imageDir.c_str());
//		}
//		carpeta3 = FOLDER_FALLING_BALL;
//		file = FILE_FALLING_BALL;
//		this->inballFallImages = new ALLEGRO_BITMAP *[FALLING_PICS_BALL];
//		for (int i = 0; i < FALLING_PICS_BALL; i++)
//		{
//			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i/* + 1*/) + ".png";
//			this->inballFallImages[i] = al_load_bitmap(imageDir.c_str());
//		}
//		carpeta3 = FOLDER_DESTRUCTION_BALL;
//		file = FILE_DESTRUCTION_BALL;  // FALTAN IMAGENES DE LOS ENEMIGOS CONGELANDOSE
//		this->inballDestructiontImages = new ALLEGRO_BITMAP *[DESTRUCTION_PICS_BALL];
//		for (int i = 0; i < DESTRUCTION_PICS_BALL; i++)
//		{
//			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i + 1) + ".png";
//			this->inballDestructiontImages[i] = al_load_bitmap(imageDir.c_str());
//		}
//	}
//}


void ImageContainer::load_purple_bitmaps() {
	std::string carpeta1 = FOLDER_ENEMY;
	std::string carpeta2 = FOLDER_PURPLE;
	std::string carpeta3 = FOLDER_WALKING;
	std::string file = FILE_PURPLE_WALKING;
	std::string imageDir;

	enemy_images curr_images = my_enemy_images.purple;
	
	curr_images.walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_PURPLE];
	for (int i = 0; i < WALKING_PICS_PURPLE; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.walkImages[i] = al_load_bitmap(imageDir.c_str());
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
	carpeta3 = FOLDER_TRAPPED_1;
	file = FILE_PURPLE_TRAPPED_1;
	this->trap1Images = new ALLEGRO_BITMAP *[TRAPPED_1_PICS_PURPLE];
	for (int i = 0; i < TRAPPED_1_PICS_PURPLE; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		this->trap1Images[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_TRAPPED_2;
	file = FILE_PURPLE_TRAPPED_2;
	this->trap2Images = new ALLEGRO_BITMAP *[TRAPPED_2_PICS_PURPLE];
	for (int i = 0; i < TRAPPED_2_PICS_PURPLE; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		this->trap2Images[i] = al_load_bitmap(imageDir.c_str());
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
}

void ImageContainer::load_fatty_bitmaps()
{
	std::string carpeta1 = FOLDER_ENEMY;
	std::string carpeta2 = FOLDER_FATTY;
	std::string carpeta3 = FOLDER_WALKING;
	std::string file = FILE_FATTY_WALKING;
	std::string imageDir;

	enemy_images curr_images = my_enemy_images.fatty;

	curr_images.walkImages = new ALLEGRO_BITMAP *[WALKING_PICS_FATTY];
	for (int i = 0; i < WALKING_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.walkImages[i] = al_load_bitmap(imageDir.c_str());
	}

	carpeta3 = FOLDER_JUMPING;
	file = FILE_FATTY_JUMPING;
	curr_images.jumpImages = new ALLEGRO_BITMAP *[JUMPING_PICS_FATTY];
	for (int i = 0; i < JUMPING_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.jumpImages[i] = al_load_bitmap(imageDir.c_str());
	}

	carpeta3 = FOLDER_IDLE;
	file = FILE_FATTY_IDLE;
	curr_images.idleImages = new ALLEGRO_BITMAP *[IDLE_PICS_FATTY];
	for (int i = 0; i < IDLE_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.idleImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_ATTACKING;
	file = FILE_FATTY_ATTACKING;
	curr_images.attackImages = new ALLEGRO_BITMAP *[ATTACKING_PICS_FATTY];
	for (int i = 0; i < ATTACKING_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.attackImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_FALLING;
	file = FILE_FATTY_FALLING;
	curr_images.fallImages = new ALLEGRO_BITMAP *[FALLING_PICS_FATTY];
	for (int i = 0; i < FALLING_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.fallImages[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_TRAPPED_1;
	file = FILE_FATTY_TRAPPED_1;
	curr_images.trap1Images = new ALLEGRO_BITMAP *[TRAPPED_1_PICS_FATTY];
	for (int i = 0; i < TRAPPED_1_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.trap1Images[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_TRAPPED_2;
	file = FILE_FATTY_TRAPPED_2;
	curr_images.trap2Images = new ALLEGRO_BITMAP *[TRAPPED_2_PICS_FATTY];
	for (int i = 0; i < TRAPPED_2_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.trap2Images[i] = al_load_bitmap(imageDir.c_str());
	}
	carpeta3 = FOLDER_DYING;
	file = FILE_FATTY_DYING;
	curr_images.dieImages = new ALLEGRO_BITMAP *[DYING_PICS_FATTY];
	for (int i = 0; i < DYING_PICS_FATTY; i++)
	{
		imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		curr_images.dieImages[i] = al_load_bitmap(imageDir.c_str());
	}
}

void ImageContainer::load_crazy_bitmaps()
{
}
void ImageContainer::load_projectile_bitmaps()
{
}
void ImageContainer::load_snowball_bitmaps()
{
}
void ImageContainer::load_fire_bitmaps()
{
}
void ImageContainer::load_character_bitmaps()
{
}
void ImageContainer::load_tom_bitmaps()
{

}
void ImageContainer::load_nick_bitmaps()
{
}
