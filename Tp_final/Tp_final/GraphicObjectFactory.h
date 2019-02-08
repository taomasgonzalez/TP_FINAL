#pragma once
#include "GraficObject.h" 
#include "Userdata.h"
#include "GraficObjectProjectile.h"
#include "GraficObjectEnemy.h"
#include "GraficObjectPlayer.h"
#include "GraficObjectBall.h"
class GraphicObjectFactory
{
public:
	GraphicObjectFactory();
	~GraphicObjectFactory();

	Obj_Graf * create_graphic_object(Item_type identifyer, unsigned int id);

};

