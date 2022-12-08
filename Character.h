#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <memory>
#include "Equipment.h"

class CharacterClass
{
public:
	CharacterClass();
	virtual ~CharacterClass() = 0;
	Profession getProf();
	int getmainStat();
	int getattackModifier();
	int getvitalityModifier();
	int getdefenseModifier();
	string getmainStatName();
	string getProfName();
	string getspecialAbility();

protected:
	Profession Prof;
	int mainStat;
	int attackModifier;
	int vitalityModifier;
	int defenseModifier;
	void setspecialAbility(string);
	void setmainStatName(string);
	void setdefenseModifier(int);
	void setmainStat(int);
	void setvitalityModifier(int);
	void setattackModifier(int);
	void setProf(Profession);
	string mainStatName;
	string SpecialAbility;
};

class Scout : public CharacterClass
{
public:
	Scout();
	~Scout();
};

class Mage : public CharacterClass
{
public:
	Mage();
	~Mage();
};
class Warrior : public CharacterClass
{
public:
	Warrior();
	~Warrior();
};



class Character
{
public:
	Character();
	virtual ~Character()=0;
	int getminimalAttack();
	virtual void setminimalAttack() {}
	int getmaximalAttack();
	virtual void setmaximalAttack() {}
	int getlevel();
	virtual void setlevel(int) {}
	int getcurrentHealth();
	void setcurrentHealth(int);
	double getcriticalChance();
	void setcriticalChance(double);
	int getmaxHealth();
	virtual void setBlockChance() {};
	double getBlockChance();
	virtual void setmaxHealth() {}
	virtual void setdefense() {}
	int getdefense();
	int getDamage(int);
	virtual void chooseClass() {}
	string getName();
	virtual void setName() {}
	bool useSpecialEffect(shared_ptr<Character>& opponent);
	int useSpecialAttack();
	Profession getProf();
	void attackOpponent(shared_ptr<Character>& opponent);
protected:
	
	int minimalAttack;
	int maximalAttack;
	int level;
	int currentHealth;
	int maxHealth;
	int defense;
	double blockChance;
	string name;
	double criticalChance;
	unique_ptr<CharacterClass> Class;
};

class Hero : public Character
{
public:
	~Hero();
	static shared_ptr<Hero>& getInstance();
	Hero(Hero &other) = delete;
	void operator=(const Hero &) = delete;
	void showStatistics();
	void showEQ();
	void showOneItem(ItemType,Profession);
	void setAllStats();
	void chooseClass();
	void setmaxHealth(int);
	void setdefense(int);
	void setlevel(int);
	void setminimalAttack(int);
	void setmaximalAttack(int);
	void setAttack(int, int,int);
	void setName();
	void levelup();
	void setBlockChance();
	void setMoney(int);
	int getMoney();
	void ChangeEQ(unique_ptr<Item>&);
	bool fight(shared_ptr<Character>&,bool);
private:
	Hero();
	static shared_ptr<Hero> hero;
	int money;
	unique_ptr<Equipment> EQ;
};



class monster : public Character
{
public:
	monster(int,bool);
	~monster();
	void chooseClass();
	void setmaxHealth();
	void setdefense();
	void setlevel(int);
	void setminimalAttack();
	void setmaximalAttack();
	void setName(bool);
	void setBlockChance();
	void setALL(int);
private:
};
#endif