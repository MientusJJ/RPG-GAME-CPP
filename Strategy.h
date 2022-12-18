#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H


class Strategy
{
public:
	Strategy(int p_value) : m_startingPrice(p_value), m_currentPrice(p_value){};
	virtual bool makeNewPrice(int p_wallet, int p_heroPrice) = 0;
protected:
	int getStartPrice() { return m_startingPrice; }
	int getCurrentPrice() { return m_currentPrice; }
	void setCurrentPrice(int p_value) { this->m_currentPrice = p_value; return; }
private:
	const int m_startingPrice;
	int m_currentPrice;

};

class StandardStrategy : public Strategy
{
	bool makeNewPrice(int p_wallet,int p_heroPrice) override;
};
#endif
