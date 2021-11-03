#include "common.h"

#ifndef ORDER_H
#define ORDER_H


class Order
{
public:
	Order(const int type, const int side, const float price, const int qty);
	Order(const int type, const int side, const int qty);

private:
	int type;
	int side;
	int qty;
	float price;
	int toFill;

public:
	int   getType()  { return type;  };
	int   getSide()  { return side;  };
	int   getQty()   { return qty;   };
	float getPrice() { return price; };
	int getToFill() { return toFill; };

	void setToFill(int val) {
		int rest = this->toFill - val;
		if (rest >= 0) {
			this->toFill = rest;
		}
	}

};

#endif

