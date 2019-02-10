#pragma once
#include <allegro5/allegro5.h> 
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> 
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "point.h"
#include <string>
#include <math.h>				/* pow */
#include <iostream>

#define COLS (16)
#define ROWS (12)

#define FPS (50.0)

#define BLOCK_SIZE (50)		// pixeles en X e Y que tiene un bloque de pantalla

#define JUMP_TIME (1.2)			// tiempo de salto -> 1.2s			(lo que tarda en llegar 2 bloques mas arriba)

#define MOVE_RATIO_FALL	(0.3)											// velocidad de caida (300ms/bloque)
#define VEL_FALL	(BLOCK_SIZE/(FPS*MOVE_RATIO_FALL))

enum  Direction {
	Left, Right, Up
};

class Obj_Graf
{
public:
	Obj_Graf();
	~Obj_Graf();
	Obj_Graf(double ID);
	virtual void startDraw(Direction dir, void *estado, POINT& pos) = 0;			// a startDraw lo llama el modelo del juego y le marca donde iniciar la secuencia de dibujo y en que dirección y estado
	virtual void destroy() = 0;
	virtual void draw() = 0;
	void setID(double ID);											// setea el ID
	void setPos(POINT);
	void setPos(double x, double y);								// coordenadas del objeto en el mapa
	void setInitalPos(POINT pos);
	bool isActive();
	virtual void reset() = 0;
	virtual bool secuenceOver() = 0;

protected:
	double ID;							// identificador del objeto grafico
//	ALLEGRO_BITMAP *** images = NULL;			// triple puntero porque por el bitmap ya tenes 1 y vas a tener varios arreglos para cada estado
	unsigned int actualImage;			// te marca que posicion de arreglo estas para poder pasar a la siguiente
	Direction dir;
	POINT pos;
	bool active;						// el objeto garfico va a estar activo cuando se halla iniciado su secuencia de dibujo
	int velX;							// velocidad de desplazamiento horizontal (andando) (en pixeles/sec)
	int velFall;						// velocidad de caida
	POINT InitalPos;					// posición inicial para saber cuando detener la animación, y pasivar el objeto
	bool secuenceOver_;
};