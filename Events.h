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
    void openBox(shared_ptr<Hero>& hero, shared_ptr<View> view);
};

class DescriptionVisitor;

// Part of Controller
class Event {
public:
    Event();
    virtual void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) = 0;
    virtual void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EndPoint : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToMonsterRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class Fight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class RunAway : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class CheckChest : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToTrapRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class ActiveTheTrap : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToPotionRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class DrinkPotion : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToTreasureRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToHealthRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class HealthYourself : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToTraderRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class SeeItems : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);

protected:
    void BuyItems(shared_ptr<Hero> &h, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3, shared_ptr<View> view);
    bool buyOneItem(shared_ptr<Hero> &h, shared_ptr<Item>& item, shared_ptr<View> view);
};


class EnterToEmptyRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToStartingRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class EnterToBossRoom : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
};

class BossFight : public Event {
public:
    void DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view);
    void Action(shared_ptr<Hero> &h, shared_ptr<View> view);
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
    void visitEndPoint(EndPoint event, shared_ptr<View> view);
    void visitEnterToMonsterRoom(EnterToMonsterRoom event, shared_ptr<View> view);
    void visitFight(Fight event, shared_ptr<View> view);
    void visitRunAway(RunAway event, shared_ptr<View> view);
    void visitCheckChest(CheckChest event, shared_ptr<View> view);
    void visitEnterToTrapRoom(EnterToTrapRoom event, shared_ptr<View> view);
    void visitActiveTheTrap(ActiveTheTrap event, shared_ptr<View> view);
    void visitEnterToPotionRoom(EnterToPotionRoom event, shared_ptr<View> view);
    void visitDrinkPotion(DrinkPotion event, shared_ptr<View> view);
    void visitEnterToTreasureRoom(EnterToTreasureRoom event, shared_ptr<View> view);
    void visitEnterToHealthRoom(EnterToHealthRoom event, shared_ptr<View> view);
    void visitHealthYourself(HealthYourself event, shared_ptr<View> view);
    void visitEnterToTraderRoom(EnterToTraderRoom event, shared_ptr<View> view);
    void visitSeeItems(SeeItems event, shared_ptr<View> view);
    void visitEnterToEmptyRoom(EnterToEmptyRoom event, shared_ptr<View> view);
    void visitEnterToStartingRoom(EnterToStartingRoom event, shared_ptr<View> view);
    void visitEnterToBossRoom(EnterToBossRoom event, shared_ptr<View> view);
    void visitBossFight(BossFight event, shared_ptr<View> view);

private:
    void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

#endif
