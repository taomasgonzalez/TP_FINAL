#include "Map.h"

#include<iostream>

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
	map_filler = MapThingFactory();
}

Map::~Map()
{
	for (int i = 0; i < number_of_rows; ++i)
		delete[] map_cells[i];
	delete[] map_cells;

	delete all_players;
	delete all_enemies;
	delete all_proyectiles;
	delete dijkstra_manager;
}


/******************************************
**************get_all_enemies**************
*******************************************
*get_all_enemies returns a pointer to an Enemy pointer 
*vector that contains all enemies on the map, both dead and alive.
*	INPUT:
		1) void.	
*	OUTPUT:
*		pointer to an Enemy pointer vector with the characteristics given by the description. 
*/
std::vector<Enemy*>* Map::get_all_enemies()
{
	return all_enemies;
}
/******************************************
*****************get_all_proyectiles*******
*******************************************
*get_all_proyectiles returns a pointer to a Proyectile pointer 
*vector that contains all proyectiles on the map.
*	INPUT:
		1)	void.
*	OUTPUT:
*		pointer to a Proyectile pointer vector with the characteristics given by the description.
*/
std::vector<Proyectile*>* Map::get_all_proyectiles()
{
	return all_proyectiles;
}
/******************************************
*****************get_all_players***********
*******************************************
*get_all_players returns a pointer to a Player pointer vector 
*that contains all players on the map, both dead and alive.
*	INPUT:
1)
*	OUTPUT:
*		pointer to a Player pointer vector with the characteristics given by the description.
*/
std::vector<Player*>* Map::get_all_players()
{
	return all_players;
}
/******************************************
**********give_me_the_original_map*********
*******************************************
*give_me_the_original_map returns the map's original distribution in a char array.
*This distribution has the same format as the char array received and sent by networking.
*Each char represents the same MapThing as the communication protocol establishes.
*	INPUT:
		1)	void.
*	OUTPUT:
*		char pointer that contains a string (without the terminator) with the chars that 
*		give the map the original level distribution. 
*/
const char * Map::give_me_the_original_map() {

	return this->original_distribution;
}

/******************************************
**************give_me_the_checksum*********
*******************************************
*give_me_the_checksum

*	INPUT:
*		1)	void.
*	OUTPUT:
*
*/
unsigned char  Map::give_me_the_checksum() {

	return this->my_checksum;
}
/******************************************
**************cell_has_proyectiles*********
*******************************************
*cell_has_proyectiles informs the user whether a given map cell
*contains one or more proyectiles of any kind.
*	INPUT:
*		1)coord_x :	row of the cell to be checked.
*		2)coord_y : column of the cell to be checked
*
*	OUTPUT:
*		a boolean that is true if the given cell contains a proyectile. False otherwise. 
*/
bool Map::cell_has_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_proyectiles();
}
/******************************************
**************cell_has_players*************
*******************************************
*cell_has_players informs the user whether a given map cell
*contains one or more players.
*	INPUT:
*		1)coord_x :	row of the cell to be checked.
*		2)coord_y : column of the cell to be checked
*
*	OUTPUT:
*		a boolean that is true if the given cell contains a player. False otherwise.
*/
bool Map::cell_has_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_players();
}
/******************************************
**************cell_has_enemies*************
*******************************************
*cell_has_enemiesinforms the user whether a given map cell
*contains one or more enemies.
*	INPUT:
*		1)coord_x :	row of the cell to be checked.
*		2)coord_y : column of the cell to be checked
*
*	OUTPUT:
*		a boolean that is true if the given cell contains an enemy. False otherwise.
*/
bool Map::cell_has_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).has_enemies();
}
/******************************************
**************get_cell*********************
*******************************************
*get_cell returns a MapCell object that contains 
*all the MapThings for a given map cell.
*	INPUT:
*		1)coord_x :	row of the cell of which the MapCell is needed.
*		2)coord_y : column of the cell of which the MapCell is needed. 
*
*	OUTPUT:
*		a MapCell with the characteristics mentioned in the method description.
*/
MapCell Map::get_cell(int coord_x, int coord_y) {
	return map_cells[coord_x][coord_y];
}
/******************************************
**************clear************************
*******************************************
*clear removes all MapThings from the map. 
*Note that it only removes MapThings, so that all MapCells on the map
*will remain untouched an hence should not be created again to place anything inside the map again.
*	INPUT:
*		1) void.
*
*	OUTPUT:
*		void.
*/
void Map::clear()
{
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			get_cell(i, j).clear();
}
/******************************************
***************get_cell_enemies************
*******************************************
*get_cell_enemies returns a vector containing all enemies contained on a given map cell.
*Note that the given map cell will still contain the enemies after this method is called.
*	INPUT:
*		1) coord_x : row of the cell from which the user wants to retrieve all enemies.
*		2) coord_y : column of the cell from which the user wants to retrieve all enemies.
*	OUTPUT:
*		a vector of Enemy pointers containing all enemies for the given map cell.
*/
std::vector<Enemy*> Map::get_cell_enemies(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_enemies();
}
/******************************************
*********cell_has_enemy_proyectiles********
*******************************************
*cell_has_enemy_proyectiles informs the user whether a given cell contains 
*one or more proyectiles that could kill a player 
*(a proyectile created by an enemy, hence an enemy proyectile) 
*	INPUT:
*		1)coord_x : row of the cell to be checked.
*		2)coord_y : column of the cell to be checked.
*	OUTPUT:
*		a boolean that is true if the cell contains any enemy proyectiles. False otherwise
*/
bool Map::cell_has_enemy_proyectiles(int coord_x, int coord_y)
{
	if (cell_has_proyectiles(coord_x, coord_y)) {
		std::vector<Proyectile*> proyectiles = get_cell_proyectiles(coord_x, coord_y);
		for (std::vector<Proyectile*>::iterator it = proyectiles.begin(); it != proyectiles.end(); ++it) {
			if ((*it)->is_fireball()) 
				return true;
		}
	}
	
	return false;

}
/******************************************
*********cell_has_player_proyectiles********
*******************************************
*cell_has_player_proyectiles informs the user whether a given cell contains
*one or more proyectiles that could kill an enemy
*(a proyectile created by a player, hence a player proyectile)
*	INPUT:
*		1)coord_x : row of the cell to be checked.
*		2)coord_y : column of the cell to be checked.
*	OUTPUT:
*		a boolean that is true if the cell contains any player proyectiles. False otherwise
*/
bool Map::cell_has_player_proyectiles(int coord_x, int coord_y)
{
	if (cell_has_proyectiles(coord_x, coord_y)) {
		std::vector<Proyectile*> proyectiles = get_cell_proyectiles(coord_x, coord_y);
		for (std::vector<Proyectile*>::iterator it = proyectiles.begin(); it != proyectiles.end(); ++it) {
			if ((*it)->is_snowball())
				return true;
		}
	}
	return false;

}
/******************************************
*************cell_has_floor****************
*******************************************
*cell_has_floor informs the user whether a given cell contains floor that prevents 
*movement to that cell or not.
*	INPUT:
*		1)coord_x : row of the cell to be checked.
*		2)coord_y : column of the cell to be checked.
*	OUTPUT:
*		a boolean that is true if the cell contains a 'floor' MapThing. False otherwise.
*/
bool Map::cell_has_floor(int coord_x, int coord_y)
{
	return get_cell(coord_x, coord_y).has_floor();
}
/******************************************
**************get_cell_players*************
*******************************************
* get_cell_players returns a vector of player pointers 
* that contains all players that are currently inside a given cell.
* the user should call the method cell_has_players before calling this function to make
* sure that the cell has players.
*	INPUT:
*		1)coord_x : row of the cell from which the players will be retrieved.
*		2)coord_y : column of the cell from which the players will be retrieved.
*	OUTPUT:
*		a vector containing player pointers to all the players that are currently on the given map cell.
*/
std::vector<Player*> Map::get_cell_players(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_players();
}
/******************************************
*************get_cell_proyectiles**********
*******************************************
*get_cell_proyectiles returns a vector of proyectiles pointers 
* that contains all proyectiles that are currently inside a given cell.
* the user should call the method cell_has_proyectiles before calling this function to make
* sure that the cell has proyectiles.
*	INPUT:
*		1) coord_x : row of the cell from which the players will be retrieved.
*		2) coord_y : column of the cell from which the players will be retrieved.
*	OUTPUT:
*		a vector containing proyectiles pointers to all the proyectiles that are currently on the given map cell.
*/
std::vector<Proyectile*> Map::get_cell_proyectiles(int coord_x, int coord_y) {
	return get_cell(coord_x, coord_y).get_proyectiles();
}
/******************************************
**************get_from_map*****************
*******************************************
*get_from_map retrieves a MapThing pointer from the map.
*	INPUT:
		1) id : id of the MapThing to be retrieved from the map.
*	OUTPUT:
*		MapThing pointer retrieved from the map.
*/
MapThing * Map::get_from_map(unsigned int id) {
	MapThing* gotten = NULL;
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_columns; j++)
			if ((gotten = get_cell(i, j).get_id(id)) != NULL)
				break;

	return gotten;
}
/******************************************
**************get_from_map*****************
*******************************************
*get_from_map is an internal function for map. 
*given the cell coordinates and the z coordinate (the position of the MapThing inside the MapCell array)
*it retrieves the MapThing from the map.
*	INPUT:
		1)coord_x :  
		2)coord_y : 
		3)coord_z :
*	OUTPUT:
*
*/
MapThing * Map::get_from_map(int coord_x, int coord_y, int coord_z)
{
	return get_cell(coord_x, coord_y).get_floor(coord_z);
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
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
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
bool Map::delete_from_map(MapThing * thing) {

	bool successfully_deleted = false;

	if (successfully_deleted = get_cell(thing->pos_x, thing->pos_y).delete_map_thing(thing)){
		delete_from_map_thing_vectors(thing);
		thing->pos_x = -1;
		thing->pos_y = -1;
	}

	return successfully_deleted;
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
void Map::print_cell(int coord_x, int coord_y)
{
	get_cell(coord_x, coord_y).print();
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
const char * Map::get_last_loaded_distribution()
{
	return original_distribution;
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
Position Map::find_next_movement_4_shortest_path(int from_x, int from_y, int to_x, int to_y)
{
	return dijkstra_manager->get_next_movement_shortest_path(from_x, from_y, to_x, to_y);
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
 int Map::get_number_of_rows()
{
	return number_of_rows;
}
 /******************************************
 ****************************
 ******************************************
 *

 *	INPUT:
 1)
 *	OUTPUT:
 *
 */
 int Map::get_number_of_columns()
 {
	 return number_of_columns;
 }
 /******************************************
 ****************************
 ******************************************
 *

 *	INPUT:
 1)
 *	OUTPUT:
 *
 */
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
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
bool Map::move_map_thing(MapThing * thing, int final_x, int final_y)
{
	return move_id(thing->id, final_x, final_y);
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
void Map::place_on_map(int coord_x, int coord_y, MapThing* thing) {
	MapCell cell = get_cell(coord_x, coord_y);
	cell.place_on_cell(thing);
	thing->pos_x = coord_x;
	thing->pos_y = coord_y;
	place_on_map_thing_vectors(thing);
	
}
/******************************************
****************************
******************************************
*

*	INPUT:
1)
*	OUTPUT:
*
*/
void Map::place_on_map(int coord_x, int coord_y, Item_type identifyer, Sense_type direction)
{
	place_on_map(coord_x, coord_y, map_filler.create_map_thing(identifyer, direction));
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

	for (int i = 0; i < number_of_columns*number_of_rows; i++) {
		int fil = i / number_of_columns;
		int col = i % number_of_columns;
		MapThing * new_thing = map_filler.create_map_thing((unsigned char)map_string[i]);
		place_on_map(fil, col, new_thing);
	}
	dijkstra_manager = new MapDijkstraMachine(this);
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

void Map::register_enemies_event_queue(ALLEGRO_EVENT_QUEUE * enemies_ev_queue) {
	map_filler.register_enemies_event_queue(enemies_ev_queue);
}
void Map::register_proyectiles_event_queue(ALLEGRO_EVENT_QUEUE * proyectiles_ev_queue) {
	map_filler.register_proyectiles_event_queue(proyectiles_ev_queue);
}
EA_info * Map::get_initial_enemy_actions() {
	static int loading_EA_number = 0;
	EA_info * returnable_EA = new  EA_info();

	if (returnable_EA->finished_loading = (loading_EA_number >= all_enemies->size()) ) 
		loading_EA_number = 0;
	else {
		returnable_EA = (all_enemies->at(loading_EA_number))->act();
		loading_EA_number++;
	}
	return returnable_EA;
}

