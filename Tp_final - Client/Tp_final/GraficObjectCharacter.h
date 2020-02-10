#pragma once
#include "GraficObject.h"

class Obj_Graf_Character : public Obj_Graf
{
public:
	Obj_Graf_Character();
	~Obj_Graf_Character();

protected:

	unsigned int walking_pics;
	unsigned int jumping_pics;
	unsigned int jumping_forw_pics;
	unsigned int idle_pics;
	unsigned int attacking_pics;
	unsigned int falling_pics;
	unsigned int dying_pics;

	unsigned int idleActualImage;
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	unsigned int walkActualImage;

	void handle_walking();
	void handle_jumping();
	void handle_jumping_forward();
	void handle_idle();
	void handle_attacking();
	void handle_falling();
	void handle_dying();

	int get_movement_delta();
	bool notified_half_jump = false;

	ImageContainer::character_images * chara_images = NULL;
	bool is_fatty;												// Las imagenes de fatty estan espejadas (caso especial)
};

