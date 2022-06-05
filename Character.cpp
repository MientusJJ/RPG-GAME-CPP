#include "Character.h"
string namesforMonsters[]
{
	"The Rainbow Mutant","The Crying Doll","The Icy Snake","The Night Worm","The Young Babbler","The Bruised Gorilla","The Venom Serpent"
};
const int sizenamesforMonsters = 7;
double chance()
{
	return rand() % 100;
}
Character::Character() {

}
Character::~Character() {
	delete Class;
	
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
void Character::attackOpponent(Character * opponent)
{
	if (!this->useSpecialEffect(opponent))
	{
		return;
	}
	int damage = rand() % this->getmaximalAttack() + this->getminimalAttack();
	damage = damage * this->useSpecialAttack() - opponent->getdefense();
	if (damage < 1) damage = 1;
	opponent->getDamage(damage);
	cout << this->getName() << " dealt " << damage << " damage to " << opponent->getName() << endl;
	cout << "Current health of " << opponent->getName() << " is " << opponent->getcurrentHealth() << endl;;
	return;
}
////////////jeszcze nie zrobione
bool Character::useSpecialEffect(Character *opponent)
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
		if (chance() <= block)
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
	this->setspecialAbility("You have 50 percent chance to dodge your opponent's attack");
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
	int p = rand() % 3 + 1;
	if (p == 1)
	{
		this->Class = new Warrior;
	}
	else if (p == 2)
	{
		this->Class = new Scout;
	}
	else
	{
		this->Class = new Mage;
	}
}
void monster::setmaxHealth()
{
	this->maxHealth = 20 * this->getlevel()*this->Class->getvitalityModifier();
	this->setcurrentHealth(this->maxHealth);
	return;
}
void monster::setdefense()
{
	this->defense = 3 * this->getlevel()*this->Class->getdefenseModifier();
	return;
}
void monster::setlevel(int l)
{
	this->level = l;
	return;
}
void monster::setminimalAttack()
{
	this->minimalAttack = 2 * this->getlevel()*this->Class->getattackModifier();
	return;
}
void monster::setmaximalAttack()
{
	this->maximalAttack = 5 * this->getlevel()*this->Class->getattackModifier();
	return;
}
void monster::setName()
{
	int r = rand() % sizenamesforMonsters;
	this->name = namesforMonsters[r];
	return;
}
monster::monster(int lvl)
{
	this->chooseClass();
	this->setName();
	this->setlevel(lvl);
	this->setmaxHealth();
	this->setdefense();
	this->setminimalAttack();
	this->setmaximalAttack();
	this->setcriticalChance(33);
}
monster::~monster()
{
	delete Class;
}
Hero *Hero::hero = nullptr;
Hero *Hero::getInstance()
{
	if (hero == nullptr)
	{
		hero = new Hero();
	}
	return hero;
}
Hero::Hero()
{
	setName();
	chooseClass();
	setlevel(1);
}
Hero::~Hero()
{
	delete EQ;
}
void Hero::chooseClass()
{
	bool p;
	cout << "Choose class of " << this->getName() << "Write 1 if you want warrior \n Write 2 if you want scout \n Write 3 if you want mage \n ";
	int ch;
	cin >> ch;
	while (ch<1 || ch >3)
	{
		cout << "Bad Number. Choose number between 1 and 3\n";
		cin >> ch;
	}
	cout << "Your class for the whole game is: ";
	if (ch == 1)
	{
		this->Class = new Warrior;
		cout << "Warrior\n";
	}
	else if (ch == 2)
	{
		this->Class = new Scout;
		cout << "Scout\n";
	}
	else
	{
		this->Class = new Mage;
		cout << "Mage\n";
	}

}
void Hero::setmaxHealth(int) { return; }
void Hero::setdefense(int s) { return; }
void Hero::setlevel(int s )
{
	this->level = s;
}

void Hero::setminimalAttack(int s) { return; }
void Hero::setmaximalAttack(int s) { return; }
void Hero::setName()
{
	cout << "Write name of your hero: ";
	string n;
	cin >> n;
	this->name = n;
	return;
}
void Hero::levelup()
{
	++this->level;
	return;
}
void Hero::showStatistics()
{
	cout << "Statistics of your hero" << endl;
	cout << "Name: " << this->getName() << endl;
	cout << "Class: " << this->Class->getProfName() << endl;
	cout << "Main Stat: " << this->Class->getmainStatName() << endl;
	cout << "Skill: " << this->Class->getspecialAbility() << endl;
	cout << "Level: " << this->getlevel() << endl;
	cout << "Max health: " << this->getmaxHealth() << endl;
	cout << "Current health" << this->getcurrentHealth() << endl;
	cout << "Minimal damage: " << this->getminimalAttack() << endl;
	cout << "Maximal damage: " << this->getmaximalAttack() << endl;
	cout << "Critical chance: " << this->getcriticalChance() << "%" << endl;
	cout << "Defence: " << this->getdefense() << endl;
	cout << "Amount of money: " << this->getMoney() << endl;
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