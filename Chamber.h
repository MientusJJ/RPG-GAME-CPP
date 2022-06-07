#ifndef CHAMBER_H
#define CHAMBER_H
//#include "monster.cpp"
#include "items.cpp"

class Chest {
protected:
    Item* item;

public:
    Chest();
    void openBox();
};

class Chamber {
protected:
    int chamber_ID;
    string name;

public:
    Chamber();
    int getChamberID();
    string getName();
};

class BossChamber : public Chamber {

};

class PassageChamber : public Chamber {
public:
    virtual void takeAction();
    void goNext();
};

class NormalChamber : public PassageChamber {};
class SafeChamber : public PassageChamber {};

class MonsterRoom : public NormalChamber {
protected:
    //monster* monster;
    Chest* chest;

public:
    MonsterRoom();
    void takeAction();
    void fight();
    void runAway();
};

class TrapRoom : public NormalChamber {
public:
    void takeAction();
    void getDamage();
};

class TreasureRoom : public NormalChamber {
protected:
    Chest* chest;

public:
    TreasureRoom();
    void takeAction();
    void openBox();
};

class HealthRoom : public SafeChamber {
public:
    void takeAction();
    void healthYourself();
};

class PotionRoom : public SafeChamber {
public:
    void takeAction();
    void drinkPotion();
};

class TraderRoom : public SafeChamber {
protected:
    Item* item1;
    Item* item2;
    Item* item3;

public:
    TraderRoom();
    void takeAction();
    void seeItems();
    void buyItem();
};

class EmptyRoom : public SafeChamber {
public:
    void takeAction();
};
#endif