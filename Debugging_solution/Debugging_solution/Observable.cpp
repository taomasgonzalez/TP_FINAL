#include "Observable.h"

Observable::Observable(Observable_type type)
{
	this->my_type = type;
}


Observable::~Observable()
{
}

void Observable::add_observer(Observer* ob) {
	obs.push_back(ob);
}
void Observable::notify_obs() {
	for (std::vector<Observer*>::iterator it = obs.begin(); it != obs.end(); ++it) {
		(*it)->update();
	}
}

Observable_type Observable::give_me_my_type()
{
	return this->my_type;
}

COM_Observable::COM_Observable() : Observable(Observable_type::COMMUNICATION) {
	
};


