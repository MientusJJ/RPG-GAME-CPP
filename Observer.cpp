#include "Observer.h"

//void Observer::add(shared_ptr<Chamber> ch)
//{
//	listofChambers.push_back(ch);
//}
void Observer::setTrue()
{
	//for(auto &v:listofChambers)
	//{
		//v->setEndFunction();
	//}
	cout << endGameMessage << endl;
}
Observer::~Observer()
{
	//this->listofChambers.clear();
}