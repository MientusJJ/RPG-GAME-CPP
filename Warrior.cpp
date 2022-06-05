#include "Warrior.h"
Warrior::Warrior()
{
	
	this->setattackModifier(1);
	this->setdefenseModifier(4);
	this->setvitalityModifier(4);
	this->setProf(warrior);
	this->setmainStat(5);
	this->setspecialAbility("You have shield, which is able to block your opponent's attacks");
	this->setmainStatName("Strength");
}
Warrior::~Warrior()
{
}