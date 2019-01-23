#pragma once
#include "Observer.h"
#include "Scene.h"


class Drawer: 
{
public:
	Drawer();
	~Drawer();

	//graphical_objects
	void draw(Scene * scenario);

	
};

