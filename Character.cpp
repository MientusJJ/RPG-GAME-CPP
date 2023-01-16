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
void Character::attackOpponent(shared_ptr<Character>& opponent, shared_ptr<View> view)
{
	if (!this->useSpecialEffect(opponent, view))
	{
		return;
	}
	int damage = static_cast<int>(round(makeRand(this->getminimalAttack(), this->getmaximalAttack())));
	damage = damage * this->useSpecialAttack() - opponent->getdefense();
	if (damage < 1) damage = 1;
	opponent->getDamage(damage);

    view->ShowCourseOfRound(this->getName(), opponent->getName(), damage);
    view->ShowCurrentHealthAfterRound(opponent->getName(), opponent->getcurrentHealth());
	return;
}
bool Character::useSpecialEffect(shared_ptr<Character>& opponent, shared_ptr<View> view)
{
	if (this->Class->getProf() == mage || opponent->Class->getProf() == mage)
	{
		return true;
	}
	if (opponent->Class->getProf() == scout)
	{
		if (chance() <= dodge)
		{
            view->DodgedHit(opponent->getName(), this->getName());
			return false;
		}
		return true;
	}
	if (opponent->Class->getProf() == warrior)
	{
		if (chance() <= opponent->getBlockChance())
		{
            view->BlockedHit(opponent->getName(), this->getName());
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
	else if(this->getProf()==mage)
	{
		return "Mage";
	}
	else
	{
		return "undefined";
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
	//this->setName("xxx");
	this->chooseClass(1);
	this->setlevel(1);
	this->setMoney(100);
	EQ = make_unique<Equipment>(this->getlevel(), this->Class->getProf());
	this->setAllStats();
	this->setcurrentHealth(this->getmaxHealth());


}
Hero::~Hero()
{
}
void Hero::setcurrentHealth(int h)
{
	Character::setcurrentHealth(h);
	if(!this->getcurrentHealth())
	{
		this->Notify();
	}
}
void Hero::AddObserver(shared_ptr<Observer> o)
{
	this->obs.push_back(o);
}
void Hero::DeleteObserver(shared_ptr<Observer> o)
{
	this->obs.remove(o);
}
void Hero::Notify()
{
	for(auto it= this->obs.begin();it!=this->obs.end();it++)
	{
		(*it)->setTrue();
	}

}

void Hero::chooseClass(int ch)
{
    if (ch == 1)
		this->Class = make_unique<Warrior>();
	else if (ch == 2)
		this->Class = make_unique<Scout>();
	else
		this->Class = make_unique<Mage>();
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
void Hero::setName(string n)
{
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
void Hero::showStatistics(shared_ptr<View> view)
{
    int mainStat = this->EQ->weapon_slot->getMainStat() + this->EQ->headgear_slot->getMainStat() + this->Class->getmainStat() + this->EQ->talisman_slot->getMainStat();

    view->ShowStatistics(this->getName(), this->Class->getProfName(), this->Class->getmainStatName(),
                         this->Class->getspecialAbility(), this->getlevel(), mainStat, this->getmaxHealth(),
                         this->getcurrentHealth(), this->getminimalAttack(), this->getmaximalAttack(),
                         this->getcriticalChance(), this->getdefense(), this->getMoney(), this->getBlockChance());

	return;
}
void Hero::showOneItem(ItemType it, Profession p, shared_ptr<View> view)
{
    int val1, val2, val3;
    string mainStat, name, type;
    int value;

	if (it == weapon)
	{
        type = "weapon";
        name = this->EQ->weapon_slot->getName();
        val1 = this->EQ->weapon_slot->getMinDamage();
        val2 = this->EQ->weapon_slot->getMaxDamage();
        val3 = this->EQ->weapon_slot->getMainStat();
        mainStat = this->EQ->weapon_slot->getMainStatName();
        value = this->EQ->weapon_slot->getValue();
	}
	else if (it == talisman)
	{
        type = "talisman";
        name = this->EQ->talisman_slot->getName();
        val1 = this->EQ->talisman_slot->getMainStat();
        val2 = this->EQ->talisman_slot->getCriticalChance();
        mainStat = this->EQ->talisman_slot->getMainStat();
        value = this->EQ->talisman_slot->getValue();
	}
	else if (it == shield)
	{
        type = "shield";
        name = this->EQ->shield_slot->getName();
        val1 = this->EQ->shield_slot->getDefense();
        val2 = this->EQ->shield_slot->getBlockChance();
        value = this->EQ->shield_slot->getValue();
	}
	else if (it == armor)
	{
        type = "armor";
        name = this->EQ->armor_slot->getName();
        val1 = this->EQ->armor_slot->getDefense();
        val2 = this->EQ->armor_slot->getHealth();
        value = this->EQ->armor_slot->getValue();
	}
	else if (it == headgear)
	{
        type = "headgear";
        name = this->EQ->headgear_slot->getName();
        val1 = this->EQ->headgear_slot->getDefense();

        if (p == mage)
        {
            val2 = this->EQ->headgear_slot->getMainStat();
            mainStat = this->EQ->headgear_slot->getMainStatName();
        }
        else
            val2 = this->EQ->headgear_slot->getHealth();

        value = this->EQ->headgear_slot->getValue();
	}

    string proff;
    if (p == warrior)
        proff = "Warrior";
    else if (p == scout)
        proff = "Scout";
    else if (p == mage)
        proff = "Mage";

    view->ShowOneItem(type, proff, value, name, val1, val2, val3, mainStat);
	return;
}
void Hero::showEQ(shared_ptr<View> view)
{
    string prof = this->Class->getProfName();
    string weaponName = this->EQ->weapon_slot->getName();
    int minDamage = this->EQ->weapon_slot->getMinDamage();
    int maxDamage = this->EQ->weapon_slot->getMaxDamage();
    string mainStateName =this->EQ->weapon_slot->getMainStatName();
    int weaponMainStat = this->EQ->weapon_slot->getMainStat();
    int weaponValue = this->EQ->weapon_slot->getValue();
    string talismanName = this->EQ->talisman_slot->getName();
    string talismanMainStatName = this->EQ->headgear_slot->getMainStatName();
    int talismanMainStat = this->EQ->talisman_slot->getMainStat();
    int talismanCrit = this->EQ->talisman_slot->getCriticalChance();
    int talismanValue = this->EQ->talisman_slot->getValue();
    string armorName = this->EQ->armor_slot->getName();
    int armorDef = this->EQ->armor_slot->getDefense();
    int armorHealth = this->EQ->armor_slot->getHealth();
    int armorValue = this->EQ->armor_slot->getValue();
    string headGearName = this->EQ->headgear_slot->getName();
    int headGearDef = this->EQ->headgear_slot->getDefense();
    int headGearVal;
    int headgearValue = this->EQ->headgear_slot->getValue();
    string headGearMainstat;
    string shieldName;
    int shieldDef;
    int shieldBlockChance;
    int shieldValue;

    if (this->getProf() == mage)
    {
        headGearVal = this->EQ->headgear_slot->getMainStat();
        headGearMainstat = this->EQ->headgear_slot->getMainStatName();
    }
    if (this->getProf() == warrior)
    {
        shieldName = this->EQ->shield_slot->getName();
        shieldDef = this->EQ->shield_slot->getDefense();
        shieldBlockChance = this->EQ->shield_slot->getBlockChance();
        shieldValue = this->EQ->shield_slot->getValue();
    }

    view->ShowEqiupment(prof, weaponName, minDamage, maxDamage, mainStateName,
                        weaponMainStat, weaponValue, talismanName, talismanMainStatName,
                        talismanMainStat, talismanCrit, talismanValue, armorName, armorDef,
                        armorHealth, armorValue, headGearName, headGearDef, headGearVal,
                        headgearValue, headGearMainstat, shieldName, shieldDef,
                        shieldBlockChance, shieldValue);

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
	//this->maxHealth = 1;
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
void Hero::ChangeEQ(shared_ptr<Item>&i, shared_ptr<View> view)
{
	this->EQ->ChangeItem(i);
	this->setAllStats();

	view->CompletedEqChanging();
	return;
}
bool Hero::fight(shared_ptr<Character>& opponent,bool boss, shared_ptr<View> view)
{
	bool whoIsAttacking = true;
	chrono::milliseconds timespan(1000);
	while (this->getcurrentHealth() != 0 && opponent->getcurrentHealth() != 0)
	{
        view->BreakLine();
		if (whoIsAttacking)
		{
			this->attackOpponent(opponent, view);
		}
		else
		{
			shared_ptr<Character> h = this->getInstance();
			opponent->attackOpponent(h, view);
		}
		whoIsAttacking = !whoIsAttacking;

		if (boss)
		{
			this_thread::sleep_for(timespan);
		}
	}
    view->BreakLine();
	return this->getcurrentHealth() != 0;
}
void Observer::setTrue()
{
	this->endik = true;
}
bool Observer::getEndik()
{
	return this->endik;
}
bool Observer::check(shared_ptr<View> view)
{
	if (this->getEndik())
	{
        view->EndGameMessage();
		return true;
	}
	else
		return false;
}
void Observer::removeFromObserver()
{
	this->h->DeleteObserver(shared_from_this());
}
void Observer::addToObserver()
{
	this->h->AddObserver(shared_from_this());
}