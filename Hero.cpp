#include "Hero.h"

Hero Hero::*hero = nullptr;
Hero *Hero::getInstance()
{
	if (hero == nullptr)
	{
		hero = new Hero();
	}
	return hero;
}
Hero::Hero()
{
}
Hero::~Hero()
{
	delete EQ;
}
void showStatistics();
void chooseClass();
void death();
void setmaxHealth(int);
void setdefense(int);
void setlevel(int);
void setminimalAttack(int);
void setmaximalAttack(int);
void setName(string);
string getName();
