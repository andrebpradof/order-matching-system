#include "Orderbook.h"


int Orderbook::stopClause(Order* orderInProcess) {
	if (orderInProcess->getSide() == BUY) {
		if (orderInProcess->getType() == LIMIT) {
			return ((this->asks.size() > 0) && (orderInProcess->getPrice() >= this->asks.top()->getPrice()));
		}
		else if (orderInProcess->getType() == MARKET) {
			return this->asks.size() > 0;
		}
	}
	else {
		if (orderInProcess->getType() == LIMIT) {
			return ((this->bids.size() > 0) && (orderInProcess->getPrice() <= this->bids.top()->getPrice()));
		}
		else if (orderInProcess->getType() == MARKET) {
			return this->bids.size() > 0;
		}
	}
}

void Orderbook::processOrder(Order* orderInProcess) {
	int qty = 0;
	while (Orderbook::stopClause(orderInProcess)) {
		Order *auxOrder = NULL;

		if (orderInProcess->getSide() == SELL) {
			auxOrder = this->bids.top();
			this->bids.pop();
		}
		else {
			auxOrder = this->asks.top();
			this->asks.pop();
		}

		if (orderInProcess->getToFill() == auxOrder->getToFill()) {
			qty = orderInProcess->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;
			break;
		}
		else if (orderInProcess->getToFill() > auxOrder->getToFill()) {
			qty = auxOrder->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;
		}
		else if (orderInProcess->getToFill() < auxOrder->getToFill()) {
			qty = orderInProcess->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;

			if (auxOrder->getSide() == SELL) {
				this->asks.push(auxOrder);
			}
			else {
				this->bids.push(auxOrder);
			}
			break;
		}
	}

	if (orderInProcess->getToFill() > 0 && orderInProcess->getType() == LIMIT) {
		if (orderInProcess->getSide() == SELL) {
			this->asks.push(orderInProcess);
		}
		else {
			this->bids.push(orderInProcess);
		}
	}
}

