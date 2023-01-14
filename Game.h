#ifndef GAME_H
#define GAME_H
#pragma once
#include "Chambers.h"
#include "Views.cpp"

// Controller
class Game
{
public:
	Game();
	~Game();
	void play();
    unique_ptr<TXTView> ViewInterface;
	shared_ptr<ChamberNode> prepareMap();
	void chamberTransitionFunction(shared_ptr<ChamberNode>& start);
private:
	shared_ptr<Hero> hero;
	shared_ptr<Observer> o;
};
#endif
