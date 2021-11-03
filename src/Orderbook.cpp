#include "Orderbook.h"

// While stopping criterion
int Orderbook::stopClause(Order* orderInProcess) {
	if (orderInProcess->getSide() == BUY) {
		if (orderInProcess->getType() == LIMIT) {
			// Empty queue or unable to trade.
			return ((this->asks.size() > 0) && (orderInProcess->getPrice() >= this->asks.top()->getPrice()));
		}
		else if (orderInProcess->getType() == MARKET) {
			return this->asks.size() > 0;
		}
	}
	else {
		if (orderInProcess->getType() == LIMIT) {
			// Empty queue or unable to trade.
			return ((this->bids.size() > 0) && (orderInProcess->getPrice() <= this->bids.top()->getPrice()));
		}
		else if (orderInProcess->getType() == MARKET) {
			return this->bids.size() > 0;
		}
	}
	return 0;
}

// Process incoming orders
void Orderbook::processOrder(Order* orderInProcess) {
	int qty = 0;
	// As long as you can trade
	while (Orderbook::stopClause(orderInProcess)) {
		Order *auxOrder = NULL;

		// Get the best to buy
		if (orderInProcess->getSide() == SELL) {
			auxOrder = this->bids.top();
			this->bids.pop();
		}
		// Get the best to sell
		else {
			auxOrder = this->asks.top();
			this->asks.pop();
		}

		// If the order quantity are the same
		if (orderInProcess->getToFill() == auxOrder->getToFill()) {
			qty = orderInProcess->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;
			break;
		}
		// If the amount of shares in the current order is greater than the best buy or sell
		else if (orderInProcess->getToFill() > auxOrder->getToFill()) {
			qty = auxOrder->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;
		}
		// If the amount of shares in the current order is less than the best buy or sell
		else if (orderInProcess->getToFill() < auxOrder->getToFill()) {
			qty = orderInProcess->getToFill();
			orderInProcess->setToFill(qty);
			auxOrder->setToFill(qty);
			cout << "Trade, price: " << auxOrder->getPrice() << ", qty: " << qty << endl;

			// Save the rest of the best buy or sell
			if (auxOrder->getSide() == SELL) {
				this->asks.push(auxOrder);
			}
			else {
				this->bids.push(auxOrder);
			}
			break;
		}
	}

	// Saves the remainder of the current buy or sell
	if (orderInProcess->getToFill() > 0 && orderInProcess->getType() == LIMIT) {
		if (orderInProcess->getSide() == SELL) {
			this->asks.push(orderInProcess);
		}
		else {
			this->bids.push(orderInProcess);
		}
	}
}

