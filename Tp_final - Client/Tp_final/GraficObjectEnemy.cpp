#include "GraficObjectEnemy.h"
#include "EnemyActionsFSMDRAWObserver.h"

using namespace std;

Obj_Graf_Enemy::Obj_Graf_Enemy()
{
}

Obj_Graf_Enemy::Obj_Graf_Enemy(double ID, ENEMY_TYPE type, ImageContainer* container) : Obj_Graf(ID)
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
	actualImageInball = 0;
	this->type = type;
	vel_x_inball = VEL_X_INBALL;

	switch (type)
	{
	case PURPLE:
		velX = VEL_PURPLE;
		images = &container->my_enemy_images_container.purple;
		break;
	case FATTY:
		velX = VEL_FATTY;
		images = &container->my_enemy_images_container.fatty;

		break;
	case CRAZY:
		velX = VEL_CRAZY;
		images = &container->my_enemy_images_container.crazy;
		break;
	}
}


Obj_Graf_Enemy::~Obj_Graf_Enemy()
{
}

void Obj_Graf_Enemy::draw()
{
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
		handle_trapped(enemy_TRAPPED_1);
		break;
	case enemy_TRAPPED_2:
		handle_trapped(enemy_TRAPPED_2);
		break;
	case enemy_DYING:
		handle_dying();				//checked
		break;
	case enemy_IDLE:
		handle_iddle();				//checked
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
	this->dir = dir;
	this->pos.set_x_coord(pos.get_x_coord());
	this->pos.set_y_coord(pos.get_y_coord());
	this->InitalPos = pos;
	this->state = *(ENEMY_STATE *)state;
	this->actualImage = 0;			// comienza con la primera imagen
	this->secuenceOver_ = false;
}

void Obj_Graf_Enemy::destroy()
{
}

void Obj_Graf_Enemy::reset()
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
	actualImageInball = 0;
}

bool Obj_Graf_Enemy::secuenceOver()
{
	return this->secuenceOver_;
}



void Obj_Graf_Enemy::handle_walking() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	switch (type)
	{
	case PURPLE:
		pics_quantity = WALKING_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;			// FATTY TIENE LAS IMAGES INVERTIDAS!
		pics_quantity = WALKING_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = WALKING_PICS_CRAZY;
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
		secuenceOver_ = true;
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
		active = false;															// se pasiva el objeto
		actualImage = 0;
	}
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX);	// muevo la posicion del dibujo

	//should flip the image when going left

	al_draw_scaled_bitmap(images->walkImages[walkActualImage / 2], 0, 0, al_get_bitmap_height(images->walkImages[walkActualImage / 2]),
							al_get_bitmap_width(images->walkImages[walkActualImage / 2]), pos.get_x_coord(), pos.get_y_coord(),
								BLOCK_SIZE, BLOCK_SIZE, flip);

	// se pasa al siguiente sprite
	((walkActualImage + 1) < 2 * pics_quantity) ? walkActualImage++ : walkActualImage = 0;
				
}

void Obj_Graf_Enemy::handle_jumping() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity = JUMPING_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity = JUMPING_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = JUMPING_PICS_CRAZY;
		break;
	}

	bool reached_final_pos = pos.get_y_coord() < (InitalPos.get_y_coord() - 2 * BLOCK_SIZE);;

	if (reached_final_pos)		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		pos.set_y_coord(InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
		actualImage = 0;
		notify_finished_drawing_step();
	}
	else
	{
		(actualImage < (pics_quantity - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
		if(pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE))
			notify_finished_drawing_step();
	}

	al_draw_scaled_bitmap(images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[actualImage]), al_get_bitmap_width(images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}


void Obj_Graf_Enemy::handle_jumping_forward() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity = JUMPING_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity = JUMPING_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = JUMPING_PICS_CRAZY;
		break;
	}

	int delta = get_movement_delta();
	if (pos.get_y_coord() < (InitalPos.get_y_coord() - 2 * BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		pos.set_y_coord(InitalPos.get_y_coord() - 2 * BLOCK_SIZE);
		actualImage = 0;
		notify_finished_drawing_step();
	}
	else
	{
		(actualImage < (pics_quantity - 1)) ? actualImage++ : NULL;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() - velFall);															// muevo la posicion del dibujo
		
		if (pos.get_y_coord() < (InitalPos.get_y_coord() - BLOCK_SIZE))
			notify_finished_drawing_step();

	}

	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);


	if (reached_final_pos)
		pos.set_x_coord(InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else
		pos.set_x_coord(pos.get_x_coord() + delta * velX / 2);	// muevo la posicion del dibujo


	al_draw_scaled_bitmap(images->jumpImages[actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[actualImage]),
							al_get_bitmap_width(images->jumpImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(),
								BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Enemy::handle_iddle() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity = IDLE_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity = IDLE_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = IDLE_PICS_CRAZY;
		break;
	}

	actualImage = 0;


	al_draw_scaled_bitmap(images->idleImages[idleActualImage], 0, 0, 
		al_get_bitmap_height(images->idleImages[idleActualImage]), al_get_bitmap_width(images->idleImages[idleActualImage]),
		pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

	(( idleActualImage + 1) < pics_quantity) ? idleActualImage++ : idleActualImage = 0;
}
void Obj_Graf_Enemy::handle_trapped(ENEMY_STATE trapped_state) {
	unsigned int pics_quantity_1;
	unsigned int pics_quantity_2;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity_1 = TRAPPED_1_PICS_PURPLE;
		pics_quantity_2 = TRAPPED_2_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity_1 = TRAPPED_1_PICS_FATTY;
		pics_quantity_2 = TRAPPED_2_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity_1 = TRAPPED_1_PICS_CRAZY;
		pics_quantity_2 = TRAPPED_2_PICS_CRAZY;
		break;
	}


	//ENEMY_STATE : enemy_TRAPPED_1 or enemy_TRAPPED_2
	if (trapped_state == enemy_TRAPPED_1) {
		trap1ActualImage = (trap1ticks % (pics_quantity_1 * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
		al_draw_scaled_bitmap(images->trap1Images[trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

		if (++trap1ticks > TICKS_TRAPPED)
		{
			secuenceOver_ = true;
			trap1ticks = 0;
		}
	}
	else if (trapped_state == enemy_TRAPPED_2) {
		trap2ActualImage = (trap2ticks % (pics_quantity_2 * 2)) / 2;
		al_draw_scaled_bitmap(images->trap2Images[trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]),
								al_get_bitmap_width(images->trap2Images[trap2ActualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		trap2ticks++;

		if (trap2ticks > TICKS_TRAPPED)
		{
			secuenceOver_ = true;
			trap2ticks = 0;
		}
	}

}
void Obj_Graf_Enemy::handle_attacking() {
	if (type == FATTY)		//FATTY is the only enemy to have an attack, any other enemy won´t attack
	{
		if ((this->attackActualImage + 1) < 2 * ATTACKING_PICS_FATTY)
		{
			this->attackActualImage++;																									// termino la secuencia de disparo
		}
		else
		{
			this->secuenceOver_ = true;
			this->attackActualImage = 0;
		}
		int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		al_draw_scaled_bitmap(images->attackImages[this->attackActualImage / 2], 0, 0, 
			al_get_bitmap_height(images->attackImages[this->attackActualImage / 2]), 
			al_get_bitmap_width(images->attackImages[this->attackActualImage / 2]), 
			this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	}
}
void Obj_Graf_Enemy::handle_falling() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity = FALLING_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity = FALLING_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = FALLING_PICS_CRAZY;
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

	al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[actualImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}
void Obj_Graf_Enemy::handle_dying() {
	unsigned int pics_quantity;
	int flip = (dir == Direction::Left) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	switch (type)
	{
	case PURPLE:
		pics_quantity = DYING_PICS_PURPLE;
		break;
	case FATTY:
		flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		pics_quantity = DYING_PICS_FATTY;
		break;
	case CRAZY:
		pics_quantity = DYING_PICS_CRAZY;
		break;
	}

	if ((dieActualImage + 1) < pics_quantity)
		dieActualImage++;
	else
		secuenceOver_ = true;

	al_draw_scaled_bitmap(images->dieImages[dieActualImage], 0, 0, al_get_bitmap_height(images->dieImages[dieActualImage]), al_get_bitmap_width(images->dieImages[dieActualImage]), 
							pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Enemy::handle_inball_iddle() {
	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;

	al_draw_scaled_bitmap(images->inballIdleImages[actualImageInball], 0, 0, al_get_bitmap_height(images->inballIdleImages[actualImageInball]), 
							al_get_bitmap_width(images->inballIdleImages[actualImageInball]), 
							pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
	((actualImageInball + 1) < IDLE_PICS_BALL) ? actualImageInball++ : actualImageInball = 0;

}

void Obj_Graf_Enemy::handle_inball_moving() {
	int delta = get_movement_delta();
	bool reached_final_pos = false;

	if (dir == Direction::Left)
		reached_final_pos = pos.get_x_coord() <= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);
	else if (dir == Direction::Right)
		reached_final_pos = pos.get_x_coord() >= (InitalPos.get_x_coord() + delta * BLOCK_SIZE);


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
	al_draw_scaled_bitmap(images->inballMoveImages[actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[actualImageInball]), al_get_bitmap_width(images->inballMoveImages[actualImageInball]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

	// se pasa al siguiente sprite
	((actualImageInball + 1) < MOVING_PICS_BALL) ? actualImageInball++ : actualImageInball = 0;

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
		pos.set_x_coord(InitalPos.get_x_coord() + delta* BLOCK_SIZE);
	}
	else
	{
		pos.set_x_coord(pos.get_x_coord() + delta * VEL_PUSHED_INBALL);
		((actualImageInball + 1) < 2 * PUSHING_PICS_BALL) ? actualImageInball++ : actualImageInball = 0;
	}

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->inballPushImages[actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[actualImageInball / 2]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
}

void Obj_Graf_Enemy::handle_inball_falling() {

	if ( pos.get_y_coord() > ( InitalPos.get_y_coord() + BLOCK_SIZE))		// se desplaza a la izquierda, veo si ya llego a la pos final 
	{
		secuenceOver_ = true;
		pos.set_y_coord(InitalPos.get_y_coord() + BLOCK_SIZE);
		actualImageInball = 0;
	}
	else
	{
		( actualImageInball < (FALLING_PICS_BALL - 1)) ? actualImageInball++ : actualImageInball = 0;																									// ubico el siguiente frame
		pos.set_y_coord(pos.get_y_coord() + velFall);															// muevo la posicion del dibujo
	}

	int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
	al_draw_scaled_bitmap(images->inballFallImages[actualImageInball], 0, 0, al_get_bitmap_height(images->inballFallImages[actualImageInball]), al_get_bitmap_width(images->inballFallImages[actualImageInball]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);

}

void Obj_Graf_Enemy::handle_inball_destruction() {

	if ( actualDestructionImage < DESTRUCTION_PICS_BALL)															// si todavia no termino la secuancia que siga
	{
		int flip = (dir == Direction::Right) ? ALLEGRO_FLIP_HORIZONTAL : NULL;
		al_draw_scaled_bitmap(images->inballDestructiontImages[actualDestructionImage], 0, 0, al_get_bitmap_height(images->inballDestructiontImages[actualDestructionImage]), al_get_bitmap_width(images->inballDestructiontImages[actualDestructionImage]), pos.get_x_coord(), pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, flip);
		actualDestructionImage++;
	}
	else
	{
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
		al_draw_scaled_bitmap(images->jumpImages[this->actualImage], 0, 0, al_get_bitmap_height(images->jumpImages[this->actualImage]), al_get_bitmap_width(images->jumpImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
			//al_draw_bitmap(images->jumpImages[this->actualImage], this->pos.get_x_coord(), this->pos.get_y_coord(), NULL);			// se dibuja
			(this->actualImage < (FALLING_PICS_PURPLE - 1)) ? this->actualImage++ : this->actualImage = 0;																									// ubico el siguiente frame
			this->pos.set_y_coord(this->pos.get_y_coord() + this->velFall);															// muevo la posicion del dibujo
		}
		al_draw_scaled_bitmap(images->fallImages[this->actualImage], 0, 0, al_get_bitmap_height(images->fallImages[this->actualImage]), al_get_bitmap_width(images->fallImages[this->actualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		break;
	case enemy_TRAPPED_1:
		trap1ActualImage = (trap1ticks % (TRAPPED_1_PICS_PURPLE * 2)) / 2;		// multiplico y divido por 2 para que sea mas lenta la enimacion
		al_draw_scaled_bitmap(images->trap1Images[this->trap1ActualImage], 0, 0, al_get_bitmap_height(images->trap1Images[this->trap1ActualImage]), al_get_bitmap_width(images->trap1Images[this->trap1ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
		trap1ticks++;
		if (this->trap1ticks > TICKS_TRAPPED)
		{
			this->secuenceOver_ = true;
			this->trap1ticks = 0;
		}
		break;
	case enemy_TRAPPED_2:
		this->trap2ActualImage = (this->trap2ticks % (TRAPPED_2_PICS_PURPLE * 2)) / 2;
		al_draw_scaled_bitmap(images->trap2Images[this->trap2ActualImage], 0, 0, al_get_bitmap_height(images->trap2Images[this->trap2ActualImage]), al_get_bitmap_width(images->trap2Images[this->trap2ActualImage]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, NULL);
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
		}
		else
		{
			this->pos.set_x_coord(this->pos.get_x_coord() + this->velX);
			((this->actualImageInball + 1) < MOVING_PICS_BALL) ? this->actualImageInball++ : this->actualImageInball = 0;
		}
		al_draw_scaled_bitmap(images->inballMoveImages[this->actualImageInball], 0, 0, al_get_bitmap_height(images->inballMoveImages[this->actualImageInball]), al_get_bitmap_width(images->inballMoveImages[this->actualImageInball]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
		break;
	case enemy_INBALL_PUSHING:
		if (this->pos.get_x_coord() > (this->InitalPos.get_x_coord() + BLOCK_SIZE))						// BLOCK_SIZE / 2 para que no atraviese el piso
		{
			this->secuenceOver_ = true;
			this->pos.set_x_coord(this->InitalPos.get_x_coord() + BLOCK_SIZE);
		}
		else
		{
			this->pos.set_x_coord(this->pos.get_x_coord() + VEL_PUSHED_INBALL);
			((this->actualImageInball + 1) < PUSHING_PICS_BALL * 2) ? this->actualImageInball++ : this->actualImageInball = 0;
		}
		al_draw_scaled_bitmap(images->inballPushImages[this->actualImageInball / 2], 0, 0, al_get_bitmap_height(images->inballPushImages[this->actualImageInball / 2]), al_get_bitmap_width(images->inballPushImages[this->actualImageInball / 2]), this->pos.get_x_coord(), this->pos.get_y_coord(), BLOCK_SIZE, BLOCK_SIZE, ALLEGRO_FLIP_HORIZONTAL);
		break;

	}
}


int Obj_Graf_Enemy::get_movement_delta(){
	int delta = 0;			//for quickly detecting errors (the enemy will not move).

	if (dir == Direction::Left) 
		delta = -1;
	else if (dir == Direction::Right) 
		delta = 1;

	return delta;
}
