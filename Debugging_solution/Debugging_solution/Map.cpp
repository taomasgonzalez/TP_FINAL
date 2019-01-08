#include "Map.h"


Map::Map(int number_of_rows, int number_of_columns)
{
	this->number_of_rows = number_of_rows;
	this->number_of_columns = number_of_columns;

	map_cells = new MapCell*[number_of_rows];
	for (int i = 0; i < number_of_rows; ++i)
		map_cells[i] = new MapCell[number_of_columns];
}

Map::~Map()
{
}

bool Map::cell_has_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->has_proyectiles();
}
bool Map::cell_has_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->has_players();
}
bool Map::cell_has_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->has_enemies();
}

MapCell* Map::get_cell(int coord_x, int coord_y) {
	return &(map_cells[coord_x][coord_y]);
}


std::vector<Enemy*> Map::get_cell_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->get_enemies();
}

std::vector<Player*> Map::get_cell_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->get_players();
}

std::vector<Proyectile*> Map::get_cell_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y)->get_proyectiles();
}

MapThing * Map::get_from_map(unsigned int id) {
	MapThing* gotten = NULL;
	for (int i = 0; i < number_of_rows; i++) 
		for (int j = 0; j < number_of_columns; j++) 
			if ((gotten = get_cell(i, j)->get_id(id)) != NULL)
				break;
	
	return gotten;
}

bool Map::delete_from_map(unsigned int id) {
	bool successfully_deleted = false;
	for (int i = 0; i < number_of_rows; i++) 
		for (int j = 0; j < number_of_columns; j++) 
			if (successfully_deleted = get_cell(i, j)->delete_id(id))
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

void Map::place_on_map(int coord_x, int coord_y, MapThing* thing) {
	MapCell* cell = get_cell(coord_x, coord_y);
	cell->place_on_cell(thing);
}


void Map::print_map() {
	int number_of_floors = get_max_number_of_floors();

	char* printable = new char[number_of_rows * number_of_columns * number_of_floors];
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			std::vector<MapThing*> floors = get_cell(i, j)->get_floors();
			int floor_number = 0;
			for (std::vector<MapThing*>::iterator it = floors.begin(); it != floors.end(); ++it) {
				//arr[x + width * (y + depth * z)]
				printable[i + number_of_columns* (j + number_of_floors * floor_number)] = (*it)->id;
				floor_number++;
			}
		}

	for(int f = 0; f < number_of_floors; f++){
		printf("FLOOR %u : \n",f);
		for(int i = 0; i < number_of_rows; i++)
			for (int j = 0; j < number_of_columns; j++)
				printf("%c", printable[i + number_of_columns * (j + number_of_floors * f)]);
		printf("\n\n");
	}
}

int Map::get_max_number_of_floors() {

	int max_number_of_floors = 0;

	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++) {
			int curr = 0;
			if (( curr = get_cell(i, j)->get_number_of_floors()) > max_number_of_floors)
				max_number_of_floors = curr;
		}

	return max_number_of_floors;
		
}

void Map::load_on_map(char* map_string) {
	MapThingFactory map_filler;
	for (int i = 0; i < number_of_columns*number_of_rows; i++)
		place_on_map(i / number_of_columns, i % number_of_rows, map_filler.create_map_thing(map_string[i]));
}

void Map::reset_map()
{
}
