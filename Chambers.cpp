#include <iostream>
#include <cstdlib>
#include "Chambers.h"
using namespace std;
int numOfChamber;
int chambersWithoutMonsters;
int chambersWithoutTrader;


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
	cout << "You found " << coins << " gold in the chest" << endl;
	h->setMoney(h->getMoney() + coins);

	cout << "There is also an item in chest" << endl;
	cout << "Your current item: " << endl;
	h->showOneItem(item->getType(), h->getProf());
	cout << endl;
	cout << "The item in the chest: " << endl;
	showItemDetails(item,h->getProf());
	
	cout << "Do you want to replace your item with a new found one? (Y/N)" << endl;

	char decision;
    while (true) {
        cin >> decision;

        if (decision == 'Y')
            h->ChangeEQ(item);

        if (decision == 'Y' || decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
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
	h->fight(boss_monster,1);
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

	if (numOfChamber < 19)
	{
		cout << "Currently You are in Chamber number: " << numOfChamber << endl;
		numOfChamber++;

		char showSth;
        while (true) {
            cout << "Do you want to see your EQ or statistics? (equipment - E, statistics - S, nothing - N)" << endl;
            cin >> showSth;

            if (showSth == 'E')
                h->showEQ();
            else if (showSth == 'S')
                h->showStatistics();
            else if (showSth == 'N')
                break;
            else
                cout << "Character not recognized, please retype" << endl;
        }

		cout << "Where do you want to go? (left - L, right - R)" << endl;

		int left = rand() % 7;
		int right = rand() % 7;
		int next;

        char direction;
        while (true) {
            cin >> direction;

            if (direction == 'L') {
                next = left;
                break;
            }
            else if (direction == 'R') {
                next = right;
                break;
            }
            else
                cout << "Character not recognized, please retype" << endl;
        }

		if (next == 0 || chambersWithoutMonsters == 3)
			next_chamber = new MonsterRoom(h);
		else if (next == 1 || chambersWithoutTrader == 8)
			next_chamber = new TraderRoom(h);
		else if (next == 2)
			next_chamber = new TreasureRoom(h);
		else if (next == 3)
			next_chamber = new HealthRoom(h);
		else if (next == 4)
			next_chamber = new PotionRoom(h);
		else if (next == 5)
			next_chamber = new TrapRoom(h);
		else
			next_chamber = new EmptyRoom(h);
	}
	else if (numOfChamber == 19) {
        numOfChamber++;

        cout << "After this room, the next one will be with a boss" << endl;
        cout << "The chambers have open doors, so you can see what is inside" << endl;
        cout << "Where do you want to go? (HealthRoom - L, TraderRoom - R)" << endl;

        char direction;
        while (true) {
            cin >> direction;

            if (direction == 'L') {
                next_chamber = new HealthRoom(h);
				break;
            }
            else if (direction == 'R') {
                next_chamber = new TraderRoom(h);
				break;
            }
            else
                cout << "Character not recognized, please retype" << endl;
        }
    }
    else {
        cout << "The last chamber is ahead of you - BossChamber" << endl;

        char decision;
        while (true) {
            cout << "Do you want to face the boss? (Y/N)" << endl;
            cin >> decision;

            if (decision == 'Y')
                break;
            else if (decision == 'N')
                cout << "You can't give up now, you are so close to your desired goal" << endl;
            else
                cout << "Character not recognized, please retype" << endl;
        }

        next_chamber = new BossChamber(h);
    }


	return next_chamber;
}


NormalChamber::NormalChamber(Hero *h) : PassageChamber(h) {}
Chamber* NormalChamber::takeAction(Hero* h) { return nullptr; }

SafeChamber::SafeChamber(Hero *h) : PassageChamber(h) {}
Chamber* SafeChamber::takeAction(Hero* h) { return nullptr; }


MonsterRoom::MonsterRoom(Hero *h) : NormalChamber(h) {
    chambersWithoutMonsters = 0;
    chambersWithoutTrader++;
	chest = new Chest(h);
	normal_monster = new monster(h->getlevel());
}

Chamber* MonsterRoom::takeAction(Hero *h) {
	cout << "You have entered the room with the monster" << endl;
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	cout << "Are you fighting or running? (F/R)" << endl;
	char action;

    while (true) {
        cin >> action;

        if (action == 'F') {
            fight(h);
            break;
        }
        else if (action == 'R') {
            runAway(h);
            break;
        }
        else
            cout << "Character not recognized, please retype" << endl;
    }


	return goNext(h);
}

void MonsterRoom::fight(Hero *h) {
	h->fight(normal_monster,0);
	if (h->getcurrentHealth() > 0)
	{
		h->levelup();
		cout << "You have leveled up. Your current level is: " << hero->getlevel() << endl;
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl << endl;
		cout << "After defeating the monster you saw the box in the corner of the room" << endl;
		cout << "Do you want to open it? (Y/N)" << endl;
		char player_decision;

        while (true) {
            cin >> player_decision;
            if (player_decision == 'Y')
                chest->openBox(h);

            if (player_decision == 'Y' || player_decision == 'N')
                break;
            else
                cout << "Character not recognized, please retype" << endl;
        }
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


TrapRoom::TrapRoom(Hero *h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

Chamber* TrapRoom::takeAction(Hero *h) {
	getDamage(h);
	return goNext(h);
}

void TrapRoom::getDamage(Hero *h) {
	cout << "There was a trap in the room that has hurted you" << endl;
	h->getDamage(h->getmaxHealth() * 0.2);
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


PotionRoom::PotionRoom(Hero *h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

Chamber* PotionRoom::takeAction(Hero *h) {
	cout << "In the room you came to there is a mysterious potion with unknown properties" << endl;
	cout << "Do you want to drink it? (Y/N)" << endl;
	char player_decision;

    while (true) {
        cin >> player_decision;

        if (player_decision == 'Y')
            drinkPotion(h);

        if (player_decision == 'Y' || player_decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }

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
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
	chest = new Chest(h);
}

Chamber* TreasureRoom::takeAction(Hero *h) {
	openBox(h);
	return goNext(h);
}

void TreasureRoom::openBox(Hero *h) {
	cout << "There is a box in the room, do you want to open it? (Y/N)" << endl;
	char player_decision;

    while (true) {
        cin >> player_decision;

        if (player_decision == 'Y')
            chest->openBox(h);

        if (player_decision == 'Y' || player_decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}


HealthRoom::HealthRoom(Hero *h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

Chamber* HealthRoom::takeAction(Hero *h) {
	healthYourself(h);
	return goNext(h);
}

void HealthRoom::healthYourself(Hero *h) {
	cout << "You came to the room with the fountain of life, after drinking the magic water you regain all health points" << endl;
	h->setcurrentHealth(h->getmaxHealth());
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


TraderRoom::TraderRoom(Hero* h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader = 0;
	item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
};

Chamber* TraderRoom::takeAction(Hero* h) {
	cout << "You came to a room with a merchant who offers you to see his items" << endl;
	cout << "Do you want to watch them? (Y/N)" << endl;
	char player_decision;

    while (true) {
        cin >> player_decision;

        if (player_decision == 'Y')
            seeItems(h);

        if (player_decision == 'Y' || player_decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }

	return goNext(h);
}

void TraderRoom::seeItems(Hero* h) {
	h->showEQ();
	cout << "item 1:" << endl;
	showItemDetails(item1,h->getProf());
	cout << "price: " << item1->getValue() << endl << endl;

	cout << "item 2:" << endl;
	showItemDetails(item2, h->getProf());
	cout << "price: " << item2->getValue() << endl << endl;

	cout << "item 3:" << endl;
	showItemDetails(item3, h->getProf());
	cout << "price: " << item3->getValue() << endl << endl;
	cout << "Your balance: " << h->getMoney() << endl;
	cout << "Do you want to buy something? (Y/N)" << endl;
	
	char player_decision;

    while (true) {
        cin >> player_decision;

        if (player_decision == 'Y')
            buyItem(h);

        if (player_decision == 'Y' || player_decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}

void TraderRoom::buyItem(Hero* h) {
	bool wantToBuy = true;
	int num;
	char player_decision;
	bool bought1 = false, bought2 = false, bought3 = false;

	while (wantToBuy)
	{
		cout << "Enter the number of the item you want to buy:" << endl;
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
			cout << "Your balance: " << h->getMoney() << endl;
			cout << "Do you want to buy anything else? (Y/N)" << endl;

            while (true) {
                cin >> player_decision;

                if (player_decision == 'N')
                    wantToBuy = false;

                if (player_decision == 'Y' || player_decision == 'N')
                    break;
                else
                    cout << "Character not recognized, please retype" << endl;
            }
		}
		else {
			cout << "You already bought all items from the merchant..." << endl;
			wantToBuy = false;
		}
	}
}


EmptyRoom::EmptyRoom(Hero *h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

Chamber* EmptyRoom::takeAction(Hero* h) {
	cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
	return goNext(h);
}


StartingRoom::StartingRoom(Hero *h) : SafeChamber(h) {
	numOfChamber = 0;
    chambersWithoutMonsters = 0;
    chambersWithoutTrader = 0;
}

Chamber* StartingRoom::takeAction(Hero *h) {
	cout << "Your adventure begins here" << endl;
	return goNext(h);
}