#include "Game.h"

Game::Game()
{
}
void Game::play()
{
	hero = Hero::getInstance();
	unique_ptr<Chamber>CurrentCham = make_unique<StartingRoom>(hero);
	while (CurrentCham != nullptr)
	{
		CurrentCham = CurrentCham->takeAction(hero);
	}
}
Game::~Game()
{
}