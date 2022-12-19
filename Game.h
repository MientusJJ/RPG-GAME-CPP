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
private:
	Hero *hero;
};
#endif
