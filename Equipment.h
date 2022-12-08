#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Items.h"
class Equipment
{
public:
	Equipment(int, Profession);
	~Equipment();
	bool ChangeItem(unique_ptr<Item>&);
	unique_ptr<Item> weapon_slot;
	unique_ptr<Item> armor_slot;
	unique_ptr<Item> shield_slot;
	unique_ptr<Item> headgear_slot;
	unique_ptr<Item> talisman_slot;
private:
	unique_ptr<ItemFactory> fac;
};
#endif
