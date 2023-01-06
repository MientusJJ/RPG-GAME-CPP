#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include "Names.h"
#include <iostream>
class Observer
{

public:
	//void add(shared_ptr<Chamber>);
	void setTrue();
	bool check();
private:
	bool endik{false};
	bool getEndik();
};

#endif