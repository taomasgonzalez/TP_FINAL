#pragma once

#define MOVE_RATIO	(0.05)											// segundos que le tarda al proyectil recorrer un casillero
#define VEL_X	(BLOCK_SIZE/(FPS*MOVE_RATIO))
#define MOVE_RATIO_PUSHED	(0.5)
#define VEL_PUSHED	(BLOCK_SIZE/(FPS*MOVE_RATIO_PUSHED))

#define IDLE_PICS		1
#define MOVING_PICS		10											// cantidad de imagenes de cada una para saber repetir el ciclo
#define PUSHING_PICS	10
#define FALLING_PICS	10
#define DESTRUCTION_PICS	10

#define FOLDER_BALL	("ball")

#define FOLDER_IDLE			("IDLE")
#define FOLDER_PUSHING		("PUSHING")
#define FOLDER_MOVING		("MOVING")
#define FOLDER_FALLING		("FALLING")
#define FOLDER_DESTRUCTION		("DESTRUCTION")

#define FILE_IDLE			("ball idle-F")
#define FILE_MOVING			("Sonic Running-F")
#define FILE_PUSHING		("ball pushing")
#define FILE_FALLING		("ball falling-F")
#define FILE_DESTRUCTION	("ball destruction-F")