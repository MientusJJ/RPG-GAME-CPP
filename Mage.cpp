#include "Mage.h"

Mage::Mage()
{
	this->setattackModifier(4);
	this->setdefenseModifier(1);
	this->setvitalityModifier(1);
	this->setProf(mage);
	this->setmainStat(20);
	this->setspecialAbility("Opponent is not able to block your attack");
	this->setmainStatName("Intelligence");
}
Mage::~Mage()
{
}
