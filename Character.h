#pragma once
#include "Equipment.h"
#include "CharacterClass.h"
using namespace std;
const double dodge = 33.0;
const double block = 20.;
class Character
{
public:
	Character();
	virtual ~Character()=0;
	int getminimalAttack();
	virtual void setminimalAttack(int);
	int getmaximalAttack();
	virtual void setmaximalAttack(int);
	int getlevel();
	virtual void setlevel(int);
	int getcurrentHealth();
	void setcurrentHealth(int);
	double getcriticalChance();
	void setcriticalChance(double);
	int getmaxHealth();
	virtual void setmaxHealth(int);
	virtual void setdefense(int);
	int getdefense();
	int getDamage(int);
	virtual void chooseClass();
	virtual string getName();
	virtual void setName(string);
	bool useSpecialEffect(Character *opponent);
	int useSpecialAttack();
	void attackOpponent(Character * opponent);
protected:
	
	int minimalAttack;
	int maximalAttack;
	int level;
	int currentHealth;
	int maxHealth;
	int defense;
	double criticalChance;
	CharacterClass *Class;
};

