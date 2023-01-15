#ifndef GAME_H
#define GAME_H
#pragma once
#include "Chambers.h"

// Controller
class Game
{
public:
	Game();
	~Game();
	void play();
    shared_ptr<View> view;
	shared_ptr<ChamberNode> prepareMap();
	void chamberTransitionFunction(shared_ptr<ChamberNode>& start, shared_ptr<View> view);
private:
	shared_ptr<Hero> hero;
	shared_ptr<Observer> o;
    void heroSetClass(shared_ptr<View> view);
    void heroSetName(shared_ptr<View> view);
};
#endif
