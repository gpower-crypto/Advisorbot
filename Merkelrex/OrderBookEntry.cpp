// implementation of the class in a cpp file

#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType,
    std::string _username)

    : price(_price),
      amount(_amount),
      timestamp(_timestamp),
      product(_product),
      orderType(_orderType),
      username(_username)
{

}

OrderBookType OrderBookEntry::convertToOrderBookType(std::string s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}
