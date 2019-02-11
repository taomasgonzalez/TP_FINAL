#pragma once

#define MOVE_RATIO	(0.3)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_X	(BLOCK_SIZE/(FPS*MOVE_RATIO))
#define MOVE_RATIO_PUSHED	(1.0)
#define VEL_PUSHED	(BLOCK_SIZE/(FPS*MOVE_RATIO_PUSHED))

#define IDLE_PICS		1
#define MOVING_PICS		16											// cantidad de imagenes de cada una para saber repetir el ciclo
#define PUSHING_PICS	16
#define FALLING_PICS	16
#define DESTRUCTION_PICS	18

#define FOLDER_BALL	("ball")

#define FOLDER_IDLE			("IDLE")
#define FOLDER_PUSHING		("PUSHING")
#define FOLDER_MOVING		("MOVING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_DESTRUCTION		("DESTRUCTION")

#define FILE_IDLE			("tile00")
#define FILE_MOVING			("tile00")
#define FILE_PUSHING		("tile00")
#define FILE_FALLING		("tile00")
#define FILE_DESTRUCTION	("Blue Ring Explosion")