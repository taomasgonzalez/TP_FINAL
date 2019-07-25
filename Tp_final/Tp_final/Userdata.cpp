#include "Userdata.h"

using namespace std;

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

void NetworkData::tell_me_his_name(std::string  his_name)
{
	 this->his_name = his_name;  //como viene sin /n tomo los primero namelength chars 
}


std::string NetworkData::give_me_my_ip()
{
	return this->my_ip;
}

std::string NetworkData::give_me_his_ip()
{
	return this->his_ip;
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



Userdata::Userdata()
{
}



Userdata::~Userdata()
{
}


DRAW* Userdata::drawer = NULL;

Direction_type Userdata::sense_2_direction(Sense_type sense) {
	if (sense == Sense_type::Left)
		return Direction_type::Left;
	else if (sense == Sense_type::Right)
		return Direction_type::Right;
	else
		return Direction_type::None;
}


NetworkData::NetworkData() {
	my_ip = "25.98.236.6";
	his_ip = "25.66.202.87";
}