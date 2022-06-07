#pragma once
#include "items.cpp"
class Equipment
{
public:
	Equipment(int, Profession);
	~Equipment();
	bool ChangeItem(Item *,ItemType );
	Item *weapon_slot;
	Item *armor_slot;
	Item *shield_slot;
	Item *headgear_slot;
	Item *talisman_slot;
private:
	ItemFactory *fac;
};

