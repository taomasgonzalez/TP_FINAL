#include "Map.h"


Map::Map(int number_of_rows, int number_of_columns, const char * original_map_distribution)
{

	this->number_of_rows = number_of_rows;
	this->number_of_columns = number_of_columns;
	this->original_map_distribution = new char[192]; //reservo la memoria

	map_cells = new MapCell*[number_of_rows];
	for (int i = 0; i < number_of_rows; ++i)
		map_cells[i] = new MapCell[number_of_columns];

	//load_the_map(original_map_distribution);
}

Map::~Map(){

	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		delete (*it);
	}
}

void Map::load_the_map(const char * CSV_map_location) {

	memcpy((void *)this->original_map_distribution, CSV_map_location, 192); //copio el csv que me llega en la clase
	//this->my_checksum=make_checksum(CSV_map_location);
}

//hace checksum local, función guido
unsigned char Map::make_checksum(const char * CSV_map_location) {

	unsigned char local_checksum='d'; 

	return local_checksum;
}
//después usar esta función que haga guido para el checksum de mapas que llegan para validarlos

const char * Map::give_me_the_original_map() {

	return this->original_map_distribution;
}

unsigned char  Map::give_me_the_checksum() {

	return this->my_checksum;
}



bool Map::cell_has_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_proyectiles();
}
bool Map::cell_has_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_players();
}
bool Map::cell_has_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_enemies();
}

MapCell Map::get_cell(int coord_x, int coord_y) {
	return map_cells[coord_x][coord_y];
}


std::vector<Enemy*> Map::get_cell_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_enemies();
}

std::vector<Player*> Map::get_cell_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_players();
}

std::vector<Proyectile*> Map::get_cell_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_proyectiles();
}

MapThing * Map::get_from_map(unsigned int id) {
	MapThing* gotten = NULL;
	for (int i = 0; i < number_of_rows; i++) 
		for (int j = 0; j < number_of_columns; j++) 
			if ((gotten = get_cell(i, j).get_id(id)) != NULL)
				break;
	
	return gotten;
}

bool Map::delete_from_map(unsigned int id) {
	bool successfully_deleted = false;
	for (int i = 0; i < number_of_rows; i++) 
		for (int j = 0; j < number_of_columns; j++) 
			if (successfully_deleted = get_cell(i, j).delete_id(id))
				break;
		
	return successfully_deleted;
}

bool Map::move_id(unsigned int id, int final_x, int final_y) {
	bool moved = false;
	MapThing * thingy = NULL;
	if ((thingy = get_from_map(id)) != NULL) 
		if (delete_from_map(id)) {
			place_on_map(final_x, final_y, thingy);
			moved = true;
		}
	return moved;
}

bool Map::place_on_map(int coord_x, int coord_y, MapThing* thing) {

	bool ok_pos=true; //??
	get_cell(coord_x, coord_y).place_on_cell(thing);

	return ok_pos;
}
