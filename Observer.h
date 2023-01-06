#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>
#include "Names.h"
#include "Chambers.h"

class Observer
{
public:
	//void add(shared_ptr<Chamber>);
	void setTrue();
	virtual ~Observer();
private:
	//std::vector<shared_ptr<Chamber>> listofChambers;
};

#endif