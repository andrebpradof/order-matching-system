#include "common.h"
#include "Order.h"
#include "Orderbook.h"

#ifndef MAIN_C
#define MAIN_C

vector<string>* splitLine(string commandOrder, vector<string> *words) {
	stringstream test(commandOrder);
	string segment;

	while(std::getline(test, segment, ' '))
	{
		words->push_back(segment);
	}
	return words;

}

int main(int argc, char** argv) {

	
	Orderbook* orderbook = new Orderbook();

	string parameter = argv[1];

	if(!parameter.compare("test")){
		unsigned seed = time(0);
		srand(seed);
		
		vector<Order*> orders;

		int numOrders = 50;

		for(int i=0; i<numOrders; i++){
			if(rand()%2 == 0){
				if(rand()%2 == 0){
					orders.push_back(new Order(LIMIT, SELL, rand()%4+1, rand()%200+1));
				}
				else{
					orders.push_back(new Order(LIMIT, BUY, rand()%4+1, rand()%200+1));
				}
			}
			else{
				if(rand()%2 == 0){
					orders.push_back(new Order(MARKET, SELL, rand()%200+1));
				}
				else{
					orders.push_back(new Order(MARKET, BUY, rand()%200+1));
				}
			}
		}

		for(int i=0; i<numOrders; i++){
			orderbook->processOrder(orders[i]);
		}
	}
	else{
		string commandOrder;

		cout << "Order Matching System \n";

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
			else if (words[0] == "market") {
				if (words[1] == "sell") {
					order = new Order(MARKET, SELL, stoi(words[2]));
				}
				else {
					order = new Order(MARKET, BUY, stoi(words[2]));
				}
			}
			else if (words[0] == "exit"){
				exit(0);
			}
			orderbook->processOrder(order);
		}
	}
}

#endif

