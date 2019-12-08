#pragma once

#include "ImageContainer.h"
#include "general.h"
#include "Observable.h"

#define COLS (16)
#define ROWS (12)

#define JUMP_TIME (1.2)			// tiempo de salto -> 1.2s			(lo que tarda en llegar 2 bloques mas arriba)

#define MOVE_RATIO_FALL	(0.3)											// velocidad de caida (300ms/bloque)
#define VEL_FALL	(BLOCK_SIZE/(FPS*MOVE_RATIO_FALL))

enum  Direction {
	Left, Right, Up, None
};

class Obj_Graf: public Observable
{
public:
	Obj_Graf();
	~Obj_Graf();
	Obj_Graf(double ID);
	virtual void startDraw(Direction dir, void *estado, POINT_& pos) = 0;			// a startDraw lo llama el modelo del juego y le marca donde iniciar la secuencia de dibujo y en que dirección y estado
	virtual void destroy() = 0;
	virtual void draw() = 0;
	void setID(double ID);											// setea el ID
	void setPos(POINT_);
	void setPos(double x, double y);								// coordenadas del objeto en el mapa
	void setInitalPos(POINT_ pos);
	bool isActive();
	void activeObj();
	void disactiveObj();
	virtual void reset() = 0;
	virtual bool secuenceOver() = 0;
	virtual bool finished_drawing_step();
protected:
	double ID;							// identificador del objeto grafico
//	ALLEGRO_BITMAP *** images = NULL;			// triple puntero porque por el bitmap ya tenes 1 y vas a tener varios arreglos para cada estado
	unsigned int actualImage;			// te marca que posicion de arreglo estas para poder pasar a la siguiente
	Direction dir;
	POINT_ pos;
	bool active;						// el objeto garfico va a estar activo cuando se halla iniciado su secuencia de dibujo
	int velX;							// velocidad de desplazamiento horizontal (andando) (en pixeles/sec)
	int velFall;						// velocidad de caida
	POINT_ InitalPos;					// posición inicial para saber cuando detener la animación, y pasivar el objeto
	bool secuenceOver_;

	void notify_finished_drawing_step();
	bool finished_step = false;
};
