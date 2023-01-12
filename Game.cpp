#include "Game.h"

Game::Game()
{
}

void Game::play()
{
	hero = Hero::getInstance();
	o = make_shared<Observer>();
	hero->setObserver(o);
	shared_ptr<ChamberNode> start = prepareMap(hero);
	chamberTransitionFunction(start);
}

shared_ptr<ChamberNode> Game::prepareMap(shared_ptr<Hero>& hero)
{
	shared_ptr<ChamberNode> start = make_shared<ChamberNode>(make_shared<StartingRoom>(hero));
	shared_ptr<ChamberNode> n1 = make_shared<ChamberNode>(make_shared<MonsterRoom>(hero));
	shared_ptr<ChamberNode> n2 = make_shared<ChamberNode>(make_shared<TrapRoom>(hero));
	shared_ptr<ChamberNode> n3 = make_shared<ChamberNode>(make_shared<TraderRoom>(hero));
	shared_ptr<ChamberNode> n4 = make_shared<ChamberNode>(make_shared<EmptyRoom>(hero));
	shared_ptr<ChamberNode> n5 = make_shared<ChamberNode>(make_shared<TreasureRoom>(hero));
	shared_ptr<ChamberNode> n6 = make_shared<ChamberNode>(make_shared<HealthRoom>(hero));
	shared_ptr<ChamberNode> n7 = make_shared<ChamberNode>(make_shared<TreasureRoom>(hero));
	shared_ptr<ChamberNode> n8 = make_shared<ChamberNode>(make_shared<MonsterRoom>(hero));
	shared_ptr<ChamberNode> n9 = make_shared<ChamberNode>(make_shared<MonsterRoom>(hero));
	shared_ptr<ChamberNode> n10 = make_shared<ChamberNode>(make_shared<TrapRoom>(hero));
	shared_ptr<ChamberNode> n11 = make_shared<ChamberNode>(make_shared<TraderRoom>(hero));
	shared_ptr<ChamberNode> n12 = make_shared<ChamberNode>(make_shared<PotionRoom>(hero));
	shared_ptr<ChamberNode> n13 = make_shared<ChamberNode>(make_shared<HealthRoom>(hero));
	shared_ptr<ChamberNode> n14 = make_shared<ChamberNode>(make_shared<TraderRoom>(hero));
	shared_ptr<ChamberNode> boss = make_shared<ChamberNode>(make_shared<BossChamber>(hero));
	start->option1 = n1;
	start->option2 = n2;
	n1->option1 = n3;
	n1->option2 = n4;
	n2->option1 = n4;
	n2->option2 = n5;
	n3->option1 = n6;
	n4->option1 = n7;
	n4->option2 = n8;
	n5->option1 = n9;
	n6->option1 = n10;
	n7->option1 = n10;
	n8->option1 = n11;
	n9->option1 = n11;
	n9->option2 = n12;
	n10->option1 = n13;
	n11->option1 = n13;
	n12->option1 = n14;
	n13->option1 = boss;
	n14->option1 = boss;

	return start;
}

void Game::chamberTransitionFunction(shared_ptr<ChamberNode>& start)
{
	shared_ptr<ChamberNode> curr = start;
    shared_ptr<ActionVisitor> visitor(new ActionVisitor());

	while (true)
	{
        curr->current->action(*visitor);

		if (this->o->check())
		{
			break;
		}
		cout << endl;
		if (curr->option1 == nullptr)
			break;
		else if (curr->option2 == nullptr)
		{
			cout << "There is only one way out of this room..." << endl;
			cout << "Type L or R to go next" << endl;
			char choice;
			cin >> choice;
			choice = makeBig(choice);
			while (choice != 'L' && choice != 'R') {
				cout << "Character not recognized, please retype" << endl;
				cin >> choice;
				choice = makeBig(choice);
			}
			curr = curr->option1;
		}
		else {
			cout << "You see two passages - which way do you want to go?" << endl;
			cout << "[L] left" << endl;
			cout << "[R] right" << endl;

			char choice;
			cin >> choice;
			choice = makeBig(choice);
			while (choice != 'L' && choice != 'R') {
				cout << "Character not recognized, please retype" << endl;
				cin >> choice;
				choice = makeBig(choice);
			}

			if (choice == 'L')
				curr = curr->option1;
			else
				curr = curr->option2;
		}

		cout << endl;
	}
}

Game::~Game()
{
}