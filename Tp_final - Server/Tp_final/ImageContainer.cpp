#include "ImageContainer.h"

using namespace std;

ImageContainer::ImageContainer()
{
	load_enemy_bitmaps();
	load_projectile_bitmaps();
	load_character_bitmaps();
}
ImageContainer::~ImageContainer()
{
	destroy_all_bitmaps();
}
void ImageContainer::load_enemy_bitmaps() {

		load_crazy_bitmaps();
		load_fatty_bitmaps();
		load_purple_bitmaps();
}


void ImageContainer::load_purple_bitmaps() {

	fill_bitmap(&my_enemy_images_container.purple.walkImages, FOLDER_ENEMY, FOLDER_WALKING, FILE_PURPLE_WALKING, WALKING_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.jumpImages, FOLDER_ENEMY, FOLDER_JUMPING, FILE_PURPLE_JUMPING, JUMPING_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.idleImages, FOLDER_ENEMY, FOLDER_IDLE, FILE_PURPLE_IDLE, IDLE_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.attackImages, FOLDER_ENEMY, FOLDER_ATTACKING, FILE_PURPLE_ATTACKING, ATTACKING_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.fallImages, FOLDER_ENEMY, FOLDER_FALLING, FILE_PURPLE_FALLING, FALLING_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.trap1Images, FOLDER_ENEMY, FOLDER_TRAPPED_1, FILE_PURPLE_TRAPPED_1, TRAPPED_1_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.trap2Images, FOLDER_ENEMY, FOLDER_TRAPPED_2, FILE_PURPLE_TRAPPED_2, TRAPPED_2_PICS_PURPLE, FOLDER_PURPLE);
	fill_bitmap(&my_enemy_images_container.purple.dieImages, FOLDER_ENEMY, FOLDER_DYING, FILE_PURPLE_DYING, DYING_PICS_PURPLE, FOLDER_PURPLE);

	// se cargan las imagenes de los enemigos en la bola
	fill_bitmap(&my_enemy_images_container.purple.inballIdleImages, FOLDER_BALL, FOLDER_IDLE_BALL, FILE_IDLE_BALL, IDLE_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.purple.inballMoveImages, FOLDER_BALL, FOLDER_MOVING_BALL, FILE_MOVING_BALL, MOVING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.purple.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.purple.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.purple.inballFallImages, FOLDER_BALL, FOLDER_FALLING_BALL, FILE_FALLING_BALL, FALLING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.purple.inballDestructiontImages, FOLDER_BALL, FOLDER_DESTRUCTION_BALL, FILE_DESTRUCTION_BALL, DESTRUCTION_PICS_BALL);
}

void ImageContainer::load_fatty_bitmaps()
{
	fill_bitmap(&my_enemy_images_container.fatty.walkImages, FOLDER_ENEMY, FOLDER_WALKING, FILE_FATTY_WALKING, WALKING_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.jumpImages, FOLDER_ENEMY, FOLDER_JUMPING, FILE_FATTY_JUMPING, JUMPING_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.idleImages, FOLDER_ENEMY, FOLDER_IDLE, FILE_FATTY_IDLE, IDLE_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.attackImages, FOLDER_ENEMY, FOLDER_ATTACKING, FILE_FATTY_ATTACKING, ATTACKING_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.fallImages, FOLDER_ENEMY, FOLDER_FALLING, FILE_FATTY_FALLING, FALLING_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.trap1Images, FOLDER_ENEMY, FOLDER_TRAPPED_1, FILE_FATTY_TRAPPED_1, TRAPPED_1_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.trap2Images, FOLDER_ENEMY, FOLDER_TRAPPED_2, FILE_FATTY_TRAPPED_2, TRAPPED_2_PICS_FATTY, FOLDER_FATTY);
	fill_bitmap(&my_enemy_images_container.fatty.dieImages, FOLDER_ENEMY, FOLDER_DYING, FILE_FATTY_DYING, DYING_PICS_FATTY, FOLDER_FATTY);

	// se cargan las imagenes de los enemigos en la bola
	fill_bitmap(&my_enemy_images_container.fatty.inballIdleImages, FOLDER_BALL, FOLDER_IDLE_BALL, FILE_IDLE_BALL, IDLE_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.fatty.inballMoveImages, FOLDER_BALL, FOLDER_MOVING_BALL, FILE_MOVING_BALL, MOVING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.fatty.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.fatty.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.fatty.inballFallImages, FOLDER_BALL, FOLDER_FALLING_BALL, FILE_FALLING_BALL, FALLING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.fatty.inballDestructiontImages, FOLDER_BALL, FOLDER_DESTRUCTION_BALL, FILE_DESTRUCTION_BALL, DESTRUCTION_PICS_BALL);
}

void ImageContainer::load_crazy_bitmaps()
{
	fill_bitmap(&my_enemy_images_container.crazy.walkImages, FOLDER_ENEMY, FOLDER_WALKING, FILE_CRAZY_WALKING, WALKING_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.jumpImages, FOLDER_ENEMY, FOLDER_JUMPING, FILE_CRAZY_JUMPING, JUMPING_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.idleImages, FOLDER_ENEMY, FOLDER_IDLE, FILE_CRAZY_IDLE, IDLE_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.attackImages, FOLDER_ENEMY, FOLDER_ATTACKING, FILE_CRAZY_ATTACKING, ATTACKING_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.fallImages, FOLDER_ENEMY, FOLDER_FALLING, FILE_CRAZY_FALLING, FALLING_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.trap1Images, FOLDER_ENEMY, FOLDER_TRAPPED_1, FILE_CRAZY_TRAPPED_1, TRAPPED_1_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.trap2Images, FOLDER_ENEMY, FOLDER_TRAPPED_2, FILE_CRAZY_TRAPPED_2, TRAPPED_2_PICS_CRAZY, FOLDER_CRAZY);
	fill_bitmap(&my_enemy_images_container.crazy.dieImages, FOLDER_ENEMY, FOLDER_DYING, FILE_CRAZY_DYING, DYING_PICS_CRAZY, FOLDER_CRAZY);

	// se cargan las imagenes de los enemigos en la bola
	fill_bitmap(&my_enemy_images_container.crazy.inballIdleImages, FOLDER_BALL, FOLDER_IDLE_BALL, FILE_IDLE_BALL, IDLE_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.crazy.inballMoveImages, FOLDER_BALL, FOLDER_MOVING_BALL, FILE_MOVING_BALL, MOVING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.crazy.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.crazy.inballPushImages, FOLDER_BALL, FOLDER_PUSHING_BALL, FILE_PUSHING_BALL, PUSHING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.crazy.inballFallImages, FOLDER_BALL, FOLDER_FALLING_BALL, FILE_FALLING_BALL, FALLING_PICS_BALL);
	fill_bitmap(&my_enemy_images_container.crazy.inballDestructiontImages, FOLDER_BALL, FOLDER_DESTRUCTION_BALL, FILE_DESTRUCTION_BALL, DESTRUCTION_PICS_BALL);
}

void ImageContainer::load_projectile_bitmaps()
{
	load_fire_bitmaps();
	load_snowball_bitmaps();
}

void ImageContainer::load_snowball_bitmaps()
{
	fill_bitmap(&my_projectile_images_container.snowball.moveImages, FOLDER_PROYECTILES, FOLDER_MOVING, FILE_SNOW_MOVING, MOVING_PICS_SNOW, FOLDER_SNOW);
	fill_bitmap(&my_projectile_images_container.snowball.decayImages, FOLDER_PROYECTILES, FOLDER_DECAYING, FILE_SNOW_DECAYING, DECAYING_PICS_SNOW, FOLDER_SNOW);
	fill_bitmap(&my_projectile_images_container.snowball.impactImages, FOLDER_PROYECTILES, FOLDER_IMPACT, FILE_SNOW_IMPACT, IMPACT_PICS_SNOW, FOLDER_SNOW);
	fill_bitmap(&my_projectile_images_container.snowball.fallImages, FOLDER_PROYECTILES, FOLDER_FALLING, FILE_SNOW_FALLING, FALLING_PICS_SNOW, FOLDER_SNOW);
}

void ImageContainer::load_fire_bitmaps()
{
	fill_bitmap(&my_projectile_images_container.fire.moveImages, FOLDER_PROYECTILES, FOLDER_MOVING, FILE_FIRE_MOVING, MOVING_PICS_FIRE, FOLDER_FIRE);
	fill_bitmap(&my_projectile_images_container.fire.decayImages, FOLDER_PROYECTILES, FOLDER_DECAYING, FILE_FIRE_DECAYING, DECAYING_PICS_FIRE, FOLDER_FIRE);
	fill_bitmap(&my_projectile_images_container.fire.impactImages, FOLDER_PROYECTILES, FOLDER_IMPACT, FILE_FIRE_IMPACT, IMPACT_PICS_FIRE, FOLDER_FIRE);
	fill_bitmap(&my_projectile_images_container.fire.fallImages, FOLDER_PROYECTILES, FOLDER_FALLING, FILE_FIRE_FALLING, FALLING_PICS_FIRE, FOLDER_FIRE);
}

void ImageContainer::load_character_bitmaps()
{
	load_tom_bitmaps();
	load_nick_bitmaps();
}
void ImageContainer::load_tom_bitmaps()
{
	fill_bitmap(&my_character_images_container.tom.walkImages, FOLDER_CHARA, FOLDER_WALKING, FILE_TOM_WALKING, WALKING_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.jumpImages, FOLDER_CHARA, FOLDER_JUMPING, FILE_TOM_JUMPING, JUMPING_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.idleImages, FOLDER_CHARA, FOLDER_IDLE, FILE_TOM_IDLE, IDLE_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.attackImages, FOLDER_CHARA, FOLDER_ATTACKING, FILE_TOM_ATTACKING, ATTACKING_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.fallImages, FOLDER_CHARA, FOLDER_FALLING, FILE_TOM_FALLING, FALLING_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.pushImages, FOLDER_CHARA, FOLDER_PUSHING, FILE_TOM_PUSHING, PUSHING_PICS, FOLDER_TOM);
	fill_bitmap(&my_character_images_container.tom.dieImages, FOLDER_CHARA, FOLDER_DYING, FILE_TOM_DYING, DYING_PICS, FOLDER_TOM);

}
void ImageContainer::load_nick_bitmaps()
{
	fill_bitmap(&my_character_images_container.nick.walkImages, FOLDER_CHARA, FOLDER_WALKING, FILE_NICK_WALKING, WALKING_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.jumpImages, FOLDER_CHARA, FOLDER_JUMPING, FILE_NICK_JUMPING, JUMPING_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.idleImages, FOLDER_CHARA, FOLDER_IDLE, FILE_NICK_IDLE, IDLE_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.attackImages, FOLDER_CHARA, FOLDER_ATTACKING, FILE_NICK_ATTACKING, ATTACKING_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.fallImages, FOLDER_CHARA, FOLDER_FALLING, FILE_NICK_FALLING, FALLING_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.pushImages, FOLDER_CHARA, FOLDER_PUSHING, FILE_NICK_PUSHING, PUSHING_PICS, FOLDER_NICK);
	fill_bitmap(&my_character_images_container.nick.dieImages, FOLDER_CHARA, FOLDER_DYING, FILE_NICK_DYING, DYING_PICS, FOLDER_NICK);
}

void ImageContainer::fill_bitmap(ALLEGRO_BITMAP *** curr_images, std::string carpeta1, std::string carpeta3, std::string file, int limit, std::string carpeta2){
	string imageDir;

	*curr_images = new ALLEGRO_BITMAP *[limit];

	for (int i = 0; i < limit; i++){
		if (carpeta2 == "")
			imageDir = carpeta1 + '/' + carpeta3 + '/' + file + to_string(i /* + 1*/) + ".png";
		else
			imageDir = carpeta1 + '/' + carpeta2 + '/' + carpeta3 + '/' + file + to_string(i /*+ 1*/) + ".png";
		(*curr_images)[i] = al_load_bitmap(imageDir.c_str());
	}
}

void ImageContainer::destroy_enemy_bitmaps()
{
	// delete purple
	delete[] my_enemy_images_container.purple.attackImages;
	delete[] my_enemy_images_container.purple.dieImages;
	delete[] my_enemy_images_container.purple.fallImages;
	delete[] my_enemy_images_container.purple.idleImages;
	delete[] my_enemy_images_container.purple.inballDestructiontImages;
	delete[] my_enemy_images_container.purple.inballFallImages;
	delete[] my_enemy_images_container.purple.inballIdleImages;
	delete[] my_enemy_images_container.purple.inballMoveImages;
	delete[] my_enemy_images_container.purple.inballPushImages;
	delete[] my_enemy_images_container.purple.jumpImages;
	delete[] my_enemy_images_container.purple.trap1Images;
	delete[] my_enemy_images_container.purple.trap2Images;
	delete[] my_enemy_images_container.purple.walkImages;


	// delete fatty
	delete[] my_enemy_images_container.fatty.attackImages;
	delete[] my_enemy_images_container.fatty.dieImages;
	delete[] my_enemy_images_container.fatty.fallImages;
	delete[] my_enemy_images_container.fatty.idleImages;
	delete[] my_enemy_images_container.fatty.inballDestructiontImages;
	delete[] my_enemy_images_container.fatty.inballFallImages;
	delete[] my_enemy_images_container.fatty.inballIdleImages;
	delete[] my_enemy_images_container.fatty.inballMoveImages;
	delete[] my_enemy_images_container.fatty.inballPushImages;
	delete[] my_enemy_images_container.fatty.jumpImages;
	delete[] my_enemy_images_container.fatty.trap1Images;
	delete[] my_enemy_images_container.fatty.trap2Images;
	delete[] my_enemy_images_container.fatty.walkImages;


	// delete crazy
	delete[] my_enemy_images_container.crazy.attackImages;
	delete[] my_enemy_images_container.crazy.dieImages;
	delete[] my_enemy_images_container.crazy.fallImages;
	delete[] my_enemy_images_container.crazy.idleImages;
	delete[] my_enemy_images_container.crazy.inballDestructiontImages;
	delete[] my_enemy_images_container.crazy.inballFallImages;
	delete[] my_enemy_images_container.crazy.inballIdleImages;
	delete[] my_enemy_images_container.crazy.inballMoveImages;
	delete[] my_enemy_images_container.crazy.inballPushImages;
	delete[] my_enemy_images_container.crazy.jumpImages;
	delete[] my_enemy_images_container.crazy.trap1Images;
	delete[] my_enemy_images_container.crazy.trap2Images;
	delete[] my_enemy_images_container.crazy.walkImages;
}

void ImageContainer::destroy_projectile_bitmaps()
{
	// delete snow
	delete[] my_projectile_images_container.snowball.decayImages;
	delete[] my_projectile_images_container.snowball.fallImages;
	delete[] my_projectile_images_container.snowball.impactImages;
	delete[] my_projectile_images_container.snowball.moveImages;


	// delete fire
	delete[] my_projectile_images_container.fire.decayImages;
	delete[] my_projectile_images_container.fire.fallImages;
	delete[] my_projectile_images_container.fire.impactImages;
	delete[] my_projectile_images_container.fire.moveImages;
}

void ImageContainer::destroy_character_bitmaps()
{
	//delete tom
	delete[] my_character_images_container.tom.attackImages;
	delete[] my_character_images_container.tom.dieImages;
	delete[] my_character_images_container.tom.fallImages;
	delete[] my_character_images_container.tom.idleImages;
	delete[] my_character_images_container.tom.jumpImages;
	delete[] my_character_images_container.tom.pushImages;
	delete[] my_character_images_container.tom.walkImages;


	//delete nick
	delete[] my_character_images_container.nick.attackImages;
	delete[] my_character_images_container.nick.dieImages;
	delete[] my_character_images_container.nick.fallImages;
	delete[] my_character_images_container.nick.idleImages;
	delete[] my_character_images_container.nick.jumpImages;
	delete[] my_character_images_container.nick.pushImages;
	delete[] my_character_images_container.nick.walkImages;
}

void ImageContainer::destroy_all_bitmaps()
{
	destroy_character_bitmaps();
	destroy_enemy_bitmaps();
	destroy_projectile_bitmaps();
}