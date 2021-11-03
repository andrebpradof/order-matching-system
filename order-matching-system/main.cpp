#include "common.h"
#include "Order.h"
#include "Orderbook.h"

#ifndef MAIN_C
#define MAIN_C

vector<string>* splitLine(string commandOrder, vector<string> *words) {
	char delimiter = ' ';
	istringstream sstream(commandOrder);
	string word;
	while (getline(sstream, word, delimiter)) {
		word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
		words->push_back(word);
	}
	return words;
}

int main(int argc, char** argv) {

	string commandOrder;

	cout << "Order Matching System \n";
	Orderbook* orderbook = new Orderbook();

	cout << "Please enter with the orders: " << endl;

	while (1) {
		Order *order;
		vector<string> words{};
		cout << ">> ";
		getline(cin, commandOrder);
		splitLine(commandOrder, &words);

		if (words[0] == "limit") {
			if (words[1] == "sell") {
				order = new Order(LIMIT, SELL, stoi(words[2]), stoi(words[3]));
			}
			else {
				order = new Order(LIMIT, BUY, stoi(words[2]), stoi(words[3]));
			}
		}
		else {
			if (words[1] == "sell") {
				order = new Order(MARKET, SELL, stoi(words[2]));
			}
			else {
				order = new Order(MARKET, BUY, stoi(words[2]));
			}
		}
		orderbook->processOrder(order);
	}
}

#endif

