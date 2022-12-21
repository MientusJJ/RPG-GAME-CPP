#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Items.h"
class Equipment
{
public:
	Equipment(int, Profession);
	~Equipment();
	bool ChangeItem(shared_ptr<Item>&);
	shared_ptr<Item> weapon_slot;
	shared_ptr<Item> armor_slot;
	shared_ptr<Item> shield_slot;
	shared_ptr<Item> headgear_slot;
	shared_ptr<Item> talisman_slot;
private:
	unique_ptr<ItemFactory> fac;
};
#endif
