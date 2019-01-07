#pragma once
#include "Observer.h"
#include "Scene.h"


class Drawer: public Observer
{
public:
	Drawer();
	~Drawer();

	void update();

private:

	//graphical_objects
	void draw(Scene * scenario);
	
};

