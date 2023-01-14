#include "Controller.h"


// Klasy wchodzące w skład kontrolera:
// Game, ActionVisitor, Chamber, Event, DescriptionVisitor, Chest
// (+ wszystkie klasy po nich dziedziczące)
void Controller::playGame() {
    unique_ptr<Game> newGame;
    newGame = make_unique<Game>();
    newGame->play();
    system("pause");
}


int main() {
    unique_ptr<Controller> myGame;
    myGame->playGame();


	return 0;
}
