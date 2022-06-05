#include "Character.h"

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
	opponent->getDamage(damage);
	cout << this->getName() << " dealt " << damage << " damage to " << opponent->getName() << endl;
	cout << "Current health of " << opponent->getName() << " is " << opponent->getcurrentHealth();
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
			cout << opponent->getName() << " block the hit from " << this->getName() << endl;
			return false;
		}
		return true;
	}
}