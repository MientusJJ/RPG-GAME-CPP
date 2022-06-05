#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum Profession
{
    warrior = 1,
    scout = 2,
    mage = 3
};


double dRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

class Item {
protected:
    int item_ID;
    int value;
    string name;

public:
    Item(int level) {
        srand (time(NULL));
        item_ID = rand() % 1000;
    }
    int getValue() const { return value; }
    int getItemID() const { return item_ID; }
    string getName() const { return name; }
    virtual int getMainStat() const { return -1; }
    virtual int getDefense() const { return -1; }
    virtual int getHealth() const { return -1; }
    virtual double getCriticalChance() const { return -1; }
    virtual double getBlockChance() const { return -1; }
};

class Weapon : public Item {
protected:
    int min_damage;
    int max_damage;
    double critical_chance;

public:
    Weapon(int level) : Item(level) {
        int min = 1 + (level-1) * 2;
        int max = min + 9;

        min_damage = min + rand() % 9;
        max_damage = min_damage + rand() % (1+max-min);
        critical_chance = rand() % (15 + 1);

        value = level*100;
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
            main_stat = level + rand() % (level+1);

        name = "Sword";
    }
    int getMainStat() const { return main_stat; }
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
            main_stat = level + rand() % (level+1);

        name = "MagicStick";
    }
    int getMainStat() const { return main_stat; }
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
            main_stat = level + rand() % (level+1);

        name = "Bow";
    }
    int getMainStat() const { return main_stat; }
};

class Armor : public Item {
protected:
    int defense;
    int health;

public:
    Armor(int level) : Item(level) {
        int min = 1 + (level-1) * 2;
        int x = 1 + rand() % 10;

        defense = min + rand() % 5;
        // 40% chance for bonus
        if (x > 4)
            health = 0;
        else
            health = level*50 + rand() % 501;

        value = level*120;

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
        int min = level;
        defense = min + rand() % 3;

        value = level*70;
    }
    int getDefense() const { return defense; }
};

class Helmet : public Headgear {
protected:
    int health;

public:
    Helmet(int level) : Headgear(level) {
        health = level*10 + rand() % 201;
        name = "Helmet";
    }
    int getHealth() const { return health; }
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
};

class Talisman : public Item {
protected:
    double critical_chance;

public:
    Talisman(int level) : Item(level) {
        critical_chance = dRand(1.0, 10.0);

        value = level*60;
    }
    double getCriticalChance () const { return critical_chance; }
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
};

class Shield : public Item {
protected:
    int defense;
    double block_chance;

public:
    Shield(int level) : Item(level) {
        defense = level + rand() % 5;
        block_chance = dRand(1.0, 20.0);
        value = level*90;
        name = "Shield";
    }

    int getDefense() const { return defense; }
    double getBlockChance() const { return block_chance; }
};

class ItemFactory {
public:
    //types of item: 0 - weapon; 1 - armor; 2 - headgear; 3 - talisman; 4 - shield
    //professions: 1 - warrior; 2 - scout; 3 - mage

    static Item * createItem(int level, int type, Profession profession) {
        Item *item = nullptr;

        if (type == 0)          //weapon
        {
            if (profession == 1) {
                item = new Sword(level);
            }
            else if (profession == 2) {
                item = new Bow(level);
            }
            else if (profession == 3) {
                item = new MagicStick(level);
            }
            else {
                cout << "wrong class value" << endl;
            }
        }
        else if (type == 1)     //armor
        {
            item = new Armor(level);
        }
        else if (type == 2)     //headgear
        {
            if (profession == 1) {
                item = new Helmet(level);
            }
            else if (profession == 2) {
                item = new Helmet(level);
            }
            else if (profession == 3) {
                item = new MagicHat(level);
            }
            else {
                cout << "wrong class value" << endl;
            }
        }
        else if (type == 3)     //talisman
        {
            if (profession == 1) {
                item = new WarriorTalisman(level);
            }
            else if (profession == 2) {
                item = new ScoutTalisman(level);
            }
            else if (profession == 3) {
                item = new MageTalisman(level);
            }
            else {
                cout << "wrong class value" << endl;
            }
        }
        else if (type == 4)     //shield
        {
            if (profession == 1)
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


int main() {
    /*
    int level, type;
    auto* factory = new ItemFactory;
    Profession profession = warrior;

    cin >> level;
    while (level != -1) {
        cin >> type;

        Item* item = ItemFactory::createItem(level, type, profession);

        cout << item->getName() << endl << item->getItemID() << endl << item->getValue() << endl;


        cout << "main_stat: " << item->getMainStat() << endl;
        cout << "defense: " << item->getDefense() << endl;
        cout << "health: " << item->getHealth() << endl;
        cout << "critical_chance: " << item->getCriticalChance() << endl;
        cout << "block_chance " << item->getBlockChance() << endl;

        delete item;
        cin >> level;
    }

    delete factory;
    */
    return 0;
}
