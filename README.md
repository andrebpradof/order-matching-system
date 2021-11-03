# Order Matching System
A c++ matching engine for market and limit orders.

## Features
* For the implementation of the engine, a FIFO structure was considered, in this way the limit orders are filled according to the order of receipt.
*For the main operations, there is:

**Matching: O(1)

**Insertion: O(log n)

Assume n is the average number of quotes in the orderbook

### **Requirements:**
* C++20
* gcc 9.3.0 or newer

### Install
`$ make`

### Install
`$ cd bin/main`
