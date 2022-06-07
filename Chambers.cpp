#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Chamber.h"
using namespace std;

// hero stats
const int level = 1;
Profession profession = warrior;


ItemType getRandomItemType() {
    int type = rand() % 5;
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

void assignItemToHero(Item* item) {
/*
    if (hero.coinAmount >= item->getValue()) {
        if (item->getType() == weapon) {
            delete hero.weapon;
            hero.weapon = item;
        }
        else if (item->getType() == armor) {
            delete hero.armor;
            hero.armor = item;
        }
        else if (item->getType() == headgear) {
            delete hero.headgear;
            hero.headgear = item;
        }
        else if (item->getType() == talisman) {
            delete hero.talisman;
            hero.talisman = item;
        }
        else if (item->getType() == shield) {
            delete hero.shield;
            hero.shield = item;
        }

        // ???
        item = nullptr;
    }
    else {
        cout << "You do not have enough coins" << endl;
    }
    */
}


Chest::Chest() {
    ItemType itemType = getRandomItemType();

    item = ItemFactory::createItem(level, itemType, profession);
}

void Chest::openBox() {
    int coins = rand() % (level * 100);
    cout << "You found " << coins << " gold in the chest";
    // hero.amountOfCoins += coins;

    cout << "There is also an item in chest" << endl;
    showItemDetails(*item);
    cout << "Do you want to take this item? (Y/N)" << endl;

    char decision;
    cin >> decision;

    if (decision == 'Y') {
        string name = item->getName();

        if (name == "Sword" || name == "MagicStick" || name == "Bow") {

        }
        else if (name == "Armor") {

        }
        else if (name == "Helmet" || name == "MagicHat") {

        }
        else if (name == "WarriorTalisman" || name == "ScoutTalisman" || name == "MageTalisman") {

        }
        else if (name == "Shield") {

        }
    }
}

Chamber::Chamber() {
    srand (time(NULL));
    chamber_ID = rand() % 1000;
}

int Chamber::getChamberID() {
    return chamber_ID;
}

string Chamber::getName() {
    return name;
}

void PassageChamber::takeAction() {}

void PassageChamber::goNext() {
    cout << "Where do you want to go? (left - L, right - R)";
    char direction;
    cin >> direction;

    int left = rand() % 7;
    int right = rand() % 7;
    int next;

    if (direction == 'L')
        next = left;
    else if (direction == 'R')
        next = right;

    Chamber* current_chamber;
    if (next == 0)
        current_chamber = new MonsterRoom();
    else if (next == 1)
        current_chamber = new TrapRoom();
    else if (next == 2)
        current_chamber = new TreasureRoom();
    else if (next == 3)
        current_chamber = new HealthRoom();
    else if (next == 4)
        current_chamber = new PotionRoom();
    else if (next == 5)
        current_chamber = new TraderRoom();
    else
        current_chamber = new EmptyRoom();
}

MonsterRoom::MonsterRoom() {
    chest = new Chest();
    //monster = new monster();
}

void MonsterRoom::takeAction() {
    cout << "You have entered the room with the monster" << endl;
    cout << "Are you fighting or running? (F/R)" << endl;
    char action;
    cin >> action;

    if (action == 'F')
        fight();
    else if (action == 'R')
        runAway();
}

void MonsterRoom::fight() {
    // walka

    cout << "After defeating the monster you saw the box in the corner of the room" << endl;
    cout << "Do you want to open it? (Y/N)" << endl;
    char player_decision;
    cin >> player_decision;
    if (player_decision == 'Y')
        chest->openBox();

    goNext();
}

void MonsterRoom::runAway() {
    int chance = rand() % 10;

    if (chance < 3) {
        cout << "While escaping you got hit by a monster" << endl;
        // hero.current_health *= 0.8;
    }
    else
        cout << "You escaped the monster" << endl;

    goNext();
}

void TrapRoom::takeAction() {
    getDamage();
}

void TrapRoom::getDamage() {
    cout << "There was a trap in the room that hurt you" << endl;
    // hero.current_health -= hero.max_health * 0.8;

    goNext();
}

TreasureRoom::TreasureRoom() {
    chest = new Chest();
}

void TreasureRoom::takeAction() {
    openBox();
}

void TreasureRoom::openBox() {
    cout << "There is a box in the room, do you want to open it? (Y/N)";
    char player_decision;
    cin >> player_decision;
    if (player_decision == 'Y')
        chest->openBox();

    goNext();
}

void HealthRoom::takeAction() {
    healthYourself();
}

void HealthRoom::healthYourself() {
    cout << "You came to the room with the fountain of life, after drinking the magic water you regain all health points" << endl;
    // hero.current_health = hero.max_health;

    goNext();
}

void PotionRoom::takeAction() {
    cout << "In the room you came to there is a mysterious potion with unknown properties" << endl;
    cout << "Do you want to drink it? (Y/N)" << endl;
    char player_decision;
    cin >> player_decision;
    if (player_decision == 'Y')
        drinkPotion();

    goNext();
}

void PotionRoom::drinkPotion() {
    int drawn_num = rand() % 2;

    if (drawn_num == 0) {
        //hero.current_health = hero.max_health;
    }
    else {
        //hero.current_health -= hero.max_health * 0.3;
    }
}

TraderRoom::TraderRoom() {
    item1 = ItemFactory::createItem(level, getRandomItemType(), profession);
    item2 = ItemFactory::createItem(level, getRandomItemType(), profession);
    item3 = ItemFactory::createItem(level, getRandomItemType(), profession);
};

void TraderRoom::takeAction() {
    cout << "You came to a room with a merchant who offers you to see his items" << endl;
    cout << "Do you want to watch them? (Y/N)" << endl;
    char player_decision;
    cin >> player_decision;
    if (player_decision == 'Y')
        seeItems();

    goNext();
}

void TraderRoom::seeItems() {
    cout << "item 1:" << endl;
    showItemDetails(*item1);
    cout << "price: " << item1->getValue() << endl << endl;

    cout << "item 2:" << endl;
    showItemDetails(*item2);
    cout << "price: " << item2->getValue() << endl << endl;

    cout << "item 3:" << endl;
    showItemDetails(*item3);
    cout << "price: " << item3->getValue() << endl << endl;

    cout << "Your balance: hero.balance" << endl;
    cout << "Do you want to buy something? (Y/N)" << endl;
    char player_decision;
    cin >> player_decision;
    if (player_decision == 'Y')
        buyItem();

    goNext();
}

void TraderRoom::buyItem() {
    bool wantToBuy = true;
    int num;
    char player_decision;

    while (wantToBuy)
    {
        cout << "Enter the number of the item you want to buy: ";
        cin >> num;

        if (num == 1) {
            if (item1 != nullptr) {
                assignItemToHero(item1);
            }
            else {
                cout << "You have already purchased this item" << endl;
            }
        }
        else if (num == 2) {
            if (item2 != nullptr) {
                assignItemToHero(item2);
            }
            else {
                cout << "You have already purchased this item" << endl;
            }
        }
        else if (num == 3) {
            if (item3 != nullptr) {
                assignItemToHero(item3);
            }
            else {
                cout << "You have already purchased this item" << endl;
            }
        }
        else {
            cout << "Invalid item number" << endl;
        }

        if (item1 != nullptr || item2 != nullptr || item3 != nullptr) {
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

void EmptyRoom::takeAction() {
    cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
    goNext();
}