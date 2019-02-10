#pragma once

#define MOVE_RATIO	(0.3)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_X	(BLOCK_SIZE/(FPS*MOVE_RATIO))
#define MOVE_RATIO_PUSHED	(1.0)
#define VEL_PUSHED	(BLOCK_SIZE/(FPS*MOVE_RATIO_PUSHED))

#define IDLE_PICS		1
#define MOVING_PICS		1											// cantidad de imagenes de cada una para saber repetir el ciclo
#define PUSHING_PICS	1
#define FALLING_PICS	1
#define DESTRUCTION_PICS	48

#define FOLDER_BALL	("ball")

#define FOLDER_IDLE			("IDLE")
#define FOLDER_PUSHING		("PUSHING")
#define FOLDER_MOVING		("MOVING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_DESTRUCTION		("DESTRUCTION")

#define FILE_IDLE			("RainbowBall")
#define FILE_MOVING			("RainbowBall")
#define FILE_PUSHING		("RainbowBall")
#define FILE_FALLING		("RainbowBall")
#define FILE_DESTRUCTION	("Explosion 2-F")
