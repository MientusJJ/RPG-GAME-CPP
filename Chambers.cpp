#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Chambers.h"
using namespace std;
int numOfChamber;


ItemType getRandomItemType(Hero* h) {
	int type = rand() % 4;

	if (h->getProf() == warrior) {
		type += rand() % 2;
	}

	ItemType itemType;
	if (type == 0)
		itemType = weapon;
	else if (type == 1)
		itemType = armor;
	else if (type == 2)
		itemType = headgear;
	else if (type == 3)
		itemType = talisman;
	else
		itemType = shield;

	return itemType;
}


Chest::Chest(Hero* h) {
	ItemType itemType = getRandomItemType(h);

	item = ItemFactory::createItem(h->getlevel(), itemType, h->getProf());
}

void Chest::openBox(Hero* h) {
	int coins = rand() % (h->getlevel() * 100);
	cout << "You found " << coins << " gold in the chest";
	h->setMoney(h->getMoney() + coins);

	cout << "There is also an item in chest" << endl;
	showItemDetails(*item);
	cout << "Your current item: " << endl;
	h->showOneItem(item->getType(), h->getProf());
	cout << "Do you want to take this item? (Y/N)" << endl;

	char decision;
	cin >> decision;

	if (decision == 'Y')
		h->ChangeEQ(item);
}


Chamber::Chamber(Hero* h) {
	chamber_ID = rand() % 1000;
	hero = h->getInstance();
}

Chamber* Chamber::takeAction(Hero *h) { return nullptr; }

int Chamber::getChamberID() {
	return chamber_ID;
}

string Chamber::getName() {
	return name;
}


BossChamber::BossChamber(Hero *h) : Chamber(h) {
	int lvl = h->getlevel() * 3 / 2;
	boss_monster = new monster(lvl, "Great BOSS");
}

Chamber* BossChamber::takeAction(Hero *h) {
	cout << "You have entered the boss's chamber" << endl;
	cout << "The last and hardest fight is ahead of you" << endl;
	finalFight(h);

	if (h->getcurrentHealth() > 0)
		cout << "Congratulations! You finished the game" << endl;
	else
		cout << "It was very close..." << endl;

	return nullptr;
}

void BossChamber::finalFight(Hero *h) {
	h->fight(boss_monster);
}


PassageChamber::PassageChamber(Hero *h) : Chamber(h) {}

Chamber* PassageChamber::takeAction(Hero* h) { return nullptr; }

Chamber* PassageChamber::goNext(Hero* h) {
	Chamber* next_chamber;

	if (h->getcurrentHealth() == 0) {
		cout << "YOU DEAD" << endl;
		cout << "THE GAME IS OVER" << endl;
		return nullptr;
	}

	if (numOfChamber < 20)
	{
		cout << "Currently You are in Chamber number " << numOfChamber << endl;
		numOfChamber++;
		cout << "Do you want to see your EQ or statistics? (equipment - E, statistics - S, nothing - N)" << endl;
		char showSth;
		cin >> showSth;

		if (showSth == 'E')
			h->showEQ();
		else if (showSth == 'S')
			h->showStatistics();

		cout << "Where do you want to go? (left - L, right - R)" << endl;
		char direction;
		cin >> direction;

		int left = rand() % 7;
		int right = rand() % 7;
		int next;

		if (direction == 'L')
			next = left;
		else if (direction == 'R')
			next = right;

		if (next == 0)
			next_chamber = new MonsterRoom(h);
		else if (next == 1)
			next_chamber = new TrapRoom(h);
		else if (next == 2)
			next_chamber = new TreasureRoom(h);
		else if (next == 3)
			next_chamber = new HealthRoom(h);
		else if (next == 4)
			next_chamber = new PotionRoom(h);
		else if (next == 5)
			next_chamber = new TraderRoom(h);
		else
			next_chamber = new EmptyRoom(h);
	}
	else
		next_chamber = new BossChamber(h);


	return next_chamber;
}


NormalChamber::NormalChamber(Hero *h) : PassageChamber(h) {}
Chamber* NormalChamber::takeAction(Hero* h) { return nullptr; }

SafeChamber::SafeChamber(Hero *h) : PassageChamber(h) {}
Chamber* SafeChamber::takeAction(Hero* h) { return nullptr; }


MonsterRoom::MonsterRoom(Hero *h) : NormalChamber(h)
{
	chest = new Chest(h);
	normal_monster = new monster(h->getlevel());
}

Chamber* MonsterRoom::takeAction(Hero *h) {
	cout << "You have entered the room with the monster" << endl;
	cout << "Are you fighting or running? (F/R)" << endl;
	char action;
	cin >> action;

	if (action == 'F')
		fight(h);
	else if (action == 'R')
		runAway(h);

	return goNext(h);
}

void MonsterRoom::fight(Hero *h) {
	h->fight(normal_monster);
	if (h->getcurrentHealth() > 0)
	{
		h->levelup();
		cout << "You have leveled up. Your current level is: " << hero->getlevel() << endl;
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
		cout << "After defeating the monster you saw the box in the corner of the room" << endl;
		cout << "Do you want to open it? (Y/N)" << endl;
		char player_decision;
		cin >> player_decision;
		if (player_decision == 'Y')
			chest->openBox(h);
	}
}

void MonsterRoom::runAway(Hero *h) {
	int chance = rand() % 10;

	if (chance < 3) {
		cout << "While escaping you got hit by a monster" << endl;
		h->getDamage(h->getcurrentHealth() * 0.2);
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	}
	else
		cout << "You escaped the monster" << endl;
}


TrapRoom::TrapRoom(Hero *h) : NormalChamber(h) {}

Chamber* TrapRoom::takeAction(Hero *h) {
	getDamage(h);
	return goNext(h);
}

void TrapRoom::getDamage(Hero *h) {
	cout << "There was a trap in the room that has hurted you" << endl;
	h->getDamage(h->getmaxHealth() * 0.2);
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


PotionRoom::PotionRoom(Hero *h) : NormalChamber(h) {}

Chamber* PotionRoom::takeAction(Hero *h) {
	cout << "In the room you came to there is a mysterious potion with unknown properties" << endl;
	cout << "Do you want to drink it? (Y/N)" << endl;
	char player_decision;
	cin >> player_decision;
	if (player_decision == 'Y')
		drinkPotion(h);

	return goNext(h);
}

void PotionRoom::drinkPotion(Hero *h) {
	int drawn_num = rand() % 2;

	if (drawn_num == 0) {
		h->setcurrentHealth(h->getmaxHealth());
		cout << "Your health has been restored" << endl;
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	}
	else {
		h->getDamage(h->getmaxHealth() * 0.3);
		cout << "The potion was poisoned. You lost " << int(h->getmaxHealth() * 0.3) << " health" << endl;
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	}
}


TreasureRoom::TreasureRoom(Hero *h) : SafeChamber(h) {
	chest = new Chest(h);
}

Chamber* TreasureRoom::takeAction(Hero *h) {
	openBox(h);
	return goNext(h);
}

void TreasureRoom::openBox(Hero *h) {
	cout << "There is a box in the room, do you want to open it? (Y/N)";
	char player_decision;
	cin >> player_decision;
	if (player_decision == 'Y')
		chest->openBox(h);
}


HealthRoom::HealthRoom(Hero *h) : SafeChamber(h) {}

Chamber* HealthRoom::takeAction(Hero *h) {
	healthYourself(h);
	return goNext(h);
}

void HealthRoom::healthYourself(Hero *h) {
	cout << "You came to the room with the fountain of life, after drinking the magic water you regain all health points" << endl;
	h->setcurrentHealth(h->getmaxHealth());
}


TraderRoom::TraderRoom(Hero* h) : SafeChamber(h) {
	item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
};

Chamber* TraderRoom::takeAction(Hero* h) {
	cout << "You came to a room with a merchant who offers you to see his items" << endl;
	cout << "Do you want to watch them? (Y/N)" << endl;
	char player_decision;
	cin >> player_decision;
	if (player_decision == 'Y')
		seeItems(h);

	return goNext(h);
}

void TraderRoom::seeItems(Hero* h) {
	h->showEQ();
	cout << "item 1:" << endl;
	showItemDetails(*item1);
	cout << "price: " << item1->getValue() << endl << endl;

	cout << "item 2:" << endl;
	showItemDetails(*item2);
	cout << "price: " << item2->getValue() << endl << endl;

	cout << "item 3:" << endl;
	showItemDetails(*item3);
	cout << "price: " << item3->getValue() << endl << endl;
	cout << "Your balance: " << h->getMoney() << endl;
	cout << "Do you want to buy something? (Y/N)" << endl;
	
	char player_decision;
	cin >> player_decision;
	if (player_decision == 'Y')
		buyItem(h);
}

void TraderRoom::buyItem(Hero* h) {
	bool wantToBuy = true;
	int num;
	char player_decision;
	bool bought1 = false, bought2 = false, bought3 = false;

	while (wantToBuy)
	{
		cout << "Enter the number of the item you want to buy: ";
		cin >> num;

		if (num == 1) {
			if (!bought1) {
				if (h->getMoney() >= item1->getValue()) {
					h->setMoney(h->getMoney() - item1->getValue());
					h->ChangeEQ(item1);
					bought1 = true;
				}
				else
					cout << "You do not have enough coins" << endl;
			}
			else {
				cout << "You have already bought this item" << endl;
			}
		}
		else if (num == 2) {
			if (!bought2) {
				if (h->getMoney() >= item2->getValue()) {
					h->setMoney(h->getMoney() - item2->getValue());
					h->ChangeEQ(item2);
					bought2 = true;
				}
				else
					cout << "You do not have enough coins" << endl;
			}
			else {
				cout << "You have already bought this item" << endl;
			}
		}
		else if (num == 3) {
			if (!bought3) {
				if (h->getMoney() >= item3->getValue()) {
					h->setMoney(h->getMoney() - item3->getValue());
					h->ChangeEQ(item3);
					bought3 = true;
				}
				else
					cout << "You do not have enough coins" << endl;
			}
			else {
				cout << "You have already bought this item" << endl;
			}
		}
		else {
			cout << "Invalid item number, try again" << endl;
		}

		if (!bought1 || !bought2 || !bought3) {
			cout << "Do you want to buy anything else? (Y/N)" << endl;
			cin >> player_decision;

			if (player_decision == 'N')
				wantToBuy = false;
		}
		else {
			cout << "You already bought all items from the merchant..." << endl;
			wantToBuy = false;
		}
	}
}


EmptyRoom::EmptyRoom(Hero *h) : SafeChamber(h) {}

Chamber* EmptyRoom::takeAction(Hero* h) {
	cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
	return goNext(h);
}


StartingRoom::StartingRoom(Hero *h) : SafeChamber(h) {

	numOfChamber = 0;
}

Chamber* StartingRoom::takeAction(Hero *h) {
	cout << "Your adventure begins here" << endl;
	return goNext(h);
}