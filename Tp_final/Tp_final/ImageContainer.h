#pragma once
#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
//#include <allegro5\>
#include "point.h"
#include <string>
#include <math.h>				/* pow */
#include <iostream>
#include "EnemyDefines.h"
#include "PlayerDefines.h"
#include "ProjectileDefine.h"
#include <vector>

class ImageContainer
{
public:
	ImageContainer();
	~ImageContainer();

	typedef struct enemy_images {
		ALLEGRO_BITMAP ** attackImages = NULL;
		ALLEGRO_BITMAP ** walkImages = NULL;
		ALLEGRO_BITMAP ** jumpImages = NULL;
		ALLEGRO_BITMAP ** idleImages = NULL;
		ALLEGRO_BITMAP ** fallImages = NULL;
		ALLEGRO_BITMAP ** trap1Images = NULL;
		ALLEGRO_BITMAP ** trap2Images = NULL;
		ALLEGRO_BITMAP ** dieImages = NULL;

		//ball images
		ALLEGRO_BITMAP ** inballIdleImages = NULL;
		ALLEGRO_BITMAP ** inballMoveImages = NULL;
		ALLEGRO_BITMAP ** inballPushImages = NULL;
		ALLEGRO_BITMAP ** inballFallImages = NULL;
		ALLEGRO_BITMAP ** inballDestructiontImages = NULL;
	}enemy_images;

	typedef struct enemies_images_container {
		enemy_images purple;
		enemy_images crazy;
		enemy_images fatty;
	} enemies_images_container;

	enemies_images_container my_enemy_images_container;

	typedef struct character_images {
		ALLEGRO_BITMAP ** walkImages = NULL;
		ALLEGRO_BITMAP ** jumpImages = NULL;
		ALLEGRO_BITMAP ** idleImages = NULL;
		ALLEGRO_BITMAP ** attackImages = NULL;
		ALLEGRO_BITMAP ** fallImages = NULL;
		ALLEGRO_BITMAP ** pushImages = NULL;
		ALLEGRO_BITMAP ** dieImages = NULL;
	} character_images;

	typedef struct character_images_container {
		character_images tom;
		character_images nick;
	} character_images_container;
	character_images_container my_character_images_container;

	typedef struct projectile_images {
		ALLEGRO_BITMAP ** moveImages = NULL;
		ALLEGRO_BITMAP ** decayImages = NULL;
		ALLEGRO_BITMAP ** impactImages = NULL;
		ALLEGRO_BITMAP ** fallImages = NULL;
	}projectile_images;

	typedef struct projectile_images_container {
		projectile_images snowball;
		projectile_images fire;
	}projectile_images_container ;

	projectile_images_container my_projectile_images_container;

private:
	//enemy bitmaps
	void load_enemy_bitmaps();
	void load_purple_bitmaps();
	void load_fatty_bitmaps();
	void load_crazy_bitmaps();

	//projectile bitmaps
	void load_projectile_bitmaps();
	void load_snowball_bitmaps();
	void load_fire_bitmaps();

	//character bitmaps
	void load_character_bitmaps();
	void load_tom_bitmaps();
	void load_nick_bitmaps();

	void fill_bitmap(ALLEGRO_BITMAP *** curr_images, std::string carpeta1, std::string carpeta3, std::string file, int limit, std::string carpeta2 = "");

};