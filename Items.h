#pragma once
#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Names.h"
using namespace std;

enum Profession
{
    warrior = 1,
    scout = 2,
    mage = 3
};

enum ItemType
{
    weapon = 0,
    armor = 1,
    headgear = 2,
    talisman = 3,
    shield = 4
};

class Item {
protected:
    int item_ID;
    int value;
    string name;
    ItemType type;

public:
    Item(int level) {
        item_ID = static_cast<int>(round(makeRand(0, 999)));
    }
    int getValue() const { return value; }
    int getItemID() const { return item_ID; }
    string getName() const { return name; }
    ItemType getType() const { return type; }
    virtual int getMainStat() const { return 0; }
    virtual string getMainStatName() const { return ""; }
    virtual int getDefense() const { return 0; }
    virtual int getHealth() const { return 0; }
    virtual double getCriticalChance() const { return 0; }
    virtual double getBlockChance() const { return 0; }
    virtual int getMinDamage() const { return 0; }
    virtual int getMaxDamage() const { return 0; }
};
class Weapon : public Item {
protected:
    int min_damage;
    int max_damage;
    double critical_chance;

public:
    Weapon(int level);
    int getMinDamage() const { return min_damage; }
    int getMaxDamage() const { return max_damage; }
    double getCriticalChance() const { return critical_chance; }
};
class Sword : public Weapon {
protected:
    int main_stat;

public:
    Sword(int level);
    int getMainStat() const { return main_stat; }
    string getMainStatName() const { return "strength"; }
};
class MagicStick : public Weapon {
protected:
    int main_stat;

public:
    MagicStick(int level);
    int getMainStat() const { return main_stat; }
    string getMainStatName() const { return "intelligence"; }
};

class Bow : public Weapon {
protected:
    int main_stat;

public:
    Bow(int level);
    int getMainStat() const { return main_stat; }
    string getMainStatName() const { return "agility"; }
};

class Armor : public Item {
protected:
    int defense;
    int health;

public:
    Armor(int level);
    int getDefense() const { return defense; }
    int getHealth() const { return health; }
};

class Headgear : public Item {
protected:
    int defense;

public:
    Headgear(int level);
    int getDefense() const { return defense; }
};

class Helmet : public Headgear {
protected:
    int health;

public:
    Helmet(int level);
    int getHealth() const { return health; }
    string getMainStatName() const { return "strength"; }
};

class MagicHat : public Headgear {
protected:
    int intelligence;

public:
    MagicHat(int level);
    int getMainStat() const { return intelligence; }
    string getMainStatName() const { return "intelligence"; }
};

class Talisman : public Item {
protected:
    double critical_chance;

public:
    Talisman(int level);
    double getCriticalChance() const { return critical_chance; }
};

class ScoutTalisman : public Talisman {
protected:
    int agility;

public:
    ScoutTalisman(int level);
    int getMainStat() const { return agility; }
    string getMainStatName() const { return "agility"; }
};

class WarriorTalisman : public Talisman {
protected:
    int strength;

public:
    WarriorTalisman(int level);
    int getMainStat() const { return strength; }
    string getMainStatName() const { return "strength"; }
};

class MageTalisman : public Talisman {
protected:
    int intelligence;

public:
    MageTalisman(int level);
    int getMainStat() const { return intelligence; }
    string getMainStatName() const { return "intelligence"; }
};

class Shield : public Item {
protected:
    int defense;
    double block_chance;

public:
    Shield(int level);
    int getDefense() const override { return defense; }
    double getBlockChance() const { return block_chance; }
};

class ItemFactory {
public:
    static unique_ptr<Item> createItem(int level, ItemType type, Profession profession);
};

static void showItemDetails(shared_ptr<Item>& item, Profession prof)
{
    if (item->getType() == weapon)
    {
        cout << "Weapon:\n\t name: " << item->getName() << "\n\t minimal Damage: " << item->getMinDamage() << "\n\t maximal Damage: " << item->getMaxDamage() << "\n\t " << item->getMainStatName() << ": " << item->getMainStat() << "\n\t value: " << item->getValue() << endl;
    }
    else if (item->getType() == talisman)
    {
        cout << "Talisman:\n\t name: " << item->getName() << "\n\t " << item->getMainStatName() << ": " << item->getMainStat() << "\n\t Critical Chance: " << item->getCriticalChance() << "\n\t value: " << item->getValue() << endl;
    }
    else if (item->getType() == shield)
    {
        cout << "Shield:\n\t name: " << item->getName() << "\n\t Defense: " << item->getDefense() << "\n\t Block Chance: " << item->getBlockChance() << "\n\t value: " << item->getValue() << endl;
    }
    else if (item->getType() == armor)
    {
        cout << "Armor:\n\t name: " << item->getName() << "\n\t Defense: " << item->getDefense() << "\n\t Health: " << item->getHealth() << "\n\t value: " << item->getValue() << endl;
    }
    else if (item->getType() == headgear)
    {
        cout << "Headgear:\n\t name: " << item->getName() << "\n\t Defense: " << item->getDefense();
        if (prof == mage)
        {
            cout << "\n\t " << item->getMainStatName() << ": " << item->getMainStat();
        }
        else
        {
            cout << "\n\t Health: " << item->getHealth();
        }
        cout << "\n\t value: " << item->getValue() << endl;
    }
    return;
}

#endif

