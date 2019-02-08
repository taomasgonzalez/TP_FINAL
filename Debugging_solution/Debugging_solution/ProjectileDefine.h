#pragma once

#define MOVE_RATIO_FIRE	(0.1)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_FIRE	(BLOCK_SIZE/(FPS*MOVE_RATIO_FIRE))
#define MOVE_RATIO_SNOW	(0.1)
#define VEL_SNOW	(BLOCK_SIZE/(FPS*MOVE_RATIO_SNOW))
#define MOVE_RATIO_BALL	(0.05)
#define VEL_BALL	(BLOCK_SIZE/(FPS*MOVE_RATIO_SNOW))

#define MOVING_PICS_SNOW	10											// cantidad de imagenes de cada una para saber repetir el ciclo
#define MOVING_PICS_FIRE	1
#define DECAYING_PICS_SNOW	1
#define DECAYING_PICS_FIRE	1
#define IMPACT_PICS_SNOW	48
#define IMPACT_PICS_FIRE	10

#define FOLDER_PROYECTILES	("proyectiles")
#define FOLDER_SNOW			("SNOW")
#define FOLDER_FIRE			("FIRE")

#define FOLDER_MOVING		("MOVING")
#define FOLDER_DECAYING		("DECAYING")
#define FOLDER_IMPACT		("IMPACT")

#define FILE_SNOW_MOVING	("Sonic Running-F")
#define FILE_SNOW_DECAYING	("Cat Running-F")
#define FILE_SNOW_IMPACT	("Explosion 2-F")
#define FILE_FIRE_MOVING	("fire move-F")
#define FILE_FIRE_DECAYING	("fire decay-F")
#define FILE_FIRE_IMPACT	("fire impact-F")