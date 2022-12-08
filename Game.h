#ifndef GAME_H
#define GAME_H
#pragma once
#include "Chambers.h"
class Game
{
public:
	Game();
	~Game();
	void play();
private:
	shared_ptr<Hero> hero;
};
#endif
