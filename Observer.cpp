#include "Observer.h"

void Observer::setTrue()
{
	this->endik = true;
}
bool Observer::getEndik()
{
	return this->endik;
}
bool Observer::check()
{
	if (this->getEndik())
	{
		cout << endGameMessage << endl;
		return true;
	}
	else
		return false;
}
