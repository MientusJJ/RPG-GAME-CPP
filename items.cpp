#include "items.h"

using namespace std;


Weapon::Weapon(int level) : Item(level) {
    type = weapon;

    int min = 1 + (level - 1) * 2;
    int max = min + 9;

    min_damage = static_cast<int>(round(makeRand(min, min + 9)));
    max_damage = static_cast<int>(round(makeRand(min_damage, max)));
    critical_chance = makeRand(1, 15);

    value = level * 100;
}
Sword::Sword(int level) : Weapon(level) {
	int x = static_cast<int>(round(makeRand(1, 10)));
	// 30% chance for bonus
	if (x > 3)
		main_stat = 0;
	else
		main_stat = static_cast<int>(round(makeRand(level, 2*level)));

	int r = static_cast<int>(round(makeRand(0, namesTableSize-1)));
	name = namesForSwords[r];
}
MagicStick::MagicStick(int level) : Weapon(level) {
    int x = static_cast<int>(round(makeRand(1, 10)));

    // 30% chance for bonus
    if (x > 3)
        main_stat = 0;
    else
        main_stat = static_cast<int>(round(makeRand(level, 2 * level)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForMagicSticks[r];
}
  


Bow::Bow(int level) : Weapon(level) {
    int x = static_cast<int>(round(makeRand(1, 10)));

    // 30% chance for bonus
    if (x > 3)
        main_stat = 0;
    else
        main_stat = static_cast<int>(round(makeRand(level, 2 * level)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForBows[r];
}
   

Armor::Armor(int level) : Item(level) {
    type = armor;

    int min = 1 + (level - 1) * 2;
    int x = static_cast<int>(round(makeRand(1, 10)));

    defense = static_cast<int>(round(makeRand(min, min+5)));
    // 40% chance for bonus
    if (x > 4)
        health = 0;
    else
        health = static_cast<int>(round(makeRand(level*50, level*50+500)));

    value = level * 120;

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForArmors[r];
}



Headgear::Headgear(int level) : Item(level) {
    type = headgear;

    int min = level;
    defense = static_cast<int>(round(makeRand(min, min+2)));

    value = level * 70;
}



Helmet::Helmet(int level) : Headgear(level) {
    health = static_cast<int>(round(makeRand(level*10, level * 10+200)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForHelmets[r];
}



MagicHat::MagicHat(int level) : Headgear(level) {
    intelligence = static_cast<int>(round(makeRand(level, level+1)));
    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForMagicHats[r];
}


Talisman::Talisman(int level) : Item(level) {
    type = talisman;

    critical_chance = makeRand(1.0, 10.0);

    value = level * 60;
}



ScoutTalisman::ScoutTalisman(int level) : Talisman(level) {
    agility = static_cast<int>(round(makeRand(level, level+1)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForTalismans[r];
}

WarriorTalisman::WarriorTalisman(int level) : Talisman(level) {
    strength = static_cast<int>(round(makeRand(level, level+1)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForTalismans[r];
}
   


MageTalisman::MageTalisman(int level) : Talisman(level) {
    intelligence = static_cast<int>(round(makeRand(level, level+1)));

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForTalismans[r];
}


Shield::Shield(int level) : Item(level) {
    type = shield;

    defense = static_cast<int>(round(makeRand(level, level+5)));
    block_chance = makeRand(1.0, 20.0);
    value = level * 90;

    int r = static_cast<int>(round(makeRand(0, namesTableSize - 1)));
    name = namesForShields[r];
}


unique_ptr<Item>  ItemFactory::createItem(int level, ItemType type, Profession profession)
{
    unique_ptr<Item>item = nullptr;

   if (type == weapon)
   {
       if (profession == warrior) {
           item = make_unique<Sword>(level);
       }
       else if (profession == scout) {
           item = make_unique<Bow>(level);
       }
       else if (profession == mage) {
           item = make_unique<MagicStick>(level);
       }
       else {
           cout << "wrong class value" << endl;
       }
   }
   else if (type == armor)
   {
       item = make_unique<Armor>(level);
   }
   else if (type == headgear)
   {
       if (profession == warrior) {
           item = make_unique<Helmet>(level);
       }
       else if (profession == scout) {
           item = make_unique<Helmet>(level);
       }
       else if (profession == mage) {
           item = make_unique<MagicHat>(level);
       }
       else {
           cout << "wrong class value" << endl;
       }
   }
   else if (type == talisman)
   {
       if (profession == warrior) {
           item = make_unique<WarriorTalisman>(level);
       }
       else if (profession == scout) {
           item = make_unique<ScoutTalisman>(level);
       }
       else if (profession == mage) {
           item = make_unique<MageTalisman>(level);
       }
       else {
           cout << "wrong class value" << endl;
       }
   }
   else if (type == shield)
   {
       if (profession == warrior)
           item = make_unique<Shield>(level);
       else {
           cout << "wrong class value" << endl;
       }
   }


   return item;
};


