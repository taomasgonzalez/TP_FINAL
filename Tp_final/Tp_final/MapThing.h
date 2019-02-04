#pragma once

enum class Item_type {
	TOM = 'T', NICK = 'N', PURPLE_GUY = 'P', GREEN_FATTIE = 'G', CRAZY = 'C', FLOOR = 'F', NADA = 'E', FIREBALL='B', SNOWBALL = 'S'
};

enum class Thing_Type { PLAYER, ENEMY, PROYECTILE, FLOOR };

enum class Sense_type {
	Right, Left, None
};


class MapThing
{

public:

	MapThing(unsigned int id, bool is_nothing, Sense_type sense);

	~MapThing();
	
	virtual bool is_proyectile();
	virtual bool is_enemy();
	virtual bool is_player();
	virtual bool is_floor();
	
	Thing_Type get_map_thing_type();

	unsigned int id;

	void set_printable(Item_type printable);
	Item_type get_printable();
	void set_sense(Sense_type sense);
	Sense_type get_sense();

	int pos_x;
	int pos_y;

protected:
	Item_type printable;
	Sense_type my_sense;
};

