#include "GraficObjectEnemy.h"
#include "EnemyActionsFSMDRAWObserver.h"

using namespace std;

Obj_Graf_Enemy::Obj_Graf_Enemy()
{
}

Obj_Graf_Enemy::Obj_Graf_Enemy(double ID, ENEMY_TYPE type, ImageContainer* imageContainer, AudioContainer* audioContainer)
{
	actualImage = 0;
	attackActualImage = 0;
	walkActualImage = 0;
	idleActualImage = 0;
	dieActualImage = 0;
	trap1ActualImage = 0;
	trap2ActualImage = 0;
	trap1ticks = 0;
	trap2ticks = 0;
	actualImageInball_moving = 0;
	actualImageInball_idle = 0;
	this->type = type;
	vel_x_inball = VEL_X_INBALL;

	switch (type)
	{
	case PURPLE:
		velX = VEL_PURPLE;
		walking_pics = WALKING_PICS_PURPLE;
		jumping_pics = JUMPING_PICS_PURPLE;
		jumping_forw_pics = JUMPING_PICS_PURPLE;
		idle_pics = IDLE_PICS_PURPLE;
		attacking_pics = ATTACKING_PICS_PURPLE;
		falling_pics = FALLING_PICS_PURPLE;
		dying_pics = DYING_PICS_PURPLE;

		chara_images = &imageContainer->my_character_images_container.purple;
		this_images = &imageContainer->my_enemy_images_container.purple;
		chara_samples = &audioContainer->my_character_samples_container.purple;
		this_samples = &audioContainer->my_ball_samples;
		break;
	case FATTY:
		velX = VEL_FATTY;
		walking_pics = WALKING_PICS_FATTY;
		jumping_pics = JUMPING_PICS_FATTY;
		jumping_forw_pics = JUMPING_PICS_FATTY;
		idle_pics = IDLE_PICS_FATTY;
		attacking_pics = ATTACKING_PICS_FATTY;
		falling_pics = FALLING_PICS_FATTY;
		dying_pics = DYING_PICS_FATTY;

		chara_images = &imageContainer->my_character_images_container.fatty;
		this_images = &imageContainer->my_enemy_images_container.fatty;
		chara_samples = &audioContainer->my_character_samples_container.fatty;
		this_samples = &audioContainer->my_ball_samples;
		break;
	case CRAZY:
		velX = VEL_CRAZY;
		walking_pics = WALKING_PICS_CRAZY;
		jumping_pics = JUMPING_PICS_CRAZY;
		jumping_forw_pics = JUMPING_PICS_CRAZY;
		idle_pics = IDLE_PICS_CRAZY;
		attacking_pics = 0;
		falling_pics = FALLING_PICS_CRAZY;
		dying_pics = DYING_PICS_CRAZY;

		chara_images = &imageContainer->my_character_images_container.crazy;
		this_images = &imageContainer->my_enemy_images_container.crazy;
		chara_samples = &audioContainer->my_character_samples_container.crazy;
		this_samples = &audioContainer->my_ball_samples;
		break;
	}
}


Obj_Graf_Enemy::~Obj_Graf_Enemy()
{
}

void Obj_Graf_Enemy::draw()
{
	if (state != enemy_FALLING)
		stop_fall_aceleration();

	switch (this->state) {
	case enemy_WALKING:
		handle_walking();			//checked
		break;
	case enemy_JUMPING:
		handle_jumping();			//checked
		break;
	case enemy_JUMPING_FOWARD:
		handle_jumping_forward();
		break;
	case enemy_FALLING:
		handle_falling();
		break;
	case enemy_TRAPPED_1:
		handle_trapped(this->type, enemy_TRAPPED_1);
		break;
	case enemy_TRAPPED_2:
		handle_trapped(this->type, enemy_TRAPPED_2);
		break;
	case enemy_TRAPPED_3:
		handle_trapped(this->type, enemy_TRAPPED_3);
		break;
	case enemy_DYING:
		handle_dying();				//checked
		break;
	case enemy_IDLE:
		handle_idle();				//checked
		break;
	case enemy_INBALL_IDLE:
		handle_inball_iddle();		//checked
		break;
	case enemy_INBALL_MOVING:
		handle_inball_moving();
		break;
	case enemy_INBALL_PUSHING:
		handle_inball_pushing();	//checked
		break;
	case enemy_INBALL_FALLING:
		handle_inball_falling();		//checked
		break;
	case enemy_INBALL_DESTRUCTION:
		handle_inball_destruction();	//checked
		break;
	}
}


void Obj_Graf_Enemy::startDraw(Direction dir, void *state, POINT_& pos)
{
	this->active = true;
	if (dir != Direction::None)
		this->dir = dir;
	this->pos.set_x_coord(pos.get_x_coord());
	this->pos.set_y_coord(pos.get_y_coord());
	this->InitalPos = pos;
	this->state = *(ENEMY_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
	this->secuenceOver_ = false;
	notified_half_jump = false;
}

void Obj_Graf_Enemy::destroy()
{
	this->~Obj_Graf_Enemy();
}

void Obj_Graf_Enemy::reset()
{
	this->actualImage = 0;
	this->attackActualImage = 0;
	this->walkActualImage = 0;
	this->idleActualImage = 0;
	this->dieActualImage = 0;
	this->trap1ActualImage = 0;
	this->trap2ActualImage = 0;
	this->trap1ticks = 0;
	this->trap2ticks = 0;
	this->actualImageInball_moving = 0;
}

bool Obj_Graf_Enemy::secuenceOver()
{
	return this->secuenceOver_;
}


void Obj_Graf_Enemy::handle_trapped(ENEMY_TYPE type, ENEMY_STATE trapped_state) {
	unsigned int pics_quantity_1;
	unsigned int pics_quantity_2;
	unsigned int pics_quantity_3;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity_1 = TRAPPED_1_PICS_PURPLE;
		pics_quantity_2 = TRAPPED_2_PICS_PURPLE;
		pics_quantity_3 = TRAPPED_3_PICS_PURPLE;
		break;
	case FATTY:
		pics_quantity_1 = TRAPPED_1_PICS_FATTY;
		pics_quantity_2 = TRAPPED_2_PICS_FATTY;
		pics_quantity_3 = TRAPPED_3_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity_1 = TRAPPED_1_PICS_CRAZY;
		pics_quantity_2 = TRAPPED_2_PICS_CRAZY;
		pics_quantity_3 = TRAPPED_3_PICS_CRAZY;
		break;
	}


	//ENEMY_STATE : enemy_TRAPPED_1 or enemy_TRAPPED_2
	if (trapped_state == enemy_TRAPPED_1) {
		trap1ActualImage = (trap1ticks % (pics_quantity_1 * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
		al_draw_scaled_bitmap(this_images->trap1Images[trap1ActualImage], 0, 0, al_get_bitmap_width(this_images->trap1Images[this->trap1ActualImage]), al_get_bitmap_height(this_images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

		if (++trap1ticks > TICKS_TRAPPED)
		{
			secuenceOver_ = true;
			trap1ticks = 0;
		}
	}
	else if (trapped_state == enemy_TRAPPED_2) {
		trap2ActualImage = (trap2ticks % (pics_quantity_2 * 2)) / 2;
		al_draw_scaled_bitmap(this_images->trap2Images[trap2ActualImage], 0, 0, al_get_bitmap_width(this_images->trap2Images[this->trap2ActualImage]),
			al_get_bitmap_height(this_images->trap2Images[trap2ActualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		trap2ticks++;

		if (trap2ticks > TICKS_TRAPPED)
		{
			secuenceOver_ = true;
			trap2ticks = 0;
		}
	}
	else if (trapped_state == enemy_TRAPPED_3) {
		trap3ActualImage = (trap3ticks % (pics_quantity_3 * 2)) / 2;
		al_draw_scaled_bitmap(this_images->trap3Images[trap3ActualImage], 0, 0, al_get_bitmap_width(this_images->trap3Images[this->trap3ActualImage]),
			al_get_bitmap_height(this_images->trap3Images[trap3ActualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		trap3ticks++;

		if (trap3ticks > TICKS_TRAPPED)
		{
			secuenceOver_ = true;
			trap3ticks = 0;
		}
	}

}

void Obj_Graf_Enemy::handle_inball_iddle() {
	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(this_images->inballIdleImages[actualImageInball_idle], 0, 0, al_get_bitmap_height(this_images->inballIdleImages[actualImageInball_idle]),
		al_get_bitmap_width(this_images->inballIdleImages[actualImageInball_idle]),
		pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((actualImageInball_idle + 1) < IDLE_PICS_BALL) ? actualImageInball_idle++ : actualImageInball_idle = 0;

}

void Obj_Graf_Enemy::handle_inball_moving() {
	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	if(actualImageInball_moving == 0)
		al_play_sample(this_samples->move_soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);


	if (reached_final_pos)
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
		active = false;															// se pasiva el objeto
		actualImage = 0;
	}
	else
		pos.set_x_coord(pos.get_x_coord() + delta * vel_x_inball);	// muevo la posicion del dibujo

	//should flip the image when going left

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(this_images->inballMoveImages[actualImageInball_moving], 0, 0, al_get_bitmap_height(this_images->inballMoveImages[actualImageInball_moving]), al_get_bitmap_width(this_images->inballMoveImages[actualImageInball_moving]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

	// se pasa al siguiente sprite
	((actualImageInball_moving + 1) < MOVING_PICS_BALL) ? actualImageInball_moving++ : actualImageInball_moving = 0;





	/**************************************************





	if (pos.get_x_coord() <= (InitalPos.get_x_coord() - BLOCK_SIZE))
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() - BLOCK_SIZE);
	}
	else
	{
		pos.set_x_coord( pos.get_x_coord() - velX);
		((actualImageInball_moving + 1) < MOVING_PICS_BALL) ? actualImageInball_moving++ : actualImageInball_moving = 0;
	}

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(this_images->inballMoveImages[actualImageInball_moving], 0, 0, al_get_bitmap_height(this_images->inballMoveImages[actualImageInball_moving]), al_get_bitmap_width(this_images->inballMoveImages[actualImageInball_moving]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	*/
}

void Obj_Graf_Enemy::handle_inball_pushing() {

	int delta = get_movement_delta();

	bool reached_final_pos = false;
	if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() > (this->InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else
		reached_final_pos = pos.get_x_coord() < (InitalPos.get_x_coord() + delta * BLOCK_SIZE);

	if (reached_final_pos)
	{
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	}
	else
	{
		pos.set_x_coord(pos.get_x_coord() + delta * VEL_PUSHED_INBALL);
		((actualImageInball_moving + 1) < 2 * PUSHING_PICS_BALL) ? actualImageInball_moving++ : actualImageInball_moving = 0;
	}

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(this_images->inballPushImages[actualImageInball_moving / 2], 0, 0, al_get_bitmap_height(this_images->inballPushImages[actualImageInball_moving / 2]), al_get_bitmap_width(this_images->inballPushImages[actualImageInball_moving / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Enemy::handle_inball_falling() {

	if (pos.get_y_coord() > (InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		pos.set_y_coord(InitalPos.get_y_coord() + BLOCK_SIZE);
		actualImageInball_moving = 0;
	}
	else
	{
		(actualImageInball_moving < (FALLING_PICS_BALL - 1)) ? actualImageInball_moving++ : actualImageInball_moving = 0;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() + velFall);															// muevo la posicion del dibujo
	}

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(this_images->inballFallImages[actualImageInball_moving], 0, 0, al_get_bitmap_height(this_images->inballFallImages[actualImageInball_moving]), al_get_bitmap_width(this_images->inballFallImages[actualImageInball_moving]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}

void Obj_Graf_Enemy::handle_inball_destruction() {

	if(actualDestructionImage == 0)
		al_play_sample(this_samples->impact_soundEffect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

	if (actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
	{
		int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		al_draw_scaled_bitmap(this_images->inballDestructiontImages[actualDestructionImage], 0, 0, al_get_bitmap_width(this_images->inballDestructiontImages[actualDestructionImage]), al_get_bitmap_height(this_images->inballDestructiontImages[actualDestructionImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		actualDestructionImage++;
	}
	else
	{
		actualDestructionImage = 0;
		active = false;
		secuenceOver_ = true;
	}

}

void Obj_Graf_Enemy::going_right() {
	switch (this->state)
	{

	case enemy_JUMPING_FOWARD:
		if (this->pos.get_y_coord() < (this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
		{
			this->secuenceOver_ = true;
			this->pos.set_y_coord(this->InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
			//				this->active = false;															// se pasiva el objeto
			this->actualImage = 0;
			//this->state = enemy_IDLE;
		}
		else
		{
			(this->actualImage < (JUMPING_PICS_PURPLE - 1)) ? this->actualImage++ : NULL;																									// ubico el siguiente frame
			this->pos.set_y_coord(this->pos.get_y_coord() - this->velFall);															// muevo la posicion del dibujo
		}

		if (this->pos.get_x_coord() <= (this->InitalPos.get_x_coord() - BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
		{
			this->pos.set_x_coord(this->InitalPos.get_x_coord() - BLOCK_SIZE);
		}
		else
			this->pos.set_x_coord(this->pos.get_x_coord() + (this->velX) / 2);				// se divide por 2 la velocidad ya que debera recorrer en x la 
		al_draw_scaled_bitmap(this_images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_width(this_images->jumpImages[this->actualImage]), al_get_bitmap_height(this_images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		break;
	case enemy_FALLING:
		if (this->pos.get_y_coord() > (this->InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
		{
			this->secuenceOver_ = true;
			this->pos.set_y_coord(this->InitalPos.get_y_coord() + BLOCK_SIZE);
			//				this->active = false;															// se pasiva el objeto
			this->actualImage = 0;
			//						this->state = enemy_IDLE;
		}
		else
		{
			//al_draw_bitmap(this_images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
			(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
		}
		al_draw_scaled_bitmap(this_images->fallImages[this->actualImage], 0, 0, al_get_bitmap_width(this_images->fallImages[this->actualImage]), al_get_bitmap_height(this_images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		break;
	case enemy_TRAPPED_1:
		this->trap1ActualImage = (this->trap1ticks % (TRAPPED_1_PICS_PURPLE * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
		al_draw_scaled_bitmap(this_images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_width(this_images->trap1Images[this->trap1ActualImage]), al_get_bitmap_height(this_images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
		this->trap1ticks++;
		if (this->trap1ticks > TICKS_TRAPPED)
		{
			this->secuenceOver_ = true;
			this->trap1ticks = 0;
		}
		break;
	case enemy_TRAPPED_2:
		this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_PURPLE * 2)) / 2;
		al_draw_scaled_bitmap(this_images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_width(this_images->trap2Images[this->trap2ActualImage]), al_get_bitmap_height(this_images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		//al_draw_bitmap(this->trapImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);
		this->trap2ticks++;
		if (this->trap1ticks > TICKS_TRAPPED)
		{
			this->secuenceOver_ = true;
			this->trap2ticks = 0;
		}
		break;
	case enemy_INBALL_MOVING:
		if (this->pos.get_x_coord() >= (this->InitalPos.get_x_coord() + BLOCK_SIZE))
		{
			this->secuenceOver_ = true;
			this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
			//this->active = false;
			//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
		}
		else
		{
			//al_draw_bitmap(this->moveImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
			((this->actualImageInball_moving + 1) < MOVING_PICS_BALL) ? this->actualImageInball_moving++ : this->actualImageInball_moving = 0;
		}
		al_draw_scaled_bitmap(this_images->inballMoveImages[this->actualImageInball_moving], 0, 0, al_get_bitmap_height(this_images->inballMoveImages[this->actualImageInball_moving]), al_get_bitmap_width(this_images->inballMoveImages[this->actualImageInball_moving]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
		break;
	case enemy_INBALL_PUSHING:
		if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
		{
			this->secuenceOver_ = true;
			this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
		}
		else
		{
			//al_draw_bitmap(this->pushImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), ALLEGRO_FLIP_HORIZONTAL);
			this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED_INBALL);
			((this->actualImageInball_moving + 1) < PUSHING_PICS_BALL * 2) ? this->actualImageInball_moving++ : this->actualImageInball_moving = 0;
		}
		al_draw_scaled_bitmap(this_images->inballPushImages[this->actualImageInball_moving / 2], 0, 0, al_get_bitmap_height(this_images->inballPushImages[this->actualImageInball_moving / 2]), al_get_bitmap_width(this_images->inballPushImages[this->actualImageInball_moving / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
		break;

	}
}
