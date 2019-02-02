#pragma once
enum class Thing_Type { PLAYER, ENEMY, PROYECTILE, FLOOR };

class MapThing
{

public:

	MapThing(unsigned int id, bool is_nothing);

	~MapThing();
	
	virtual bool is_proyectile();
	virtual bool is_enemy();
	virtual bool is_player();
	
	Thing_Type get_map_thing_type();

	unsigned int id;

	void set_printable(char printable);
	char get_printable();

	int pos_x;
	int pos_y;

protected:
	char printable;
};

