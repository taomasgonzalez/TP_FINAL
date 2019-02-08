#include "Userdata.h"

using namespace std;
std::array<ALLEGRO_BITMAP*, 15> AllegroData::WormWalk;
std::array<ALLEGRO_BITMAP*, 10>AllegroData::WormJump;
ALLEGRO_BITMAP *AllegroData::Background;
ALLEGRO_BITMAP *AllegroData::WindowsBackground;

/// EA_info METHODS

Action_info::Action_info(EventPackage* trasnlation_procedure) {

	this->my_info_header = trasnlation_procedure->give_me_your_event_type();
	this->is_local = trasnlation_procedure->is_this_a_local_action();

	switch (my_info_header)
	{

	case Event_type::MOVE:
		if (is_local)
		{
			this->my_direction = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_direction();
		}
		else
		{
			this->my_character = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_the_character();
			this->final_pos_x = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_destination_row();
			this->final_pos_y = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_destination_column();
		}
		break;
	case Event_type::ATTACK:
		if (is_local)
		{
			this->my_direction = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_direction(); //none
		}
		else
		{
			this->my_character = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_the_character();
			this->final_pos_x = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_destination_row();
			this->final_pos_y = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_destination_column();
		}
		break;
	case Event_type::ACTION_REQUEST:
		if (is_local)
		{
			this->my_direction = ((MOVE_EventPackage*)trasnlation_procedure)->give_me_your_direction(); //none
		}
		else
		{
			this->action = ((ACTION_REQUEST_EventPackage*)trasnlation_procedure)->give_me_the_action();
			this->final_pos_x = ((ACTION_REQUEST_EventPackage*)trasnlation_procedure)->give_me_your_destination_row();
			this->final_pos_y = ((ACTION_REQUEST_EventPackage*)trasnlation_procedure)->give_me_your_destination_column();
		}
		break;

	case Event_type::ENEMY_ACTION:

		this->action = ((ENEMY_ACTION_EventPackage*)trasnlation_procedure)->give_me_the_action();
		this->final_pos_x = ((ENEMY_ACTION_EventPackage*)trasnlation_procedure)->give_me_the_destination_row();
		this->final_pos_y = ((ENEMY_ACTION_EventPackage*)trasnlation_procedure)->give_me_the_destination_column();
		this->id = ((ENEMY_ACTION_EventPackage*)trasnlation_procedure)->give_me_the_monsterID();

		break;

	}

	delete trasnlation_procedure;
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

