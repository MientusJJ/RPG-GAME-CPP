#ifndef CHAMBER_H
#define CHAMBER_H
#include "items.cpp"
#include "Character.h"


class Chest {
protected:
    Item* item;

public:
    Chest(Hero* hero);
    void openBox(Hero* hero);
};

class Chamber {
protected:
    int chamber_ID;
    string name;
    Hero* hero;

public:
    Chamber(Hero* h);
    virtual void takeAction(Hero *h);
    int getChamberID();
    string getName();
};

class BossChamber : public Chamber {
protected:
    monster* boss_monster;

public:
    BossChamber(Hero *h);
    void takeAction(Hero *h);

private:
    void finalFight(Hero *h);
};

class PassageChamber : public Chamber {
public:
    PassageChamber(Hero* h);
    virtual void takeAction(Hero* h);
    static Chamber* goNext(Hero* h);
};

class NormalChamber : public PassageChamber {
public:
    NormalChamber(Hero* h);
    void takeAction(Hero* h);
};
class SafeChamber : public PassageChamber {
public:
    SafeChamber(Hero* h);
    void takeAction(Hero* h);
};

class MonsterRoom : public NormalChamber {
protected:
    monster* normal_monster;
    Chest* chest;

public:
    MonsterRoom(Hero* h);
    void takeAction(Hero *h);

private:
    void fight(Hero *h);
    void runAway(Hero *h);
};

class TrapRoom : public NormalChamber {
public:
    TrapRoom(Hero* h);
    void takeAction(Hero *h);

private:
    void getDamage(Hero *h);
};

class PotionRoom : public NormalChamber {
public:
    PotionRoom(Hero* h);
    void takeAction(Hero *h);

private:
    void drinkPotion(Hero *h);
};

class TreasureRoom : public SafeChamber {
protected:
    Chest* chest;

public:
    TreasureRoom(Hero* h);
    void takeAction(Hero *h);

private:
    void openBox(Hero *h);
};

class HealthRoom : public SafeChamber {
public:
    HealthRoom(Hero* h);
    void takeAction(Hero *h);

private:
    void healthYourself(Hero *h);
};

class TraderRoom : public SafeChamber {
protected:
    Item* item1;
    Item* item2;
    Item* item3;

public:
    TraderRoom(Hero* h);
    void takeAction(Hero* h);

private:
    void seeItems(Hero* h);
    void buyItem(Hero* h);
};

class EmptyRoom : public SafeChamber {
public:
    EmptyRoom(Hero* h);
    void takeAction(Hero* h);
};

class StartingRoom : public SafeChamber {
public:
    StartingRoom(Hero* h);
    void takeAction(Hero* h);
};
#endif