#pragma once
#include "Observer.h"
#include "Scene.h"
#include "Userdata.h"

class Drawer
{
public:
	Drawer();
	~Drawer();

	//graphical_objects
	void draw(Scene * scenario);
};

