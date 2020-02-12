#include "GraficObjectProjectile.h"

using namespace std;

Obj_Graf_Projectile::Obj_Graf_Projectile()
{
}


Obj_Graf_Projectile::Obj_Graf_Projectile(double ID, PROYECTILE_TYPE type, ImageContainer* imageContainer, AudioContainer* audioContainer) : Obj_Graf(ID)
{
	actualImage = 0;
	actualImpactImage = 0;
	actualDecayImage = 0;
	this->type = type;
	switch (type)
	{
	case SNOW:
		velX = VEL_SNOW;
		images = &imageContainer->my_projectile_images_container.snowball;
		samples = &audioContainer->my_proyectile_samples_container.snow;
		break;
	case FIRE:
		velX = VEL_FIRE;
		images = &imageContainer->my_projectile_images_container.fire;
		samples = &audioContainer->my_proyectile_samples_container.fire;
		break;
	}

//	al_play_sample(samples->move_soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);	//the move SE will be play right when the object is created
}																						//being asumed that the will be moving when created

Obj_Graf_Projectile::~Obj_Graf_Projectile()
{
}

void Obj_Graf_Projectile::draw()
{
	switch (state) {
	case proy_MOVING:
		handle_moving(type);			//checked
		break;
	case proy_DECAYING:
		handle_decaying(type);
		break;
	case proy_IMPACT:
		handle_impacting(type);
		break;
	case proy_FALLING:
		handle_falling(type);			//checked
		break;
	}
}


void Obj_Graf_Projectile::startDraw(Direction dir, void *state, POINT_& pos)
{
	active = true;
	if (dir != Direction::None)
		this->dir = dir;
	this->pos = pos;
	InitalPos = pos;
	this->state = *(PROYECTILE_STATE *)state;
	actualImage = 0;			// comienza con la primera imagen
	secuenceOver_ = false;
}

void Obj_Graf_Projectile::destroy()
{
	this->~Obj_Graf_Projectile();
}

void Obj_Graf_Projectile::reset()
{
	actualImage = 0;
	actualDecayImage = 0;
	actualImpactImage = 0;
}

bool Obj_Graf_Projectile::secuenceOver()
{
	return this->secuenceOver_;
}

void Obj_Graf_Projectile::handle_moving(PROYECTILE_TYPE type)
{
	unsigned int pics_quantity;
	switch (type)
	{
	case SNOW:
		pics_quantity = MOVING_PICS_SNOW;
		break;
	case FIRE:
		pics_quantity = MOVING_PICS_FIRE;
		break;
	}

	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);


	if (reached_final_pos)
	{
		if (!secuenceOver_) {
			secuenceOver_ = true;
			notify_finished_drawing_step();
			pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
			active = false;															// se pasiva el objeto
			actualImage = 0;
		}
	}
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX);	// muevo la posicion del dibujo

	//should flip the image when going left
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->moveImages[this->actualImage], 0, 0, al_get_bitmap_width(images->moveImages[this->actualImage]), al_get_bitmap_height(images->moveImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

	// se pasa al siguiente sprite
	((actualImage + 1) <  pics_quantity) ? actualImage++ : actualImage = 0;
}

void Obj_Graf_Projectile::handle_falling(PROYECTILE_TYPE type)
{
	unsigned int pics_quantity;
	switch (type)
	{
	case SNOW:
		pics_quantity = FALLING_PICS_SNOW;
		break;
	case FIRE:
		pics_quantity = FALLING_PICS_FIRE;
		break;
	}

	if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		this->secuenceOver_ = true;
		this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
		this->actualImage = 0;
	}
	else
	{
		(this->actualImage < (pics_quantity - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
		this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
	}
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(images->fallImages[this->actualImage]), al_get_bitmap_height(images->fallImages[this->actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}

void Obj_Graf_Projectile::handle_decaying(PROYECTILE_TYPE type)
{
	unsigned int pics_quantity;
	switch (type)
	{
	case SNOW:
		pics_quantity = DECAYING_PICS_SNOW;
		break;
	case FIRE:
		pics_quantity = DECAYING_PICS_FIRE;
		break;
	}

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	if (this->actualDecayImage < pics_quantity)
	{
		al_draw_scaled_bitmap(images->decayImages[this->actualDecayImage], 0, 0, al_get_bitmap_width(images->decayImages[this->actualDecayImage]), al_get_bitmap_height(images->decayImages[this->actualDecayImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		this->actualDecayImage++;																									// termino la secuencia de disparo
	}
	else
	{
		this->secuenceOver_ = true;
		this->actualDecayImage = 0;
		this->active = false;
	}
}

void Obj_Graf_Projectile::handle_impacting(PROYECTILE_TYPE type)
{
	unsigned int pics_quantity;
	switch (type)
	{
	case SNOW:
		pics_quantity = IMPACT_PICS_SNOW;
		break;
	case FIRE:
		pics_quantity = IMPACT_PICS_FIRE;
		break;
	}

	if(actualImpactImage == 0)
		al_play_sample(samples->impact_soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	if (this->actualImpactImage < pics_quantity)															// si todavia no termino la secuancia que siga
	{
		al_draw_scaled_bitmap(images->impactImages[this->actualImpactImage], 0, 0, al_get_bitmap_width(images->impactImages[this->actualImpactImage]), al_get_bitmap_height(images->impactImages[this->actualImpactImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		this->actualImpactImage++;
	}
	else
	{
		if(!secuenceOver_){
			secuenceOver_ = true;
			active = false;
			notify_finished_drawing_step();
		}
	}
}

int Obj_Graf_Projectile::get_movement_delta()
{
	int delta = 0;			//for quickly detecting errors (the enemy will not move).

	if (dir == Direction::Left)
		delta = -1;
	else if (dir == Direction::Right)
		delta = 1;

	return delta;
}

