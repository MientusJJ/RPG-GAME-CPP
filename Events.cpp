#include "Events.h"
#include <chrono>
#include <thread>

void Chest::openBox(Hero *h) {
    int coins = rand() % (h->getlevel() * 100);
    cout << "You found " << coins << " gold in the chest" << endl;
    h->setMoney(h->getMoney() + coins);

    cout << "There is also an item in chest: " << endl;
    showItemDetails(item,h->getProf());
    cout << endl;
    cout << "Your current item: " << endl;
    h->showOneItem(item->getType(), h->getProf());
    cout << endl;

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


void Event::DisplayDescription() {
    cout << description;
}

void Event::Action() {}

EndPoint::EndPoint(Hero *hero) {
    h = hero;
    description = "Get out of the room";
}

void EndPoint::Action() {
    cout << "";
}

EnterToMonsterRoom::EnterToMonsterRoom(Hero *hero) {
    h = hero;
}
void EnterToMonsterRoom::Action() {
    cout << "You have entered the room with the monster" << endl;
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

Fight::Fight(Hero *hero, monster *monster) {
    h = hero;
    _monster = monster;
    description = "Fight with the monster";
}
void Fight::Action() {
    h->fight(_monster, 0);
    if (h->getcurrentHealth() > 0)
    {
        cout << "You have defeated a monster" << endl;
        cout << "Remaining health points: " << h->getcurrentHealth() << endl << endl;
        h->levelup();
        cout << "You have leveled up. Your current level is: " << h->getlevel() << endl;
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl << endl;
    }
}

RunAway::RunAway(Hero *hero) {
    h = hero;
    description = "Run away";
}
void RunAway::Action() {
    int chance = rand() % 10;

    if (chance < 3) {
        cout << "While escaping you got hit by a monster" << endl;
        h->getDamage(h->getcurrentHealth() * 0.2);
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
    }
    else
        cout << "You escaped the monster" << endl;
}

CheckChest::CheckChest(Hero *hero, Chest *chest) {
    h = hero;
    description = "Check the chest";
    _chest = chest;
}
void CheckChest::Action() {
    char decision;
    while (true) {
        cout << "You found mystery box. Do you want to open it? (Y/N)" << endl;
        cin >> decision;

        if (decision == 'Y') {
            _chest->openBox(h);
            break;
        }
        else if (decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}

EnterToTrapRoom::EnterToTrapRoom(Hero *hero) {
    h = hero;
}
void EnterToTrapRoom::Action() {
    cout << "You enter a chamber that appears to be empty..." << endl;
}

ActiveTheTrap::ActiveTheTrap(Hero *hero) {
    h = hero;
    description = "Active the trap";
}
void ActiveTheTrap::Action() {
    cout << "There was a trap in the room that has hurted you" << endl;
    h->getDamage(h->getmaxHealth() * 0.2);
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

EnterToPotionRoom::EnterToPotionRoom(Hero *hero) {
    h = hero;
}
void EnterToPotionRoom::Action() {
    cout << "You have entered to room and saw a mysterious potion on the table" << endl;
}

DrinkPotion::DrinkPotion(Hero *hero) {
    h = hero;
    description = "Drink the potion";
}
void DrinkPotion::Action() {
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

EnterToTreasureRoom::EnterToTreasureRoom(Hero *hero) {
    h = hero;
}
void EnterToTreasureRoom::Action() {
    cout << "You have entered to room and saw a chest by the wall" << endl;
}

EnterToHealthRoom::EnterToHealthRoom(Hero *hero) {
    h = hero;
}
void EnterToHealthRoom::Action() {
    cout << "Upon entering the room, the Ancient Fountain of Life appeared before your eyes" << endl;
}

HealthYourself::HealthYourself(Hero *hero) {
    h = hero;
    description = "Drink some water from the Fountain";
}
void HealthYourself::Action() {
    cout << "After drinking the magic water you regain all health points" << endl;
    h->setcurrentHealth(h->getmaxHealth());
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

EnterToTraderRoom::EnterToTraderRoom(Hero *hero) {
    h = hero;
}
void EnterToTraderRoom::Action() {
    cout << "You have enter the room and saw the stand of a traveling trader who wants to offer you his items" << endl;
}

SeeItems::SeeItems(Hero *hero, Item* i1, Item* i2, Item* i3) {
    h = hero;
    _item1 = i1;
    _item2 = i2;
    _item3 = i3;
    description = "See items";
}
void SeeItems::Action() {
    h->showEQ();
    cout << endl;
    cout << "Merchant items:" << endl;
    cout << "item 1:" << endl;
    showItemDetails(_item1,h->getProf());
    cout << "price: " << _item1->getValue() << endl << endl;

    cout << "item 2:" << endl;
    showItemDetails(_item2, h->getProf());
    cout << "price: " << _item2->getValue() << endl << endl;

    cout << "item 3:" << endl;
    showItemDetails(_item3, h->getProf());
    cout << "price: " << _item3->getValue() << endl << endl;
    cout << "Your balance: " << h->getMoney() << endl;
}

BuyItems::BuyItems(Hero *hero, Item* i1, Item* i2, Item* i3) {
    h = hero;
    _item1 = i1;
    _item2 = i2;
    _item3 = i3;
    description = "Buy some items";
}
void BuyItems::Action() {
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
                if (h->getMoney() >= _item1->getValue()) {
                    h->setMoney(h->getMoney() - _item1->getValue());
                    h->ChangeEQ(_item1);
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
                if (h->getMoney() >= _item2->getValue()) {
                    h->setMoney(h->getMoney() - _item2->getValue());
                    h->ChangeEQ(_item2);
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
                if (h->getMoney() >= _item3->getValue()) {
                    h->setMoney(h->getMoney() - _item3->getValue());
                    h->ChangeEQ(_item3);
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

EnterToEmptyRoom::EnterToEmptyRoom(Hero *hero) {
    h = hero;
}
void EnterToEmptyRoom::Action() {
    cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
}

EnterToStartingRoom::EnterToStartingRoom(Hero *hero) {
    h = hero;
}
void EnterToStartingRoom::Action() {
    cout << "Your adventure begins here" << endl;
}

EnterToBossRoom::EnterToBossRoom(Hero *hero) {
    h = hero;
}
void EnterToBossRoom::Action() {
    chrono::milliseconds timespan(1000);
    this_thread::sleep_for(timespan);
    cout << "You have entered the boss's chamber" << endl;
    this_thread::sleep_for(timespan);
    cout << "The last and hardest fight is ahead of you" << endl;
    this_thread::sleep_for(timespan);
}


EventNode::EventNode(Event* curr) {
    current = curr;
}