#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "items.h"
#include "Character.h"
#include "Events.h"
#include "Strategy.h"

class ActionVisitor;


class Chamber {
protected:
    int chamber_ID;
    shared_ptr<Hero> hero;

public:
	Chamber(shared_ptr<Hero>& h);
    virtual void action(ActionVisitor visitor) = 0;
	void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

class BossChamber : public Chamber {
public:
	BossChamber(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class PassageChamber : public Chamber {
public:
	PassageChamber(shared_ptr<Hero>& h);
};

class NormalChamber : public PassageChamber {
public:
	NormalChamber(shared_ptr<Hero>&h);
};
class SafeChamber : public PassageChamber {
public:
	SafeChamber(shared_ptr<Hero>&h);
};

class MonsterRoom : public NormalChamber {
public:
	MonsterRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TrapRoom : public NormalChamber {
public:
	TrapRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class PotionRoom : public NormalChamber {
public:
	PotionRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TreasureRoom : public SafeChamber {
public:
	TreasureRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class HealthRoom : public SafeChamber {
public:
	HealthRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class TraderRoom : public SafeChamber {
public:
	TraderRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class EmptyRoom : public SafeChamber {
public:
	EmptyRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class StartingRoom : public SafeChamber {
public:
	StartingRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
    shared_ptr<EventNode> prepareEventsGraph();
};

class ChamberNode {
public:
	ChamberNode(shared_ptr<Chamber> curr);
	shared_ptr<Chamber> current;
	shared_ptr<ChamberNode> option1;
	shared_ptr<ChamberNode> option2;
};


// Controller
class IVisitor {
public:
    virtual ~IVisitor() {}
    virtual void visitMonsterRoom(MonsterRoom room) = 0;
    virtual void visitTrapRoom(TrapRoom room) = 0;
    virtual void visitPotionRoom(PotionRoom room) = 0;
    virtual void visitTreasureRoom(TreasureRoom room) = 0;
    virtual void visitHealthRoom(HealthRoom room) = 0;
    virtual void visitTraderRoom(TraderRoom room) = 0;
    virtual void visitEmptyRoom(EmptyRoom room) = 0;
    virtual void visitStartingRoom(StartingRoom room) = 0;
    virtual void visitBossRoom(BossChamber room) = 0;
};

// Controller
class ActionVisitor : public IVisitor {
public:
    ActionVisitor(shared_ptr<Hero> h);
    void visitMonsterRoom(MonsterRoom room) override;
    void visitTrapRoom(TrapRoom room) override;
    void visitPotionRoom(PotionRoom room) override;
    void visitTreasureRoom(TreasureRoom room) override;
    void visitHealthRoom(HealthRoom room) override;
    void visitTraderRoom(TraderRoom room) override;
    void visitEmptyRoom(EmptyRoom room) override;
    void visitStartingRoom(StartingRoom room) override;
    void visitBossRoom(BossChamber room) override;

private:
    void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
    shared_ptr<Observer> obs;
};

#endif