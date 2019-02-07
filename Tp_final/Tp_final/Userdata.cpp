#include "Userdata.h"

using namespace std;
std::array<ALLEGRO_BITMAP*, 15> AllegroData::WormWalk;
std::array<ALLEGRO_BITMAP*, 10>AllegroData::WormJump;
ALLEGRO_BITMAP *AllegroData::Background;
ALLEGRO_BITMAP *AllegroData::WindowsBackground;

/// EA_info METHODS

Action_info::Action_info(ENEMY_ACTION_EventPackage* trasnlate_please) {

	this->action = trasnlate_please->give_me_the_action();
	this->final_pos_x = trasnlate_please->give_me_the_destination_row();
	this->final_pos_y = trasnlate_please->give_me_the_destination_column();
	this->id = trasnlate_please->give_me_the_monsterID();
}

Action_info::Action_info() {

}

/// NETWORKDATA METHODS
bool NetworkData::has_new_info() {
	return this->new_info;
}
bool NetworkData::is_client() {
	return this->client_mode;
}
std::string NetworkData::give_me_my_name()
{
	return this->my_name;
}

void NetworkData::tell_me_his_name(char * his_name, unsigned char his_name_length)
{
	 this->his_name=string(his_name, his_name_length);  //como viene sin /n tomo los primero namelength chars 
}


std::string NetworkData::give_me_my_ip()
{
	return this->my_ip;
}
void NetworkData::set_client(bool is_client) {

	this->client_mode = is_client;
}
void NetworkData::set_should_check_for_new_messages(bool should_check) {

	this->check_for_new_messages = should_check;
}
bool  NetworkData::get_should_check_for_new_messages(void) {
	return this->check_for_new_messages;
}


void AllegroData::LoadWormImages() {
	string string;

	for (int i = 1; i < 16; i++) {
		string = str + to_string(i) + ng;    //Se inicializan los bitmaps de los worms
		AllegroData::WormWalk[i - 1] = al_load_bitmap(string.c_str());
	}

	for (int i = 1; i < 11; i++) {
		string = STR + to_string(i) + NG;
		AllegroData::WormJump[i - 1] = al_load_bitmap(string.c_str());
	}
}

Userdata::Userdata()
{
	for (int i = 0; i < 15; i++)
		this->my_allegro_data.WormWalk[i] = NULL;
	for (int i = 0; i < 10; i++)
		this->my_allegro_data.WormJump[i] = NULL;
	this->my_allegro_data.Background = NULL;
	this->my_allegro_data.WindowsBackground = NULL;

}



Userdata::~Userdata()
{
	for (int i = 0; i < 15; i++) {
		al_destroy_bitmap(AllegroData::WormWalk[i]);
	}

	for (int i = 0; i < 10; i++) {
		al_destroy_bitmap(AllegroData::WormJump[i]);
	}

	al_destroy_bitmap(AllegroData::Background);
	al_destroy_bitmap(AllegroData::WindowsBackground);
}

