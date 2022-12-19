#include "Character.h"
#include <cstdio>
#include <vector>

class Chest {
protected:
    Item* item;

public:
    Chest(Hero* hero);
    void openBox(Hero* hero);
};


class Event {
protected:
    Hero *h;
    string description;
public:
    void DisplayDescription();
    virtual void Action();
};

class EndPoint : public Event {
public:
    EndPoint(Hero *h);
    void Action();
};

class EnterToMonsterRoom : public Event {
public:
    EnterToMonsterRoom(Hero *h);
    void Action();
};

class Fight : public Event {
protected:
    monster* _monster;
public:
    Fight(Hero *hero, monster *m);
    void Action();
};

class RunAway : public Event {
public:
    RunAway(Hero *h);
    void Action();
};

class CheckChest : public Event {
protected:
    Chest* _chest;
public:
    CheckChest(Hero *hero, Chest *chest);
    void Action();
};

class EnterToTrapRoom : public Event {
public:
    EnterToTrapRoom(Hero *h);
    void Action();
};

class ActiveTheTrap : public Event {
public:
    ActiveTheTrap(Hero *h);
    void Action();
};

class EnterToPotionRoom : public Event {
public:
    EnterToPotionRoom(Hero *h);
    void Action();
};

class DrinkPotion : public Event {
public:
    DrinkPotion(Hero *h);
    void Action();
};

class EnterToTreasureRoom : public Event {
public:
    EnterToTreasureRoom(Hero *h);
    void Action();
};

class EnterToHealthRoom : public Event {
public:
    EnterToHealthRoom(Hero *h);
    void Action();
};

class HealthYourself : public Event {
public:
    HealthYourself(Hero *h);
    void Action();
};

class EnterToTraderRoom : public Event {
public:
    EnterToTraderRoom(Hero *h);
    void Action();
};

class SeeItems : public Event {
public:
    SeeItems(Hero *h, Item* i1, Item* i2, Item* i3);
    void Action();
private:
    Item* _item1;
    Item* _item2;
    Item* _item3;
};

class BuyItems : public Event {
public:
    BuyItems(Hero *h, Item* i1, Item* i2, Item* i3);
    void Action();
private:
    Item* _item1;
    Item* _item2;
    Item* _item3;
};

class EnterToEmptyRoom : public Event {
public:
    EnterToEmptyRoom(Hero *h);
    void Action();
};

class EnterToStartingRoom : public Event {
public:
    EnterToStartingRoom(Hero *h);
    void Action();
};

class EnterToBossRoom : public Event {
public:
    EnterToBossRoom(Hero *h);
    void Action();
};




class EventNode {
public:
    EventNode(Event* curr);
    Event* current;
    vector <EventNode*> AllNexts;
};