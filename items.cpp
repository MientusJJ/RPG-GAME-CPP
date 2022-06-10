#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
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


static double dRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

class Item {
protected:
	int item_ID;
	int value;
	string name;
	ItemType type;

public:
	Item(int level) {
		item_ID = rand() % 1000;
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
	Weapon(int level) : Item(level) {
		type = weapon;

		int min = 1 + (level - 1) * 2;
		int max = min + 9;

		min_damage = min + rand() % 9;
		max_damage = min_damage + rand() % (1 + max - min);
		critical_chance = dRand(1, 15);

		value = level * 100;
	}
	int getMinDamage() const { return min_damage; }
	int getMaxDamage() const { return max_damage; }
	double getCriticalChance() const { return critical_chance; }
};

class Sword : public Weapon {
protected:
	int main_stat;

public:
	Sword(int level) : Weapon(level) {
		int x = 1 + rand() % 10;

		// 30% chance for bonus
		if (x > 3)
			main_stat = 0;
		else
			main_stat = level + rand() % (level + 1);

		name = "Sword";
	}
	int getMainStat() const { return main_stat; }
	string getMainStatName() const { return "strength"; }
};

class MagicStick : public Weapon {
protected:
	int main_stat;

public:
	MagicStick(int level) : Weapon(level) {
		int x = 1 + rand() % 10;

		// 30% chance for bonus
		if (x > 3)
			main_stat = 0;
		else
			main_stat = level + rand() % (level + 1);

		name = "MagicStick";
	}
	int getMainStat() const { return main_stat; }
	string getMainStatName() const { return "intelligence"; }
};

class Bow : public Weapon {
protected:
	int main_stat;

public:
	Bow(int level) : Weapon(level) {
		int x = 1 + rand() % 10;

		// 30% chance for bonus
		if (x > 3)
			main_stat = 0;
		else
			main_stat = level + rand() % (level + 1);

		name = "Bow";
	}
	int getMainStat() const { return main_stat; }
	string getMainStatName() const { return "agility"; }
};

class Armor : public Item {
protected:
	int defense;
	int health;

public:
	Armor(int level) : Item(level) {
		type = armor;

		int min = 1 + (level - 1) * 2;
		int x = 1 + rand() % 10;

		defense = min + rand() % 5;
		// 40% chance for bonus
		if (x > 4)
			health = 0;
		else
			health = level * 50 + rand() % 501;

		value = level * 120;

		name = "Armor";
	}
	int getDefense() const { return defense; }
	int getHealth() const { return health; }
};

class Headgear : public Item {
protected:
	int defense;

public:
	Headgear(int level) : Item(level) {
		type = headgear;

		int min = level;
		defense = min + rand() % 3;

		value = level * 70;
	}
	int getDefense() const { return defense; }
};

class Helmet : public Headgear {
protected:
	int health;

public:
	Helmet(int level) : Headgear(level) {
		health = level * 10 + rand() % 201;
		name = "Helmet";
	}
	int getHealth() const { return health; }
	string getMainStatName() const { return "strength"; }
};

class MagicHat : public Headgear {
protected:
	int intelligence;

public:
	MagicHat(int level) : Headgear(level) {
		intelligence = level + rand() % 2;
		name = "MagicHat";
	}
	int getMainStat() const { return intelligence; }
	string getMainStatName() const { return "intelligence"; }
};

class Talisman : public Item {
protected:
	double critical_chance;

public:
	Talisman(int level) : Item(level) {
		type = talisman;

		critical_chance = dRand(1.0, 10.0);

		value = level * 60;
	}
	double getCriticalChance() const { return critical_chance; }
};

class ScoutTalisman : public Talisman {
protected:
	int agility;

public:
	ScoutTalisman(int level) : Talisman(level) {
		agility = level + rand() % 2;
		name = "ScoutTalisman";
	}
	int getMainStat() const { return agility; }
	string getMainStatName() const { return "agility"; }
};

class WarriorTalisman : public Talisman {
protected:
	int strength;

public:
	WarriorTalisman(int level) : Talisman(level) {
		strength = level + rand() % 2;
		name = "WarriorTalisman";
	}
	int getMainStat() const { return strength; }
	string getMainStatName() const { return "strength"; }
};

class MageTalisman : public Talisman {
protected:
	int intelligence;

public:
	MageTalisman(int level) : Talisman(level) {
		intelligence = level + rand() % 2;
		name = "MageTalisman";
	}
	int getMainStat() const { return intelligence; }
	string getMainStatName() const { return "intelligence"; }
};

class Shield : public Item {
protected:
	int defense;
	double block_chance;

public:
	Shield(int level) : Item(level) {
		type = shield;

		defense = level + rand() % 5;
		block_chance = dRand(1.0, 20.0);
		value = level * 90;
		name = "Shield";
	}

	int getDefense() const override { return defense; }
	double getBlockChance() const { return block_chance; }
};

class ItemFactory {
public:
	static Item * createItem(int level, ItemType type, Profession profession) {
		Item *item = nullptr;

		if (type == weapon)
		{
			if (profession == warrior) {
				item = new Sword(level);
			}
			else if (profession == scout) {
				item = new Bow(level);
			}
			else if (profession == mage) {
				item = new MagicStick(level);
			}
			else {
				cout << "wrong class value" << endl;
			}
		}
		else if (type == armor)
		{
			item = new Armor(level);
		}
		else if (type == headgear)
		{
			if (profession == warrior) {
				item = new Helmet(level);
			}
			else if (profession == scout) {
				item = new Helmet(level);
			}
			else if (profession == mage) {
				item = new MagicHat(level);
			}
			else {
				cout << "wrong class value" << endl;
			}
		}
		else if (type == talisman)
		{
			if (profession == warrior) {
				item = new WarriorTalisman(level);
			}
			else if (profession == scout) {
				item = new ScoutTalisman(level);
			}
			else if (profession == mage) {
				item = new MageTalisman(level);
			}
			else {
				cout << "wrong class value" << endl;
			}
		}
		else if (type == shield)
		{
			if (profession == warrior)
				item = new Shield(level);
			else {
				cout << "wrong class value" << endl;
			}
		}
		else
		{
			cout << "wrong item type value" << endl;
		}


		return item;
	};
};

static void showItemDetails(Item * item, Profession prof) {
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
			cout << ":\n\t Health: " << item->getHealth();
		}
		cout << "\n\t value: " << item->getValue() << endl;
	}
	return;
}

#endif