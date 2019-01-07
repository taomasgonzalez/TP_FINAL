#include "Observable.h"

Observable::Observable()
{
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

