#pragma once
#include <vector> 
#include "Observer.h"

enum class Observable_type  {COMMUNICATION,SCENARIO,FSM,ALLEGRO};

class Observable
{
public:

	Observable(Observable_type type);
	~Observable();
	
	void add_observer(Observer* ob);
	void notify_obs();
	Observable_type give_me_my_type();
	
private:
	std::vector<Observer*> obs;

protected:
	Observable_type my_type;

};


/******************************************************************************
*******************************************************************************
							COM_OBSERVABLE CLASS
*******************************************************************************
*******************************************************************************/
class COM_Observable : public Observable
{
public:
	COM_Observable();

private:

};

