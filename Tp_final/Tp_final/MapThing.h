#pragma once
class MapThing
{
public:
	MapThing(unsigned int id);
	~MapThing();
	
	virtual bool is_proyectile();
	virtual bool is_enemy();
	virtual bool is_player();
	
	unsigned int id;
};

