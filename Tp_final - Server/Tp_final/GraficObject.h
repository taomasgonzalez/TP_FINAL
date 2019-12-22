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

class Obj_Graf : public Observable
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
	bool half_way_jumped();
	virtual bool finished_drawing_step();

protected:
	double ID;							// identificador del objeto grafico
	unsigned int actualImage;			// te marca que posicion de arreglo estas para poder pasar a la siguiente
	Direction dir;
	POINT_ pos;
	bool active;						// el objeto garfico va a estar activo cuando se halla iniciado su secuencia de dibujo
	float velX;							// velocidad de desplazamiento horizontal (andando) (en pixeles/sec)
	float velFall;						// velocidad de caida
	POINT_ InitalPos;					// posición inicial para saber cuando detener la animación, y pasivar el objeto
	bool secuenceOver_;
	bool half_way_jumped_;					// Esta variable indica cuando se llego a la mitad de un salto (cuando se desplazo de un bloque al siguiete), en caso que el objeto pueda saltar, en su defecto estara siempre en false

	void notify_finished_drawing_step();
	bool finished_step = false;
};