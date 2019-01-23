#include "Drawer.h"


Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}


void Drawer::draw(Scene * scenario) {

	/*Worm * worm_to_be_drawn;

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(Userdata::WindowsBackground, 0, 0, NULL);
	al_draw_bitmap(Userdata::Background, 0, 0, NULL);

	worm_to_be_drawn= scenario->get_worm(worm_id::worm1);
	draw_my_worm(worm_to_be_drawn);

	worm_to_be_drawn = scenario->get_worm(worm_id::worm2);
	draw_my_worm(worm_to_be_drawn);

	al_flip_display();*/

}

/*void Drawer::draw_my_worm(Worm * actual_worm)
{
	uint tickCount = actual_worm->gettickCount();
	Point Position = actual_worm->getPosition();
	WormState State= actual_worm->getState();
	WormDirection Direction_type= actual_worm->getDirection();



	switch (Direction_type) {
	case WormDirection::Left: {
		switch (State) {
		case WormState::WaitingToWalk: {
			al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, NULL); break;
		}
		case WormState::ReconfirmWalk: {
			if (tickCount <= 49)
				al_draw_bitmap(Userdata::WormWalk[tickCount - 35], Position.X, Position.Y, NULL);
			else if (tickCount == 50)
				al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, NULL);
			break;
		}
		case WormState::Iddle: {
			al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, NULL); break;
		}
		case WormState::Walking: {
			if (tickCount <= 5)
				al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, NULL);
			else if (tickCount <= 8)
				al_draw_bitmap(Userdata::WormWalk[tickCount - 6], Position.X, Position.Y, NULL);
			else if (tickCount <= 50) {
				if (tickCount <= 16)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 6], Position.X, Position.Y, NULL);
				else if (tickCount <= 21)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 7], Position.X, Position.Y, NULL);
				else if (tickCount == 22)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, NULL);
				else if (tickCount <= 30)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 20], Position.X, Position.Y, NULL);
				else if (tickCount <= 35)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 21], Position.X, Position.Y, NULL);
				else if (tickCount == 36)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, NULL);
				else if (tickCount <= 44)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 34], Position.X, Position.Y, NULL);
				else if (tickCount <= 49)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 35], Position.X, Position.Y, NULL);
				else if (tickCount == 50)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, NULL);
			}
			break;
		}
		case WormState::Jumping: {
			if (tickCount <= 2)
				al_draw_bitmap(Userdata::WormJump[tickCount], Position.X, Position.Y, NULL);
			else if (tickCount <= 26)
				al_draw_bitmap(Userdata::WormJump[3], Position.X, Position.Y, NULL);
			else if (tickCount <= 32)
				al_draw_bitmap(Userdata::WormJump[tickCount - 23], Position.X, Position.Y, NULL);
			break;
		}
		}
		break;
	}
	case WormDirection::Right: {
		switch (State) {
		case WormState::WaitingToWalk: {
			al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL); break;
		}
		case WormState::ReconfirmWalk: {
			if (tickCount <= 49)
				al_draw_bitmap(Userdata::WormWalk[tickCount - 35], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			else if (tickCount == 50)
				al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		case WormState::Iddle: {
			al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL); break;
		}
		case WormState::Walking: {
			if (tickCount <= 5) {
				al_draw_bitmap(Userdata::WormWalk[0], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				al_flip_display();
			}
			else if (tickCount <= 8) {
				al_draw_bitmap(Userdata::WormWalk[tickCount - 6], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				al_flip_display();
			}
			else if (tickCount <= 50) {
				if (tickCount <= 16)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 6], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount <= 21)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 7], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount == 22)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount <= 30)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 20], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount <= 35)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 21], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount == 36)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount <= 44)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 34], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount <= 49)
					al_draw_bitmap(Userdata::WormWalk[tickCount - 35], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
				else if (tickCount == 50)
					al_draw_bitmap(Userdata::WormWalk[3], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			}
			break;
		}
		case WormState::Jumping: {
			if (tickCount <= 2)
				al_draw_bitmap(Userdata::WormJump[tickCount - 1], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			else if (tickCount <= 25)
				al_draw_bitmap(Userdata::WormJump[2], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			else if (tickCount <= 32)
				al_draw_bitmap(Userdata::WormJump[tickCount - 23], Position.X, Position.Y, ALLEGRO_FLIP_HORIZONTAL);
			break;
		}
		}
	}
	}



}*/