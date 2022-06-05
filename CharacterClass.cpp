#include "CharacterClass.h"
#
CharacterClass::CharacterClass()
{

}
CharacterClass::~CharacterClass()
{
}
Profession CharacterClass::getProf()
{
	return this->Prof;
}
void CharacterClass::setProf(Profession p)
{
	this->Prof = p;
	return;
}
int CharacterClass::getattackModifier()
{
	return this->attackModifier;
}
void CharacterClass::setattackModifier(int am)
{
	this->attackModifier = am;
	return;
}
int CharacterClass::getdefenseModifier()
{
	return this->defenseModifier;
}
void CharacterClass::setdefenseModifier(int dm)
{
	this->defenseModifier = dm;
	return;
}
int CharacterClass::getmainStat()
{
	return this->mainStat;
}
void CharacterClass::setmainStat(int ms)
{
	this->mainStat = ms;
	return;
}
int CharacterClass::getvitalityModifier()
{
	return this->vitalityModifier;
}
void CharacterClass::setvitalityModifier(int vm)
{
	this->vitalityModifier = vm;
	return;
}
string CharacterClass::getspecialAbility()
{
	return this->SpecialAbility;
}
void CharacterClass::setspecialAbility(string sa)
{
	this->SpecialAbility = sa;
	return;
}
string CharacterClass::getmainStatName()
{
	return this->mainStatName;
}
void CharacterClass::setmainStatName(string sm)
{
	this->mainStatName = sm;
	return;
}

