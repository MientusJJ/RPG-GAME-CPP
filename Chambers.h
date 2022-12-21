#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "items.h"
#include "Character.h"
#include "Events.h"
class Chamber {
protected:
	int chamber_ID;
	string name;
	shared_ptr<Hero> hero;

public:
	Chamber(shared_ptr<Hero>& h);
	virtual void takeAction(shared_ptr<Hero>&h)=0;
	int getChamberID();
	string getName();
	void eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h);
};

class BossChamber : public Chamber {
protected:
	shared_ptr<monster> boss_monster;

public:
	BossChamber(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void finalFight(shared_ptr<Hero>&h);
};

class PassageChamber : public Chamber {
public:
	PassageChamber(shared_ptr<Hero>& h);
	virtual void takeAction(shared_ptr<Hero>&h);
};

class NormalChamber : public PassageChamber {
public:
	NormalChamber(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);
};
class SafeChamber : public PassageChamber {
public:
	SafeChamber(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);
};

class MonsterRoom : public NormalChamber {
protected:
	shared_ptr<monster> normal_monster;
	unique_ptr<Chest> chest;

public:
	MonsterRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void fight(shared_ptr<Hero>&h);
	void runAway(shared_ptr<Hero>&h);
};

class TrapRoom : public NormalChamber {
public:
	TrapRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void getDamage(shared_ptr<Hero>&h);
};

class PotionRoom : public NormalChamber {
public:
	PotionRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void drinkPotion(shared_ptr<Hero>&h);
};

class TreasureRoom : public SafeChamber {
protected:
	unique_ptr<Chest> chest;

public:
	TreasureRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void openBox(shared_ptr<Hero>&h);
};

class HealthRoom : public SafeChamber {
public:
	HealthRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void healthYourself(shared_ptr<Hero>&h);
};

class TraderRoom : public SafeChamber {
protected:
	shared_ptr<Item> item1;
	shared_ptr<Item> item2;
	shared_ptr<Item> item3;

public:
	TraderRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);

private:
	void seeItems(shared_ptr<Hero>&h);
	void buyItem(shared_ptr<Hero>&h);
};

class EmptyRoom : public SafeChamber {
public:
	EmptyRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);
};

class StartingRoom : public SafeChamber {
public:
	StartingRoom(shared_ptr<Hero>&h);
	void takeAction(shared_ptr<Hero>&h);
};
class ChamberNode {
public:
	ChamberNode(shared_ptr<Chamber> curr);
	shared_ptr<Chamber> current;
	shared_ptr<ChamberNode> option1;
	shared_ptr<ChamberNode> option2;
};
#endif