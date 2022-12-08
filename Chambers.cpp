#include <iostream>
#include <cstdlib>
#include "Chambers.h"
#include "Items.h"
using namespace std;
int numOfChamber;
int chambersWithoutMonsters;
int chambersWithoutTrader;

ItemType getRandomItemType( shared_ptr<Hero>&h) {
	int type = static_cast<int>(round(makeRand(0, 3)));

	if (h->getProf() == warrior) {
		type += static_cast<int>(round(makeRand(0, 1)));
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


Chest::Chest(shared_ptr<Hero>&h) {
	ItemType itemType = getRandomItemType(h);
	item = ItemFactory::createItem(h->getlevel(), itemType, h->getProf());
}

void Chest::openBox(shared_ptr<Hero>&h) {
	int coins = static_cast<int>(round(makeRand(0, h->getlevel() * 100)));
	cout << "You found " << coins << " gold in the chest" << endl;
	h->setMoney(h->getMoney() + coins);

	cout << "There is also an item in chest" << endl << endl;
	cout << "Your current item: " << endl;
	h->showOneItem(item->getType(), h->getProf());
	cout << endl;
	cout << "The item in the chest: " << endl;
	showItemDetails(item,h->getProf());
    cout << endl;
	
	cout << "Do you want to replace your item with a new found one? (Y/N)" << endl;

	char decision;
    while (true) {
        cin >> decision;
		decision = makeBig(decision);
        if (decision == 'Y')
            h->ChangeEQ(item);

        if (decision == 'Y' || decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}


Chamber::Chamber(shared_ptr<Hero>&h)
{
	chamber_ID = static_cast<int>(makeRand(1,1000));
	hero = h->getInstance();
}

unique_ptr<Chamber> Chamber::takeAction(shared_ptr<Hero>&h) { return nullptr; }

int Chamber::getChamberID() {
	return chamber_ID;
}

string Chamber::getName() {
	return name;
}


BossChamber::BossChamber(shared_ptr<Hero>&h) : Chamber(h) {
	int lvl = h->getlevel() * 3 / 2;
	boss_monster = make_shared<monster>(lvl, "Great BOSS");
}

unique_ptr<Chamber> BossChamber::takeAction(shared_ptr<Hero>&h) {
	cout << "You have entered the boss's chamber" << endl;
	cout << "The last and hardest fight is ahead of you" << endl;
	finalFight(h);

	if (h->getcurrentHealth() > 0)
		cout << "Congratulations! You finished the game" << endl;
	else
		cout << "It was very close..." << endl;

	return nullptr;
}

void BossChamber::finalFight(shared_ptr<Hero>&h) {
	shared_ptr <Character>ch = boss_monster;
	h->fight(ch,1);
}


PassageChamber::PassageChamber(shared_ptr<Hero>&h) : Chamber(h) {}

unique_ptr<Chamber> PassageChamber::takeAction(shared_ptr<Hero>&h) { return nullptr; }

unique_ptr<Chamber> PassageChamber::goNext(shared_ptr<Hero>&h) {
	unique_ptr<Chamber> next_chamber;

	if (h->getcurrentHealth() == 0) {
		cout << "YOU DEAD" << endl;
		cout << "THE GAME IS OVER" << endl;
		return nullptr;
	}

	if (numOfChamber < 19)
	{
        cout << endl;
		cout << "Currently You are in Chamber number: " << numOfChamber << endl;
		numOfChamber++;

		char showSth;
        while (true) {
            cout << "Do you want to see your EQ or statistics? (equipment - E, statistics - S, nothing - N)" << endl;
            cin >> showSth;
			showSth = makeBig(showSth);
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

		int left = static_cast<int>(round(makeRand(0,6)));
		int right = static_cast<int>(round(makeRand(0, 6)));
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
			next_chamber = make_unique<MonsterRoom>(h);
		else if (next == 1 || chambersWithoutTrader == 9)
			next_chamber = make_unique<TraderRoom>(h);
		else if (next == 2)
			next_chamber = make_unique<TreasureRoom>(h);
		else if (next == 3)
			next_chamber = make_unique<HealthRoom>(h);
		else if (next == 4)
			next_chamber = make_unique<PotionRoom>(h);
		else if (next == 5)
			next_chamber = make_unique<TrapRoom>(h);
		else
			next_chamber = make_unique<EmptyRoom>(h);
	}
	else if (numOfChamber == 19) {
        numOfChamber++;

        cout << endl;
        cout << "Your health points: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
        cout << "After this room, the next one will be with a boss" << endl;
        cout << "The chambers have open doors, so you can see what is inside" << endl;
        cout << "Where do you want to go? (HealthRoom - L, TraderRoom - R)" << endl;

        char direction;
        while (true) {
            cin >> direction;
			direction = makeBig(direction);
            if (direction == 'L') {
                next_chamber = make_unique<HealthRoom>(h);
				break;
            }
            else if (direction == 'R') {
                next_chamber = make_unique<TraderRoom>(h);
				break;
            }
            else
                cout << "Character not recognized, please retype" << endl;
        }
    }
    else {
        cout << endl;
        cout << "The last chamber is ahead of you - BossChamber" << endl;

        char decision;
        while (true) {
            cout << "Do you want to face the boss? (Y/N)" << endl;
            cin >> decision;
			decision = makeBig(decision);
            if (decision == 'Y')
                break;
            else if (decision == 'N')
                cout << "You can't give up now, you are so close to your desired goal" << endl;
            else
                cout << "Character not recognized, please retype" << endl;
        }

        next_chamber = make_unique<BossChamber>(h);;
    }


	return next_chamber;
}


NormalChamber::NormalChamber(shared_ptr<Hero>&h) : PassageChamber(h) {}
unique_ptr<Chamber> NormalChamber::takeAction(shared_ptr<Hero>&h) { return nullptr; }

SafeChamber::SafeChamber(shared_ptr<Hero>&h) : PassageChamber(h) {}
unique_ptr<Chamber> SafeChamber::takeAction(shared_ptr<Hero>&h) { return nullptr; }


MonsterRoom::MonsterRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters = 0;
    chambersWithoutTrader++;
	chest = make_unique<Chest>(h);
	normal_monster = make_shared<monster>(h->getlevel(), 0);
}

unique_ptr<Chamber> MonsterRoom::takeAction(shared_ptr<Hero>&h) {
	cout << "You have entered the room with the monster" << endl;
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	cout << "Are you fighting or running? (F/R)" << endl;
	char action;

    while (true) {
        cin >> action;
		action = makeBig(action);
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

void MonsterRoom::fight(shared_ptr<Hero>&h)
{
	shared_ptr<Character> ch = normal_monster;
	h->fight(ch, 0);
	if (h->getcurrentHealth() > 0)
	{
        cout << "You have defeated a monster" << endl;
        cout << "Remaining health points: " << h->getcurrentHealth() << endl << endl;
		h->levelup();
		cout << "You have leveled up. Your current level is: " << hero->getlevel() << endl;
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl << endl;
		cout << "After defeating the monster you saw the box in the corner of the room" << endl;
		cout << "Do you want to open it? (Y/N)" << endl;
		char player_decision;

        while (true) {
            cin >> player_decision;
			player_decision = makeBig(player_decision);
            if (player_decision == 'Y')
                chest->openBox(h);

            if (player_decision == 'Y' || player_decision == 'N')
                break;
            else
                cout << "Character not recognized, please retype" << endl;
        }
	}
}

void MonsterRoom::runAway(shared_ptr<Hero>&h) {
	const int chance = static_cast<int>(makeRand(0, 10));

	if (chance < 3) {
		cout << "While escaping you got hit by a monster" << endl;
		h->getDamage(h->getcurrentHealth() * 0.2);
		cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
	}
	else
		cout << "You escaped the monster" << endl;
}


TrapRoom::TrapRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

unique_ptr<Chamber> TrapRoom::takeAction(shared_ptr<Hero>&h) {
	getDamage(h);
	return goNext(h);
}

void TrapRoom::getDamage(shared_ptr<Hero>&h) {
	cout << "There was a trap in the room that has hurted you" << endl;
	h->getDamage(h->getmaxHealth() * 0.2);
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


PotionRoom::PotionRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

unique_ptr<Chamber> PotionRoom::takeAction(shared_ptr<Hero>&h) {
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

void PotionRoom::drinkPotion(shared_ptr<Hero>&h) {
	int drawn_num = static_cast<int>(round(makeRand(0, 1)));

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


TreasureRoom::TreasureRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
	chest = make_unique<Chest>(h);
}

unique_ptr<Chamber> TreasureRoom::takeAction(shared_ptr<Hero>&h) {
	openBox(h);
	return goNext(h);
}

void TreasureRoom::openBox(shared_ptr<Hero>&h) {
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


HealthRoom::HealthRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

unique_ptr<Chamber> HealthRoom::takeAction(shared_ptr<Hero>&h) {
	healthYourself(h);
	return goNext(h);
}

void HealthRoom::healthYourself(shared_ptr<Hero>&h) {
	cout << "You came to the room with the fountain of life, after drinking the magic water you regain all health points" << endl;
	h->setcurrentHealth(h->getmaxHealth());
	cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


TraderRoom::TraderRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader = 0;
	item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
};

unique_ptr<Chamber> TraderRoom::takeAction(shared_ptr<Hero>&h) {
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

void TraderRoom::seeItems(shared_ptr<Hero>&h) {
	h->showEQ();
    cout << endl;
    cout << "Merchant items:" << endl;
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

void TraderRoom::buyItem(shared_ptr<Hero>&h) {
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


EmptyRoom::EmptyRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

unique_ptr<Chamber> EmptyRoom::takeAction(shared_ptr<Hero>&h) {
	cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
	return goNext(h);
}


StartingRoom::StartingRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
	numOfChamber = 0;
    chambersWithoutMonsters = 0;
    chambersWithoutTrader = 0;
}

unique_ptr<Chamber> StartingRoom::takeAction(shared_ptr<Hero>&h) {
	cout << "Your adventure begins here" << endl;
	return goNext(h);
}