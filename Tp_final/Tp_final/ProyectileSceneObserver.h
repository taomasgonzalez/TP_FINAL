#pragma once
#include "Scene.h"

class ProyectileSceneObserver 
{
public:
	ProyectileSceneObserver(Proyectile* proy, Scene * scenario);
	~ProyectileSceneObserver();
protected:
	Proyectile * proy = NULL;
private:
	Scene * scenario = NULL;
};

