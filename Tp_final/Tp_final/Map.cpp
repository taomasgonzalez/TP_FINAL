#include "Map.h"


Map::Map(int number_of_rows, int number_of_columns)
{
	new [number_of_rows][number_of_columns];
}


Map::~Map()
{
}

//bool Map::cell_has_X(int coord_x, int coord_y, Map_Thing_id thing_id) {
	//thing vector = this->get_cell(coord_x,coord_y);
	//for(){
	//	if((*it)->id == thing_id){
	//		return true;
	//	}
	//}
	//return false;
//}