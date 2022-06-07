#include "Equipment.h"
Equipment::Equipment(int lvl,Profession prof)
{
	fac = new ItemFactory;
	weapon_slot = fac->createItem(lvl, weapon, prof);
	armor_slot = fac->createItem(lvl, armor, prof);
	talisman_slot = fac->createItem(lvl, talisman, prof);
	headgear_slot = fac->createItem(lvl, headgear, prof);
	if (prof == warrior)
	{
		shield_slot = fac->createItem(lvl, shield, prof);
	}
	else
	{
		shield_slot = nullptr;
	}
	delete fac;
}
bool Equipment::ChangeItem(Item * i,ItemType t)
{
	if (t == weapon)
	{
		delete this->weapon_slot;
		this->weapon_slot = i;
	}
	else if (t == armor)
	{
		delete this->armor_slot;
		this->armor_slot = i;
	}
	else if(t==talisman)
	{
		delete this->talisman_slot;
		this->talisman_slot = i;
	}
	else if (t = headgear)
	{
		delete this->headgear_slot;
		this->headgear_slot = i;
	}
	else if (t == shield)
	{
		delete this->shield_slot;
		this->shield_slot = i;
	}
	return true;
}
Equipment::~Equipment()
{
	delete weapon_slot;
	delete shield_slot;
	delete armor_slot;
	delete headgear_slot;
	delete talisman_slot;
}
