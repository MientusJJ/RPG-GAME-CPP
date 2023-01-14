#pragma once
#ifndef EVENTS_H
#define EVENTS_H
#include "Character.h"
#include <vector>
#include "Strategy.h"

ItemType getRandomItemType( shared_ptr<Hero>&h);

// Part of Controller
class Chest {
public:
    void openBox(shared_ptr<Hero>& hero);
};

class DescriptionVisitor;

// Part of Controller
class Event {
public:
    Event();
    virtual void DisplayDescription(DescriptionVisitor visitor) = 0;
    virtual void Action(shared_ptr<Hero> &h);
};

class EndPoint : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToMonsterRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class Fight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class RunAway : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class CheckChest : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToTrapRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class ActiveTheTrap : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToPotionRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class DrinkPotion : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToTreasureRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToHealthRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class HealthYourself : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToTraderRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class SeeItems : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);

protected:
    void BuyItems(shared_ptr<Hero> &h, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3);
    bool buyOneItem(shared_ptr<Hero> &h, shared_ptr<Item>& item);
};


class EnterToEmptyRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToStartingRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class EnterToBossRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};

class BossFight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor);
    void Action(shared_ptr<Hero> &h);
};


class EventNode {
public:
    EventNode(shared_ptr<Event>&& curr);
    shared_ptr<Event> current;
    vector <shared_ptr<EventNode>> AllNexts;
};

// Part of Controller
class DescriptionVisitor {
public:
    void visitEndPoint(EndPoint event);
    void visitEnterToMonsterRoom(EnterToMonsterRoom event);
    void visitFight(Fight event);
    void visitRunAway(RunAway event);
    void visitCheckChest(CheckChest event);
    void visitEnterToTrapRoom(EnterToTrapRoom event);
    void visitActiveTheTrap(ActiveTheTrap event);
    void visitEnterToPotionRoom(EnterToPotionRoom event);
    void visitDrinkPotion(DrinkPotion event);
    void visitEnterToTreasureRoom(EnterToTreasureRoom event);
    void visitEnterToHealthRoom(EnterToHealthRoom event);
    void visitHealthYourself(HealthYourself event);
    void visitEnterToTraderRoom(EnterToTraderRoom event);
    void visitSeeItems(SeeItems event);
    void visitEnterToEmptyRoom(EnterToEmptyRoom event);
    void visitEnterToStartingRoom(EnterToStartingRoom event);
    void visitEnterToBossRoom(EnterToBossRoom event);
    void visitBossFight(BossFight event);

private:
    void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

#endif
