#pragma once


enum class States
{
	Moving, Frozen
};
class Character
{
public:
	Character();
	~Character();

	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int id;
	States current_state;
	//Observer_dibujo
};

