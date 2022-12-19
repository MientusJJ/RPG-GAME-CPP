#ifndef GAME_H
#define GAME_H
#pragma once
#include "Character.h"
#include "Chambers.h"
class Game
{
public:
	Game();
	~Game();
	void play();
    ChamberNode* prepareMap(Hero* hero);
    void chambersTransitionFunction(ChamberNode* start, Hero* h);
private:
	Hero *hero;
};
#endif
