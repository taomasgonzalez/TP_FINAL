#pragma once

#define MOVE_RATIO_FIRE	(0.1)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_FIRE	(BLOCK_SIZE/(FPS*MOVE_RATIO_FIRE))
#define MOVE_RATIO_SNOW	(0.1)
#define VEL_SNOW	(BLOCK_SIZE/(FPS*MOVE_RATIO_SNOW))

#define MOVING_PICS_SNOW	1											// cantidad de imagenes de cada una para saber repetir el ciclo
#define MOVING_PICS_FIRE	34
#define DECAYING_PICS_SNOW	1
#define DECAYING_PICS_FIRE	16
#define IMPACT_PICS_SNOW	48
#define IMPACT_PICS_FIRE	48
#define FALLING_PICS_SNOW	1
#define FALLING_PICS_FIRE	1

#define FOLDER_PROYECTILES	("proyectiles")
#define FOLDER_SNOW			("SNOW")
#define FOLDER_FIRE			("FIRE")

#define FOLDER_MOVING		("MOVING")
#define FOLDER_DECAYING		("DECAYING")
#define FOLDER_IMPACT		("IMPACT")
#define FOLDER_FALLING		("FALLING")

#define FILE_SNOW_MOVING	("slash")
#define FILE_SNOW_DECAYING	("slash")
#define FILE_SNOW_IMPACT	("Explosion 2-F")
#define FILE_SNOW_FALLING	("slash")
#define FILE_FIRE_MOVING	("efecto_fuego_000")
#define FILE_FIRE_DECAYING	("efecto_fuego_00")
#define FILE_FIRE_IMPACT	("Explosion 2-F")
#define FILE_FIRE_FALLING	("efecto_fuego_00")