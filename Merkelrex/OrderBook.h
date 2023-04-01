#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    /** construct, reading a csv data file*/
    OrderBook(std::string filename);
    /** return a vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the set filters*/
    std::vector<OrderBookEntry> getOrders( OrderBookType type,
                                           std::string product,
                                           std::string timestamp );

    /** returns the earliest time in the order book */
    std::string getEarliestTime();

    /** returns the next time after the sent time in the order book
     *  If there is no next timestamp, wraps around to the start
    */
    std::string getNextTime(std::string timestamp);

    // I have added this function
    /** returns the previous timeframe */
    std::string getPreviousTime(std::string timestamp); 

    void insertOrder(OrderBookEntry& order);

    int matchAsksToBids(std::string product, std::string timestamp);

    /** return the price of the highest bid in the sent set */
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    /** return the price of the lowest bid in the sent set */
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

private:
    std::vector<OrderBookEntry> orders;
};