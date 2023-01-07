#pragma once
#ifndef EVENTS_H
#define EVENTS_H
#include "Character.h"
#include <vector>

#include "Strategy.h"

class Chest {
protected:
    shared_ptr<Item> item;

public:
    Chest(shared_ptr<Hero>& hero);
    void openBox(shared_ptr<Hero>& hero);
};


class Event {
protected:
    shared_ptr<Hero> h;
    string description;
public:
    void DisplayDescription();
    virtual void Action();
};

class EndPoint : public Event {
public:
    EndPoint(shared_ptr<Hero>& h);
    void Action();
};

class EnterToMonsterRoom : public Event {
public:
    EnterToMonsterRoom(shared_ptr<Hero>& h);
    void Action();
};

class Fight : public Event {
protected:
    shared_ptr<monster> _monster;
public:
    Fight(shared_ptr<Hero>& hero, shared_ptr<monster> m);
    void Action();
};

class RunAway : public Event {
public:
    RunAway(shared_ptr<Hero>& h);
    void Action();
};

class CheckChest : public Event {
protected:
    unique_ptr<Chest> _chest;
public:
    CheckChest(shared_ptr<Hero>& hero, unique_ptr<Chest>& chest);
    void Action();
};

class EnterToTrapRoom : public Event {
public:
    EnterToTrapRoom(shared_ptr<Hero>& h);
    void Action();
};

class ActiveTheTrap : public Event {
public:
    ActiveTheTrap(shared_ptr<Hero>& h);
    void Action();
};

class EnterToPotionRoom : public Event {
public:
    EnterToPotionRoom(shared_ptr<Hero>& h);
    void Action();
};

class DrinkPotion : public Event {
public:
    DrinkPotion(shared_ptr<Hero>& h);
    void Action();
};

class EnterToTreasureRoom : public Event {
public:
    EnterToTreasureRoom(shared_ptr<Hero>& h);
    void Action();
};

class EnterToHealthRoom : public Event {
public:
    EnterToHealthRoom(shared_ptr<Hero>& h);
    void Action();
};

class HealthYourself : public Event {
public:
    HealthYourself(shared_ptr<Hero>& h);
    void Action();
};

class EnterToTraderRoom : public Event {
public:
    EnterToTraderRoom(shared_ptr<Hero>& h);
    void Action();
};

class SeeItems : public Event {
public:
    SeeItems(shared_ptr<Hero>& h, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3);
    void Action();
private:
    shared_ptr<Item> _item1;
    shared_ptr<Item> _item2;
    shared_ptr<Item> _item3;
};

class BuyItems : public Event {
public:
    BuyItems(shared_ptr<Hero>& h, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3,unique_ptr<Strategy>& p_strategy);
    void Action();
private:
    bool buyOneItem(int num);
    unique_ptr<Strategy> _buyingStrategy;
    shared_ptr<Item> _item1;
    shared_ptr<Item> _item2;
    shared_ptr<Item> _item3;
};

class EnterToEmptyRoom : public Event {
public:
    EnterToEmptyRoom(shared_ptr<Hero>& h);
    void Action();
};

class EnterToStartingRoom : public Event {
public:
    EnterToStartingRoom(shared_ptr<Hero>& h);
    void Action();
};

class EnterToBossRoom : public Event {
public:
    EnterToBossRoom(shared_ptr<Hero>& h);
    void Action();
};


class EventNode {
public:
    EventNode(shared_ptr<Event>&& curr);
    shared_ptr<Event> current;
    void Description();
    vector <shared_ptr<EventNode>> AllNexts;
};
#endif
