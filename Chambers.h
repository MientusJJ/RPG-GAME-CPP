#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "items.h"
#include "Character.h"
#include "Events.h"
#include "Strategy.h"

class IVisitor;
class ActionVisitor;

class Chamber {
protected:
    int chamber_ID;
	string name;
    shared_ptr<Hero> hero;

public:
	Chamber(shared_ptr<Hero>& h);
    virtual void action(ActionVisitor visitor) = 0;
    shared_ptr<Hero> getHero();
	string getName();
	void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

class BossChamber : public Chamber {
protected:
	shared_ptr<monster> boss_monster;

public:
	BossChamber(shared_ptr<Hero>&h);
    shared_ptr<monster> getMonster();
    void action(ActionVisitor visitor);

private:
	void finalFight(shared_ptr<Hero>&h);
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
protected:
	shared_ptr<monster> normal_monster;
    shared_ptr<Chest> chest;

public:
	MonsterRoom(shared_ptr<Hero>&h);
    shared_ptr<Chest> getChest();
    shared_ptr<monster> getMonster();
    void action(ActionVisitor visitor);
};

class TrapRoom : public NormalChamber {
public:
	TrapRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
};

class PotionRoom : public NormalChamber {
public:
	PotionRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
};

class TreasureRoom : public SafeChamber {
protected:
    shared_ptr<Chest> chest;

public:
	TreasureRoom(shared_ptr<Hero>&h);
    shared_ptr<Chest> getChest();
    void action(ActionVisitor visitor);
};

class HealthRoom : public SafeChamber {
public:
	HealthRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
};

class TraderRoom : public SafeChamber {
protected:
	shared_ptr<Item> item1;
	shared_ptr<Item> item2;
	shared_ptr<Item> item3;
    shared_ptr<Strategy> _buyingstrategy;
public:
	TraderRoom(shared_ptr<Hero>&h);
    shared_ptr<Item> getItem1();
    shared_ptr<Item> getItem2();
    shared_ptr<Item> getItem3();
    shared_ptr<Strategy> getStrategy();
    void action(ActionVisitor visitor);
};

class EmptyRoom : public SafeChamber {
public:
	EmptyRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
};

class StartingRoom : public SafeChamber {
public:
	StartingRoom(shared_ptr<Hero>&h);
    void action(ActionVisitor visitor);
};

class ChamberNode {
public:
	ChamberNode(shared_ptr<Chamber> curr);
	shared_ptr<Chamber> current;
	shared_ptr<ChamberNode> option1;
	shared_ptr<ChamberNode> option2;
};


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

class ActionVisitor : public IVisitor {
public:
    void visitMonsterRoom(MonsterRoom room) override;
    void visitTrapRoom(TrapRoom room) override;
    void visitPotionRoom(PotionRoom room) override;
    void visitTreasureRoom(TreasureRoom room) override;
    void visitHealthRoom(HealthRoom room) override;
    void visitTraderRoom(TraderRoom room) override;
    void visitEmptyRoom(EmptyRoom room) override;
    void visitStartingRoom(StartingRoom room) override;
    void visitBossRoom(BossChamber room) override;
};

#endif