#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H
#include "Character.h"

class Strategy
{
public:
	void setStartingPrice(int p_value) { this->m_startingPrice = p_value, this->m_currentPrice = p_value; return; }
	virtual bool makeNewPrice(shared_ptr<Hero>& h, int p_heroPrice) = 0;
protected:
	int getStartPrice() { return m_startingPrice; }
	int getCurrentPrice() { return m_currentPrice; }
	void setCurrentPrice(int p_value) { this->m_currentPrice = p_value; return; }
private:
	int m_startingPrice;
	int m_currentPrice;

};

class StandardStrategy : public Strategy
{
	bool makeNewPrice(shared_ptr<Hero>& h,int p_heroPrice) override;
};
#endif
