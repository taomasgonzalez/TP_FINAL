#include "Map.h"

/*
//////////////////Map::give_me_my_enemy_action///////////// escribo el encabezdo y la función vacia asi compila
-To do: Llamo a esta función ya sea para cargar los EA iniciales o durante el juego normal. Tenés que ir por el vector con un iterador o algo
e ir mandandomelos, no te mando info adicional de que moustruo es. 
-input: bool (si recibe true es porque esta en modo inicialización, si false es que estás jugando)
-output: EventPackage* el paquete enemy action para enviar por networking

IMPORTANTE: Si ya fueron mandados todos los EA iniciales tenés que devolver NULL, sólo cuando estas en modo inicialización(te llega un true como argumento)
Aclaración: no sé si vale realmente la diferencia entre inicializando y no, lo dejo por si hay que implementar algo más adelante
*/

Map::Map(int number_of_rows, int number_of_columns, const char * original_map_distribution, unsigned char checksum )
{
	this->number_of_rows = number_of_rows;
	this->number_of_columns = number_of_columns;

	map_cells = new MapCell*[number_of_rows];
	for (int i = 0; i < number_of_rows; ++i)
		map_cells[i] = new MapCell[number_of_columns];

	original_distribution = NULL;
}

Map::~Map()
{
	for (int i = 0; i < number_of_rows; ++i)
		delete[] map_cells[i];
	delete[] map_cells;
}

void Map::load_the_map(const char * CSV_map_location) {

	memcpy((void *)this->original_map_distribution, CSV_map_location, 192); //copio el csv que me llega en la clase
}




const char * Map::give_me_the_original_map() {

	return this->original_map_distribution;
}

EventPackage* Map::give_me_my_enemy_action(bool is_initializing) {


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

void Map::clear()
{
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			get_cell(i, j).clear();
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

MapThing * Map::get_from_map(int coord_x, int coord_y, int coord_z)
{
	return get_cell(coord_x, coord_y).get_floor(coord_z);
}

bool Map::delete_from_map(unsigned int id) {
	bool successfully_deleted = false;
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			if (successfully_deleted = get_cell(i, j).delete_id(id))
				break;

	return successfully_deleted;
}

bool Map::delete_from_map(MapThing * thing) {
	bool successfully_deleted = false;
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			if (successfully_deleted = get_cell(i, j).delete_map_thing(thing))
				break;

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

void Map::reset_map()
{
	clear();
	load_on_map(original_distribution);
}
