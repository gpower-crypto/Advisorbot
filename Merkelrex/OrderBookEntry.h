#pragma once
#include <string>

enum class OrderBookType
{
    bid,
    ask,
    unknown,
    asksale,
    bidsale
};

class OrderBookEntry
{
public:
    OrderBookEntry( double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType,
                    std::string username = "dataset" );

    // it is declared as static because it doesn't depend on any of the other 
    // data members and is a standalone function
    static OrderBookType convertToOrderBookType(std::string s);

    static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    }

    static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }

    static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }

    double price; // data members of the class OrderBookEntry
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};