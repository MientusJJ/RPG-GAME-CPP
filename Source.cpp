#include "Game.h"

int main() {
	unique_ptr<Game> myGame;
	myGame = make_unique<Game>();
	myGame->play();
	system("pause");
	return 0;
}
