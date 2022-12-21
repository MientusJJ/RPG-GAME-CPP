#include "Equipment.h"

Equipment::Equipment(int lvl,Profession prof)
{
	fac = make_unique<ItemFactory>();
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
}
bool Equipment::ChangeItem(shared_ptr<Item>& i)
{
	if (i->getType() == weapon)
	{
		this->weapon_slot = i;
	}
	else if (i->getType() == armor)
	{
		this->armor_slot = i;
	}
	else if (i->getType() == talisman)
	{
		this->talisman_slot = i;
	}
	else if (i->getType() == headgear)
	{
		this->headgear_slot = i;
	}
	else if (i->getType() == shield)
	{
		this->shield_slot = i;
	}
	return true;
}
Equipment::~Equipment()
{
}
