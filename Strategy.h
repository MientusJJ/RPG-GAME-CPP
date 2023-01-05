#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H
#include "Character.h"

class Strategy
{
public:
	void setStartingPrice(int p_value) { this->m_startingPrice = p_value, this->m_currentPrice = p_value; return; }
	Strategy(shared_ptr<Hero>& h);
	bool buyingProcess(int price);
protected:
	int getStartPrice() { return m_startingPrice; }
	int getCurrentPrice() { return m_currentPrice; }
	void setCurrentPrice(int p_value) { this->m_currentPrice = p_value; return; }
	virtual bool makeNewPrice( int p_heroPrice) = 0;
	shared_ptr<Hero> h;
private:
	int m_startingPrice;
	int m_currentPrice;
	void takeMoney();
};

class StandardStrategy : public Strategy
{
public:
	StandardStrategy(shared_ptr<Hero> h);
private:
	bool makeNewPrice(int p_heroPrice) override;
};
#endif
