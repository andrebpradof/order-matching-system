#include "Order.h"
#include "common.h"

#ifndef ORDERBOOK_H
#define ORDERBOOK_H


using namespace std;

struct ComparePriceGrowing
{
	bool operator()(Order* const& order1, Order* const& order2)
	{
		return order1->getPrice() > order2->getPrice();
	}
};

struct ComparePriceDescending
{
	bool operator() (Order* const& order1, Order* const& order2)
	{
		return order1->getPrice() < order2->getPrice();
	}
};

class Orderbook
{
public:

	priority_queue<Order*, vector<Order*>, ComparePriceDescending> bids;
	priority_queue<Order*, vector<Order*>, ComparePriceGrowing> asks;
	void processOrder(Order *orderInProcess);

private:
	int stopClause(Order *orderInProcess);
};

#endif
