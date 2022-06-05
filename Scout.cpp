#include "Scout.h"

Scout::Scout()
{
	this->setattackModifier(2);
	this->setdefenseModifier(2);
	this->setvitalityModifier(2);
	this->setProf(scout);
	this->setmainStat(10);
	this->setspecialAbility("You have 50 percent chance to dodge your opponent's attack");
	this->setmainStatName("Agility");
}
Scout::~Scout()
{

}