#include "Order.h"

using namespace std;

Order::Order(const int type, const int side, const float price, const int qty) {
	this->type = type;
	this->side = side;
	this->qty = qty;
	this->price = price;
	this->toFill = qty;
}

Order::Order(const int type, const int side, const int qty) {
	this->type = type;
	this->side = side;
	this->qty = qty;
	this->toFill = qty;
	this->price = 0;
}