#include "DRAW.h"
#include <vector>



DRAW::DRAW()
{
	//this->TimerDraw = NULL;
	//this->QueueDraw = NULL;
}


DRAW::~DRAW()
{
}

void DRAW::createObjGraf(double ID, PLAYER_TYPE type)
{
	Obj_Graf_Player *obj = new Obj_Graf_Player(ID, type);
	this->mapObjGraf[ID] = obj;
}

void DRAW::createObjGraf(double ID, ENEMY_TYPE type)
{
	Obj_Graf_Enemy *obj = new Obj_Graf_Enemy(ID, type);
	this->mapObjGraf[ID] = obj;
}

void DRAW::createObjGraf(double ID, PROYECTILE_TYPE type)
{
	Obj_Graf_Projectile *obj = new Obj_Graf_Projectile(ID, type);
	this->mapObjGraf[ID] = obj;
}

void DRAW::draw()		
{
	vector<double> keys;

	for (map<double, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<double>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		if (this->mapObjGraf[*it]->isActive())										// si el objeto grafico esta activo
			this->mapObjGraf[*it]->draw();											// se dibuja
}

void DRAW::destroyObj(double ID)
{
	this->mapObjGraf[ID]->destroy();
}

void DRAW::destroyAll()
{
	vector<double> keys;

	for (map<double, Obj_Graf*>::iterator it = this->mapObjGraf.begin(); it != this->mapObjGraf.end(); ++it)		// creo un vector con todas las keys del mapa de O. graficos
		keys.push_back(it->first);

	for (vector<double>::iterator it = keys.begin(); it < keys.end(); it++)			// barro todos los elementos del mapa
		this->mapObjGraf[*it]->destroy();										// si el objeto grafico esta activo
}



//bool DRAW::init()
//{
//	bool ret = false;
//
//	if (this->TimerDraw = al_create_timer(1 / FPS))
//	{
//		if (this->QueueDraw = al_create_event_queue())
//			ret = true;
//		else
//		{
//			al_destroy_timer(this->TimerDraw);
//			ret = false;
//		}
//	}
//	else
//		ret = false;
//
//	if (ret)
//	{
//		al_register_event_source(this->QueueDraw, al_get_timer_event_source(this->TimerDraw));
//		al_start_timer(this->TimerDraw);
//	}
//
//	return ret;
//}