#pragma once
#ifndef CHAMBER_H
#define CHAMBER_H
#include "items.h"
#include "Character.h"

class Chest {
protected:
	unique_ptr<Item> item;


public:
	Chest(shared_ptr<Hero>&h);
	void openBox(shared_ptr<Hero>&h);
};

class Chamber {
protected:
	int chamber_ID;
	string name;
	shared_ptr<Hero>hero;

public:
	Chamber(shared_ptr<Hero>& h);
	virtual unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
	int getChamberID();
	string getName();
};

class BossChamber : public Chamber {
protected:
	shared_ptr<monster> boss_monster;

public:
	BossChamber(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void finalFight(shared_ptr<Hero>&h);
};

class PassageChamber : public Chamber {
public:
	PassageChamber(shared_ptr<Hero>& h);
	virtual unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
	static unique_ptr<Chamber> goNext(shared_ptr<Hero>&h);
};

class NormalChamber : public PassageChamber {
public:
	NormalChamber(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
};
class SafeChamber : public PassageChamber {
public:
	SafeChamber(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
};

class MonsterRoom : public NormalChamber {
protected:
	shared_ptr<monster> normal_monster;
	unique_ptr<Chest> chest;

public:
	MonsterRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void fight(shared_ptr<Hero>&h);
	void runAway(shared_ptr<Hero>&h);
};

class TrapRoom : public NormalChamber {
public:
	TrapRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void getDamage(shared_ptr<Hero>&h);
};

class PotionRoom : public NormalChamber {
public:
	PotionRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void drinkPotion(shared_ptr<Hero>&h);
};

class TreasureRoom : public SafeChamber {
protected:
	unique_ptr<Chest> chest;

public:
	TreasureRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void openBox(shared_ptr<Hero>&h);
};

class HealthRoom : public SafeChamber {
public:
	HealthRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void healthYourself(shared_ptr<Hero>&h);
};

class TraderRoom : public SafeChamber {
protected:
	unique_ptr<Item> item1;
	unique_ptr<Item> item2;
	unique_ptr<Item> item3;

public:
	TraderRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);

private:
	void seeItems(shared_ptr<Hero>&h);
	void buyItem(shared_ptr<Hero>&h);
};

class EmptyRoom : public SafeChamber {
public:
	EmptyRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
};

class StartingRoom : public SafeChamber {
public:
	StartingRoom(shared_ptr<Hero>&h);
	unique_ptr<Chamber> takeAction(shared_ptr<Hero>&h);
};
#endif