#pragma once
class Observable;

class Observer
{
public:
	Observer();
	~Observer();

	virtual void update() = 0;
};
