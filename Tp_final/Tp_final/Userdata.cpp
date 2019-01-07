#include "Userdata.h"

using namespace std;
std::array<ALLEGRO_BITMAP*, 15> Userdata::WormWalk;
std::array<ALLEGRO_BITMAP*, 10>Userdata::WormJump;
ALLEGRO_BITMAP *Userdata::Background;
ALLEGRO_BITMAP *Userdata::WindowsBackground;

Userdata::Userdata()
{
	for (int i = 0; i < 15; i++)
		this->WormWalk[i] = NULL;
	for (int i = 0; i < 10; i++)
		this->WormJump[i] = NULL;
	this->Background = NULL;
	this->WindowsBackground = NULL;

}



Userdata::~Userdata()
{
	for (int i = 0; i < 15; i++) {
		al_destroy_bitmap(Userdata::WormWalk[i]);
	}

	for (int i = 0; i < 10; i++) {
		al_destroy_bitmap(Userdata::WormJump[i]);
	}

	al_destroy_bitmap(Userdata::Background);
	al_destroy_bitmap(Userdata::WindowsBackground);
}

void Userdata::LoadWormImages() {
	string string;

	for (int i = 1; i < 16; i++) {
		string = str + to_string(i) + ng;    //Se inicializan los bitmaps de los worms
		Userdata::WormWalk[i - 1] = al_load_bitmap(string.c_str());
	}

	for (int i = 1; i < 11; i++) {
		string = STR + to_string(i) + NG;
		Userdata::WormJump[i - 1] = al_load_bitmap(string.c_str());
	}
}
