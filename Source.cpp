#include "Game.h"

int main() {
	Game *myGame;
	myGame = new Game;
	myGame->play();
	system("pause");
	return 0;
}
