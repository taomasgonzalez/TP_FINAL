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
	unsigned int iddle_pics;
	unsigned int attacking_pics;
	unsigned int falling_pics;
	unsigned int dying_pics;

	unsigned int jump_ticks;		//ticks to manage the MRUV of the jumps
	unsigned int fall_ticks;		//ticks to manage the MRUV of the falls

	unsigned int idleActualImage;
	unsigned int attackActualImage;
	unsigned int dieActualImage;
	unsigned int walkActualImage;


	void handle_walking();
	void handle_jumping();
	void handle_jumping_forward();
	void handle_iddle();
	void handle_attacking();
	void handle_falling();
	void handle_dying();

	void stop_fall_aceleration();	//this function will be call in each draw() call, it controls the variables for a more dinamic drawing

	int get_movement_delta();
	bool notified_half_jump = false;

	ImageContainer::character_images * chara_images = NULL;
	AudioContainer::character_samples * chara_samples = NULL;

	ALLEGRO_SAMPLE_ID* walking_sample_id;

	//debug
	int counter = 0;
};

