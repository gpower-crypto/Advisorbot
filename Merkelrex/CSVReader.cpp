#include "CSVReader.h"
#include <iostream>
#include <fstream>


CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{ csvFilename };
    std::string line;

    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception& e)
            {
                std::cout << "CSVReader::readCSV recieved bad data" << std::endl;
            }

        } // end of while loop
    }
    std::cout << "CSVReader::readCSV() read " << entries.size() << " entries" << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separater)
{
    std::vector<std::string> tokens;
    std::string token;

    signed int start = 0, end = 0;

    start = csvLine.find_first_not_of(separater, 0);

    do
    {
        end = csvLine.find_first_of(separater, start);

        if (start == csvLine.length() || start == end)
            break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);

        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);

        start = end + 1;

    } while (end > 0);

    return tokens;
}

// returns a single order book entry from each input entry of tokens
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line" << std::endl;
        throw std::exception{}; // will crash and give an error 
    }

    try
    {
        // we have 5 tokens
        price = std::stod(tokens[3]); // convert string to double
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception& e)
    {
        std::cout << "Bad float! " << tokens[3] << std::endl;
        std::cout << "Bad float! " << tokens[4] << std::endl;
        throw; // will throw out the exception
    }

    OrderBookEntry obe{ price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::convertToOrderBookType(tokens[2]) };

    return obe; // returns the order book entry object
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
    std::string amountString,
    std::string timestamp,
    std::string product,
    OrderBookType orderType)
{
    double price, amount;
    try
    {
        // we have 5 tokens
        price = std::stod(priceString); // convert string to double
        amount = std::stod(amountString);
    }
    catch (const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
        throw; // will throw out the exception
    }

    OrderBookEntry obe{ price,
                        amount,
                        timestamp,
                        product,
                        orderType };
    return obe;
}