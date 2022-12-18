#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy
{
	virtual int makeNewPrice(int p_wallet, int p_actualPrice, int p_previousPrice) = 0;
	
};

class StandardStrategy : public Strategy
{
	int makeNewPrice(int p_wallet, int p_actualPrice, int p_previousPrice) override;
};
#endif
