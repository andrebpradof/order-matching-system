# Order Matching System
A c++ matching engine for market and limit orders.

## Features
For the implementation of the engine, a FIFO structure was considered, in this way the limit orders are filled according to the order of receipt.

* There are the following complexities for the main operations:

  * Find the best price for a market order: O(1).

  * Insertion: O(log n).

Assume n is the average number of quotes in the order book.

## **Requirements:**
* C++20
* gcc 9.3.0 or newer

## Install
`$ make`

## Run
`$ cd bin/main`
