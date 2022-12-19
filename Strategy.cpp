#include "Strategy.h"
#include <iostream>

bool StandardStrategy::makeNewPrice(int p_wallet, int p_heroPrice)
{
	bool l_flag{ false };
	if(p_heroPrice>p_wallet)
	{
		std::cout << "You don't have that amount of money" << std::endl;
	}
	else if(p_heroPrice<this->getStartPrice()/2)
	{
		std::cout << "I won't sell this item for nothing!!!!" << std::endl;
	}
	else if(p_heroPrice>=this->getCurrentPrice())
	{
		l_flag = true;
		std::cout << "This price is fair. I can sell you this item" << std::endl;
	}
	else
	{
		int l_newPrice{ this->getCurrentPrice() + p_heroPrice / 2 };
		std::cout << "This price is too low, but I can propose: " << l_newPrice << std::endl;
		this->setCurrentPrice(l_newPrice);
	}
	std::cout << "Current price: " << this->getCurrentPrice();
	return l_flag;
}