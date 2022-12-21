#include "Character.h"
#include <thread>



const int defaultHealth = 50;
const double defaultCriticalChance = 3.;
const int defaultAttackMin = 2;
const int defaultAttackMax = 5;
const int counterAttackMin = 2;
const int counterAttackMax = 3;
const int defaultMonsterDefense = 3;
const double defaultMonsterCriticalChance = 15.;
const int defaultHealthMonster = 80;
const int defaultAttackMonsterMin = 20;
const int defaultAttackMonsterMax = 50;

Character::Character() {

}
Character::~Character() {

}
int Character::getminimalAttack()
{
	return this->minimalAttack;
}
int Character::getmaximalAttack()
{
	return this->maximalAttack;
}
int Character::getlevel()
{
	return this->level;
}
int Character::getcurrentHealth()
{
	return this->currentHealth;
}
void Character::setcurrentHealth(int h)
{
	if (h > this->getmaxHealth())
	{
		h = this->getmaxHealth();
	}
	this->currentHealth = h;
}
int Character::getmaxHealth()
{
	return this->maxHealth;
}

int Character::getdefense()
{
	return this->defense;
}
string Character::getName()
{
	return this->name;
}
int Character::getDamage(int d)
{
	if (d >= this->getcurrentHealth())
	{
		this->setcurrentHealth(0);
	}
	else
	{
		this->setcurrentHealth(this->getcurrentHealth() - d);
	}
	return this->getcurrentHealth();
}
double Character::getcriticalChance()
{
	return this->criticalChance;
}
double Character::getBlockChance()
{
	return this->blockChance;
}
void Character::setcriticalChance(double c)
{
	this->criticalChance = c;
	return;
}
int Character::useSpecialAttack()
{
	if (chance() <= this->getcriticalChance())
	{
		return 2;
	}
	return 1;
}
Profession Character::getProf()
{
	return this->Class->getProf();
}
void Character::attackOpponent(shared_ptr<Character>& opponent)
{
	if (!this->useSpecialEffect(opponent))
	{
		return;
	}
	int damage = static_cast<int>(round(makeRand(this->getminimalAttack(), this->getmaximalAttack())));
	damage = damage * this->useSpecialAttack() - opponent->getdefense();
	if (damage < 1) damage = 1;
	opponent->getDamage(damage);
	cout << this->getName() << " dealt " << damage << " damage to " << opponent->getName() << endl;
	cout << "Current health of " << opponent->getName() << " is " << opponent->getcurrentHealth() << endl;
	return;
}
bool Character::useSpecialEffect(shared_ptr<Character>& opponent)
{
	if (this->Class->getProf() == mage || opponent->Class->getProf() == mage)
	{
		return true;
	}
	if (opponent->Class->getProf() == scout)
	{
		if (chance() <= dodge)
		{
			cout << opponent->getName() << " dodged the hit from " << this->getName() << endl;
			return false;
		}
		return true;
	}
	if (opponent->Class->getProf() == warrior)
	{
		if (chance() <= opponent->getBlockChance())
		{
			cout << opponent->getName() << " blocked the hit from " << this->getName() << endl;
			return false;
		}
		return true;
	}
	return true;
}

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
string CharacterClass::getProfName()
{
	if (this->getProf() == warrior)
	{
		return "Warrior";
	}
	else if (this->getProf() == scout)
	{
		return "Scout";
	}
	else
	{
		return "Mage";
	}
}

Scout::Scout()
{
	this->setattackModifier(2);
	this->setdefenseModifier(2);
	this->setvitalityModifier(2);
	this->setProf(scout);
	this->setmainStat(10);
	this->setspecialAbility("You have 33 percent chance to dodge your opponent's attack");
	this->setmainStatName("Agility");
}
Scout::~Scout()
{

}
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
void monster::chooseClass()
{
	int p = static_cast<int>(round(makeRand(1, 3)));
	if (p == 1)
	{
		this->Class = make_unique<Warrior>();
	}
	else if (p == 2)
	{
		this->Class = make_unique<Scout>();
	}
	else
	{
		this->Class = make_unique<Mage>();
	}
}
void monster::setmaxHealth()
{
	this->maxHealth = defaultHealthMonster * this->getlevel()*this->Class->getvitalityModifier();
	this->setcurrentHealth(this->maxHealth);
	return;
}
void monster::setdefense()
{
	this->defense = defaultMonsterDefense * this->getlevel()*this->Class->getdefenseModifier();
	return;
}
void monster::setlevel(int l)
{
	this->level = l;
	return;
}
void monster::setBlockChance()
{
	if (this->Class->getProf() == warrior)
	{
		this->blockChance = 15.;
	}
	else
	{
		this->blockChance = 0.;
	}
	return;
}
void monster::setminimalAttack()
{
	this->minimalAttack = defaultAttackMonsterMin * this->getlevel()*this->Class->getattackModifier();
	return;
}
void monster::setmaximalAttack()
{
	this->maximalAttack = defaultAttackMonsterMax * this->getlevel()*this->Class->getattackModifier();
	return;
}
void monster::setName(bool p)
{
	if (!p)
	{
		int r = static_cast<int>(round(makeRand(0, sizenamesforMonsters-1)));
		this->name = namesforMonsters[r];
	}
	else
	{
		int r = static_cast<int>(round(makeRand(0, sizenamesforBosses - 1)));
		this->name = namesforBosses[r];
	}
	
	return;
}
monster::monster(int lvl,bool p)
{
	setALL(lvl);
	this->setName(p);
}

void monster::setALL(int lvl)
{
	this->chooseClass();
	this->setlevel(lvl);
	this->setmaxHealth();
	this->setdefense();
	this->setminimalAttack();
	this->setmaximalAttack();
	this->setcriticalChance(defaultMonsterCriticalChance);
}
monster::~monster()
{
}

shared_ptr<Hero> Hero::hero = nullptr;
shared_ptr<Hero>& Hero::getInstance()
{
	if (hero == nullptr)
	{
		hero.reset(new Hero());
	}
	return hero;
}
Hero::Hero()
{
	this->setName();
	this->chooseClass();
	this->setlevel(1);
	this->setMoney(100);
	EQ = make_unique<Equipment>(this->getlevel(), this->Class->getProf());
	this->setAllStats();
	this->setcurrentHealth(this->getmaxHealth());


}
Hero::~Hero()
{
}
void Hero::chooseClass()
{
	cout << "Choose class of " << this->getName() << " \nWrite 1 if you want warrior \nWrite 2 if you want scout \nWrite 3 if you want mage \n";
	string  ch;
	cin >> ch;
	while (ch != "1" && ch != "2" && ch != "3")
	{
		cout << "Bad Number. Choose number between 1 and 3\n";
		cin >> ch;
	}
	cout << "Your class for the whole game is: ";
	if (ch == "1")
	{
		this->Class = make_unique<Warrior>();
		cout << "Warrior\n";
	}
	else if (ch == "2")
	{
		this->Class = make_unique<Scout>();
		cout << "Scout\n";
	}
	else
	{
		this->Class = make_unique<Mage>();
		cout << "Mage\n";
	}

}
void Hero::setlevel(int s)
{
	this->level = s;
}

void Hero::setminimalAttack(int s)
{
	this->minimalAttack = (s + defaultAttackMin * this->getlevel())*this->Class->getattackModifier();
	return;
}
void Hero::setmaximalAttack(int s)
{
	this->maximalAttack = (s + defaultAttackMax * this->getlevel())*this->Class->getattackModifier();
	return;
}
void Hero::setName()
{
	cout << "Write name of your hero:" << endl;
	string n;
	cin >> n;
	this->name = n;
	return;
}
void Hero::levelup()
{
	++this->level;
	this->setAllStats();
	this->setcurrentHealth(this->getcurrentHealth() + double(this->getmaxHealth()*0.3));
	return;
}
void Hero::showStatistics()
{
	
	cout << endl << "Statistics of your hero:" << endl;
	cout << "Name: " << this->getName() << endl;
	cout << "Class: " << this->Class->getProfName() << endl;
	cout << "Main Stat name: " << this->Class->getmainStatName() << endl;
	cout << "Skill: " << this->Class->getspecialAbility() << endl;
	cout << "Level: " << this->getlevel() << endl;
	cout << "Main Stat: " << this->EQ->weapon_slot->getMainStat() + this->EQ->headgear_slot->getMainStat() + this->Class->getmainStat() + this->EQ->talisman_slot->getMainStat() << endl;
	cout << "Max health: " << this->getmaxHealth() << endl;
	cout << "Current health: " << this->getcurrentHealth() << endl;
	cout << "Minimal damage: " << this->getminimalAttack() << endl;
	cout << "Maximal damage: " << this->getmaximalAttack() << endl;
	cout << "Critical chance: " << this->getcriticalChance() << "%" << endl;
	cout << "Defense: " << this->getdefense() << endl;
	if (this->Class->getProf() == warrior)
	{
		cout << "Block Chance: " << this->getBlockChance() << "%" << endl;
	}
	cout << "Amount of money: " << this->getMoney() << endl;
	return;
}
void Hero::showOneItem(ItemType it, Profession p)
{
	if (it == weapon)
	{
		cout << "Weapon:\n\t name: " << this->EQ->weapon_slot->getName() << "\n\t minimal Damage: " << this->EQ->weapon_slot->getMinDamage() << "\n\t maximal Damage: " << this->EQ->weapon_slot->getMaxDamage() << "\n\t " << this->EQ->weapon_slot->getMainStatName() << ": " << this->EQ->weapon_slot->getMainStat() << "\n\t value: " << this->EQ->weapon_slot->getValue() << endl;
	}
	else if (it == talisman)
	{
		cout << "Talisman:\n\t name: " << this->EQ->talisman_slot->getName() << "\n\t " << this->EQ->talisman_slot->getMainStatName() << ": " << this->EQ->talisman_slot->getMainStat() << "\n\t Critical Chance: " << this->EQ->talisman_slot->getCriticalChance() << "\n\t value: " << this->EQ->talisman_slot->getValue() << endl;
	}
	else if (it == shield)
	{
		cout << "Shield:\n\t name: " << this->EQ->shield_slot->getName() << "\n\t Defense: " << this->EQ->shield_slot->getDefense() << "\n\t Block Chance: " << this->EQ->shield_slot->getBlockChance() << "\n\t value: " << this->EQ->shield_slot->getValue() << endl;
	}
	else if (it == armor)
	{
		cout << "Armor:\n\t name: " << this->EQ->armor_slot->getName() << "\n\t Defense: " << this->EQ->armor_slot->getDefense() << "\n\t Health: " << this->EQ->armor_slot->getHealth() << "\n\t value: " << this->EQ->armor_slot->getValue() << endl;
	}
	else if (it == headgear)
	{
		cout << "Headgear:\n\t name: " << this->EQ->headgear_slot->getName() << "\n\t Defense: " << this->EQ->headgear_slot->getDefense();
		if (p == mage)
		{
			cout << "\n\t " << this->EQ->headgear_slot->getMainStatName() << ": " << this->EQ->headgear_slot->getMainStat();
		}
		else
		{
			cout << ":\n\t Health: " << this->EQ->headgear_slot->getHealth();
		}
		cout << "\n\t value: " << this->EQ->headgear_slot->getValue() << endl;
	}
	return;
}
void Hero::showEQ()
{
	cout << endl << "Equipment of your hero:" << endl;
	this->showOneItem(weapon, this->getProf());
	this->showOneItem(armor, this->getProf());
	if (this->Class->getProf() == warrior)
	{
		this->showOneItem(shield, this->getProf());
	}
	this->showOneItem(talisman, this->getProf());
	this->showOneItem(headgear, this->getProf());
	return;
}
void Hero::setAllStats()
{
	this->setmaxHealth(this->EQ->headgear_slot->getHealth() + this->EQ->armor_slot->getHealth());
	if (this->getcurrentHealth() > this->getmaxHealth())
	{
		this->setcurrentHealth(this->getmaxHealth());
	}
	this->setcriticalChance(this->EQ->talisman_slot->getCriticalChance() + this->EQ->weapon_slot->getCriticalChance() + defaultCriticalChance * this->getlevel());
	this->setdefense(this->EQ->armor_slot->getDefense() + this->EQ->headgear_slot->getDefense());
	this->setAttack(this->EQ->weapon_slot->getMainStat() + this->EQ->headgear_slot->getMainStat() + this->Class->getmainStat()+this->EQ->talisman_slot->getMainStat(), this->EQ->weapon_slot->getMinDamage(), this->EQ->weapon_slot->getMaxDamage());
	this->setBlockChance();
	return;
}
void Hero::setAttack(int ms, int weaponmin, int weaponmax)
{
	this->setminimalAttack(ms + weaponmin * counterAttackMin);
	this->setmaximalAttack(ms + weaponmax * counterAttackMax);
	return;
}
void Hero::setmaxHealth(int h)
{
	this->maxHealth = (this->getlevel()*defaultHealth + h)*this->Class->getvitalityModifier();
}
void Hero::setdefense(int d)
{
	if (this->Class->getProf() == warrior)
	{
		d += this->EQ->shield_slot->getDefense();
	}
	this->defense = d * this->Class->getdefenseModifier();
}
void Hero::setBlockChance()
{
	if (this->Class->getProf() == warrior)
	{
		this->blockChance = this->EQ->shield_slot->getBlockChance();
	}
	else
	{
		this->blockChance = 0;
	}
	return;
}
void Hero::setMoney(int m)
{
	this->money = m;
	return;
}
int Hero::getMoney()
{
	return this->money;
}
void Hero::ChangeEQ(shared_ptr<Item>&i)
{
	this->EQ->ChangeItem(i);
	this->setAllStats();

	cout << "Changing equipment completed" << endl;
	return;
}
bool Hero::fight(shared_ptr<Character>& opponent,bool boss)
{
	bool whoIsAttacking = true;
	chrono::milliseconds timespan(1000);
	while (this->getcurrentHealth() != 0 && opponent->getcurrentHealth() != 0)
	{
        cout << endl;
		if (whoIsAttacking)
		{
			this->attackOpponent(opponent);
		}
		else
		{
			shared_ptr<Character> h = this->getInstance();
			opponent->attackOpponent(h);
		}
		whoIsAttacking = !whoIsAttacking;

		if (boss)
		{
			this_thread::sleep_for(timespan);
		}
	}
	cout << endl;
	return this->getcurrentHealth() != 0;
}