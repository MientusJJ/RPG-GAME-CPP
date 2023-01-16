#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "Events.h"

class ActionVisitor;

// Part of Controller
class Chamber {
public:
    virtual void action(ActionVisitor visitor, shared_ptr<View> view) = 0;
	void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

class BossChamber : public Chamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class PassageChamber : public Chamber {};
class NormalChamber : public PassageChamber {};
class SafeChamber : public PassageChamber {};

class MonsterRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TrapRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class PotionRoom : public NormalChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TreasureRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class HealthRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TraderRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class EmptyRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class StartingRoom : public SafeChamber {
public:
    void action(ActionVisitor visitor, shared_ptr<View> view);
    shared_ptr<EventNode> prepareEventsGraph();
};

class ChamberNode {
public:
	ChamberNode(shared_ptr<Chamber> curr);
	shared_ptr<Chamber> current;
	shared_ptr<ChamberNode> option1;
	shared_ptr<ChamberNode> option2;
};


// Part of Controller
class IVisitor {
public:
    virtual ~IVisitor() {}
    virtual void visitMonsterRoom(MonsterRoom room, shared_ptr<View> view) = 0;
    virtual void visitTrapRoom(TrapRoom room, shared_ptr<View> view) = 0;
    virtual void visitPotionRoom(PotionRoom room, shared_ptr<View> view) = 0;
    virtual void visitTreasureRoom(TreasureRoom room, shared_ptr<View> view) = 0;
    virtual void visitHealthRoom(HealthRoom room, shared_ptr<View> view) = 0;
    virtual void visitTraderRoom(TraderRoom room, shared_ptr<View> view) = 0;
    virtual void visitEmptyRoom(EmptyRoom room, shared_ptr<View> view) = 0;
    virtual void visitStartingRoom(StartingRoom room, shared_ptr<View> view) = 0;
    virtual void visitBossRoom(BossChamber room, shared_ptr<View> view) = 0;
};

// Part of Controller
class ActionVisitor : public IVisitor {
public:
    ActionVisitor(shared_ptr<Hero> h);
    void visitMonsterRoom(MonsterRoom room, shared_ptr<View> view) override;
    void visitTrapRoom(TrapRoom room, shared_ptr<View> view) override;
    void visitPotionRoom(PotionRoom room, shared_ptr<View> view) override;
    void visitTreasureRoom(TreasureRoom room, shared_ptr<View> view) override;
    void visitHealthRoom(HealthRoom room, shared_ptr<View> view) override;
    void visitTraderRoom(TraderRoom room, shared_ptr<View> view) override;
    void visitEmptyRoom(EmptyRoom room, shared_ptr<View> view) override;
    void visitStartingRoom(StartingRoom room, shared_ptr<View> view) override;
    void visitBossRoom(BossChamber room, shared_ptr<View> view) override;

private:
    void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h, shared_ptr<View> view);
    shared_ptr<Observer> obs;
};

#endif