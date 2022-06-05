#pragma once
#include "Character.h"
#include "items.h"
class Hero : public Character
{
public:
	~Hero();
	static Hero *getInstance();
	Hero(Hero &other) = delete;
	void operator=(const Hero &) = delete;
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
private:
	Hero();
	static Hero *hero;
	int money;
	string nick;
	Equipment *EQ;
};

