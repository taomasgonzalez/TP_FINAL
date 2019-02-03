#include "Map.h"


Map::Map(int number_of_rows, int number_of_columns)
{
	this->number_of_rows = number_of_rows;
	this->number_of_columns = number_of_columns;

	map_cells = new MapCell*[number_of_rows];
	for (int i = 0; i < number_of_rows; ++i)
		map_cells[i] = new MapCell[number_of_columns];

	original_distribution = NULL;

	all_players = new std::vector<Player*>();
	all_proyectiles = new std::vector<Proyectile*>();
	all_enemies = new std::vector<Enemy*>();

}

Map::~Map()
{
	for (int i = 0; i < number_of_rows; ++i)
		delete[] map_cells[i];
	delete[] map_cells;

	delete all_players;
	delete all_enemies;
	delete all_proyectiles;
}

std::vector<Enemy*>* Map::get_all_enemies()
{
	std::vector<Enemy*> all_enemies = std::vector<Enemy*>();
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			if (cell_has_enemies(i, j)) {
				std::vector<Enemy*> some_enemies = get_cell_enemies(i, j);
				all_enemies.insert(std::end(all_enemies), std::begin(some_enemies), std::end(some_enemies));
			}
		}
	return all_enemies;
}





const char * Map::give_me_the_original_map() {

	return this->original_distribution;
}

EventPackage* Map::give_me_my_enemy_action(bool is_initializing) {


}

unsigned char  Map::give_me_the_checksum() {

	return this->my_checksum;
}

std::vector<Proyectile*> Map::get_all_proyectiles()
{
	std::vector<Proyectile*> all_proyectiles = std::vector<Proyectile*>();
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			if (cell_has_proyectiles(i, j)) {
				std::vector<Proyectile*> some_proyectiles = get_cell_proyectiles(i, j);
				all_proyectiles.insert(std::end(all_proyectiles), std::begin(some_proyectiles), std::end(some_proyectiles));
			}
		}
	return all_proyectiles;
}

std::vector<Player*>* Map::get_all_players()
{
	std::vector<Player*> all_players = std::vector<Player*>();
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			if (cell_has_players(i, j)) {
				std::vector<Player*> some_players = get_cell_players(i, j);
				all_players.insert(std::end(all_players), std::begin(some_players), std::end(some_players));
			}
		}
	return all_players;
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

void Map::clear()
{
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			get_cell(i, j).clear();
}


std::vector<Enemy*> Map::get_cell_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_enemies();
}

bool Map::cell_has_floor(int coord_x, int coord_y)
{
	return get_cell(coord_x, coord_y).has_floor();
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

MapThing * Map::get_from_map(int coord_x, int coord_y, int coord_z)
{
	return get_cell(coord_x, coord_y).get_floor(coord_z);
}

bool Map::delete_from_map(unsigned int id) {
	bool successfully_deleted = false;

	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++){
			MapThing* thing = get_cell(i, j).get_id(id);
			if(thing != NULL){
				delete_from_map(thing);
				break;
			}
		}
	return successfully_deleted;
}

bool Map::delete_from_map(MapThing * thing) {

	bool successfully_deleted = false;

	if (successfully_deleted = get_cell(thing->pos_x, thing->pos_y).delete_map_thing(thing)){
		delete_from_map_thing_vectors(thing);
		thing->pos_x = -1;
		thing->pos_y = -1;
	}

	return successfully_deleted;
}
void Map::print_cell(int coord_x, int coord_y)
{
	get_cell(coord_x, coord_y).print();
}
const char * Map::get_last_loaded_distribution()
{
	return original_distribution;
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

void Map::place_on_map(int coord_x, int coord_y, MapThing* thing) {
	MapCell cell = get_cell(coord_x, coord_y);
	cell.place_on_cell(thing);
	thing->pos_x = coord_x;
	thing->pos_y = coord_y;
	place_on_map_thing_vectors(thing);
}


void Map::print_map() {

	for (int z = 0; z < get_max_number_of_floors(); z++) {
		printf("FLOOR %u : \n", z);
		for (int x = 0; x < number_of_rows; x++)
			for (int y = 0; y < number_of_columns; y++) {
				MapCell curr_cell = get_cell(x, y);
				int num_floors = curr_cell.get_number_of_floors();
				if (num_floors >= z)
					printf("%c", curr_cell.get_floor(z)->get_printable());
				else
					printf(" ");
			}
		printf("\n\n");
	}

}

int Map::get_max_number_of_floors() {

	int max_number_of_floors = 0;

	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			int curr = 0;
			if ((curr = get_cell(i, j).get_number_of_floors()) > max_number_of_floors)
				max_number_of_floors = curr;
		}

	return max_number_of_floors;

}

void Map::load_on_map(const char* map_string) {
	original_distribution = map_string;

	MapThingFactory map_filler;
	for (int i = 0; i < number_of_columns*number_of_rows; i++) {
		int fil = i / number_of_columns;
		int col = i % number_of_columns;
		place_on_map(fil, col, map_filler.create_map_thing(map_string[i]));
	}
}

void Map::load_checksum(unsigned char checksum) {

	this->my_checksum = checksum;
}



void Map::reset_map()
{
	clear();
	load_on_map(original_distribution);
}


void Map::delete_from_map_thing_vectors(MapThing* thing) {

	if (thing->is_proyectile())
		for (std::vector<Proyectile*>::iterator it = all_proyectiles->begin(); it != all_proyectiles->end(); ++it) {
			all_proyectiles->erase(it);
			break;
		}
	else if (thing->is_enemy())
		for (std::vector<Enemy*>::iterator it = all_enemies->begin(); it != all_enemies->end(); ++it) {
			all_enemies->erase(it);
			break;
		}
	else if (thing->is_player())
		for (std::vector<Player*>::iterator it = all_players->begin(); it != all_players->end(); ++it) {
			all_players->erase(it);
			break;
		}
}

void Map::place_on_map_thing_vectors(MapThing* thing) {
	if (thing->is_proyectile())
		all_proyectiles->push_back(thing);
	else if (thing->is_enemy())
		all_enemies->push_back(thing);
	else if (thing->is_player())
		all_players->push_back(thing);
}