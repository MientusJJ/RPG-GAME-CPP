#ifndef GAME_H
#define GAME_H
#pragma once
#include "Chambers.h"
#include "Observer.h"
class Game
{
public:
	Game();
	~Game();
	void play();
	shared_ptr<ChamberNode> prepareMap(shared_ptr<Hero>& hero);
	void chamberTransitionFunction(shared_ptr<ChamberNode>& start, shared_ptr<Hero>& h);
private:
	shared_ptr<Hero> hero;
	shared_ptr<Observer> o;
};
#endif
