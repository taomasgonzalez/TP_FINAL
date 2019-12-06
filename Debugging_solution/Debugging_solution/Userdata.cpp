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

void NetworkData::tell_me_his_name(char * his_name, unsigned char his_name_length)
{
	 this->his_name = string(his_name, his_name_length);  //como viene sin /n tomo los primero namelength chars 
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


NetworkData::NetworkData() {

}