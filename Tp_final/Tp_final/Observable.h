#pragma once
#include <vector> 
#include "Observer.h"


class Observable
{
public:

	Observable();
	~Observable();
	
	void add_observer(Observer* ob);
	void notify_obs();
	
private:
	std::vector<Observer*> obs;
};
