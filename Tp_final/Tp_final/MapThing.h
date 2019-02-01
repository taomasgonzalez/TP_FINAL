#pragma once
class MapThing
{
public:
	MapThing(unsigned int id, bool is_nothing);

	~MapThing();
	
	virtual bool is_proyectile();
	virtual bool is_enemy();
	virtual bool is_player();
	
	unsigned int id;

	void set_printable(char printable);
	char get_printable();

protected:
	char printable;
};

