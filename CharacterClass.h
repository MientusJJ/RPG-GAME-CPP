#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;
enum Profession
{
	warrior = 1,
	scout = 2,
	mage = 3
};
double chance()
{
	return rand() % 100;
}
class CharacterClass
{
public:
	 CharacterClass();
	 virtual ~CharacterClass()=0;
	 Profession getProf();
	 int getmainStat();
	 int getattackModifier();
	 int getvitalityModifier();
	 int getdefenseModifier();
	 string getmainStatName();
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

