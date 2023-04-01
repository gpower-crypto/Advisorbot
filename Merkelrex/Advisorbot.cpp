#include "Advisorbot.h"
#include <iostream>
#include <vector>
#include <string>
#include<cmath>
#include "Command.h"

Advisorbot::Advisorbot()
{
	
}

void Advisorbot::init()
{
	std::string input; // store the user input
	currentTime = orderBook.getEarliestTime();

	while (true)
	{
		printStartStatement();
		input = getUserInput(); 
		processUserInput(input);
	}
}

void Advisorbot::printStartStatement()
{
	std::cout << "\n" << "advisorbot> Please enter a command, or help for a list of commands" << std::endl;
}

std::string Advisorbot::getUserInput()
{
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void Advisorbot::printHelp()
{
	std::cout << "advisorbot> The available commands are help, help <cmd>, prod, min, max, matchStats, avg, predict, VAR, SD, skewness, time, step, exit." << std::endl;
}

void Advisorbot::helpCommand(std::string command)
{
	if (command == "prod")
	{
		std::cout << "prod (list available products) -> ETH/BTC, DOGE/BTC,.." << std::endl;
	}
	else if (command == "min")
	{
		std::cout << "Example: min ETH/BTC ask -> The min ask for ETH/BTC is 1.0" << std::endl;
	}
	else if (command == "max")
	{
		std::cout << "Example: max ETH/BTC ask -> The max ask for ETH/BTC is 1.0" << std::endl;
	}
	else if (command == "matchStats")
	{
		std::cout << "print all the successful matches for each product in current timeframe" << std::endl;
	}
	else if (command == "avg")
	{
		std::cout << "Example: avg ETH/BTC ask 10 -> The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
	}
	else if (command == "predict")
	{
		std::cout << "Example: predict max ETH/BTC bid -> The average ETH/BTC max bid price over the last 10 timesteps was 1.0" << std::endl;
	}
	else if (command == "VAR")
	{
		std::cout << "Example: VAR ETH/BTC bid -> The Variance for the product ETH/BTC bid price in the current timestep is 1.0" << std::endl;
	}
	else if (command == "SD")
	{
		std::cout << "Example: SD ETH/BTC bid -> The Standard Deviation for the product ETH/BTC bid price in the current timestep is 1.0" << std::endl;
	}
	else if (command == "skewness")
	{
		std::cout << "Example: skewness ETH/BTC bid -> The Skewness for the product ETH/BTC bid price in the current timestep is 1.0" << std::endl;
	}
	else if (command == "time")
	{
		std::cout << "time (state current time in dataset) -> 2020/03/17 17:01:24" << std::endl;
	}
	else if (command == "step")
	{
		std::cout << "step (move to next time step) -> now at 2020/03/17 17:01:30" << std::endl;
	}
	else if (command == "exit")
	{
		std::cout << "exit the advisorbot program" << std::endl;
	}
	else
	{
		printErrorMessage();
	}
}

void Advisorbot::listProducts()
{
	std::cout << "advisorbot> Products:" << std::endl;
	for (std::string const& p : orderBook.getKnownProducts())
	{
		std::cout << p << std::endl;
	}
}

bool Advisorbot::checkProduct(std::string product)
{
	for (std::string const& p : orderBook.getKnownProducts())
	{
		if (product == p)
		{
			return true;
		}
	}
	return false;
}

void Advisorbot::findMin(std::string product, OrderBookType type)
{
	std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, currentTime); 

	if (type == OrderBookType::ask) // check if ask or bid
	{
		std::cout << "advisorbot> The min ask for " << product << " is " << orderBook.getLowPrice(entries) << std::endl;
	}
	else
	{
		std::cout << "advisorbot> The min bid for " << product << " is " << orderBook.getLowPrice(entries) << std::endl;
	}
}

void Advisorbot::findMax(std::string product, OrderBookType type)
{
	std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, currentTime);

	if (type == OrderBookType::ask) // check if order type is ask or bid
	{
		std::cout << "advisorbot> The max ask for " << product << " is " << orderBook.getHighPrice(entries) << std::endl;
	}
	else
	{
		std::cout << "advisorbot> The max bid for " << product << " is " << orderBook.getHighPrice(entries) << std::endl;
	}
}

void Advisorbot::printSuccessfulMatches()
{
	
	for (std::string const& p : orderBook.getKnownProducts())
	{
		
		std::cout << p << " - " << orderBook.matchAsksToBids(p, currentTime) << std::endl;
	}
}

void Advisorbot::avg(std::string product, OrderBookType type, int numberOfTimesteps)
{
	int orderSize = 0, i = 0; // orderSize will store the total number of orders

	double sum = 0, avg = 0; // sum will calculate the sum of all prices

	// create and initialise the temporary current time to the value of the current timestamp
	std::string tempCurrentTime = currentTime;

	while (i < numberOfTimesteps && tempCurrentTime > orderBook.getEarliestTime())
	{
		tempCurrentTime = orderBook.getPreviousTime(tempCurrentTime);

		std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, tempCurrentTime);
		
		for (OrderBookEntry& e : entries)
		{
			sum += e.price;
			orderSize += entries.size();
		}
		i++;
	}

	// check if the user has atleast crossed one timestep
	if (i != 0)
	{
		avg = sum / orderSize; // calculate average

		if (i < numberOfTimesteps) // check if the user has crossed the required number of timesteps in the dataset
		{
			std::cout << "advisorbot> You have crossed only " << i << " timestamps in the dataset" << std::endl;
		}

		if (type == OrderBookType::ask) // check if order type is ask or bid
		{
			std::cout << "advisorbot> The average " << product << " ask price over the last "
				<< i << " timestamps was " << avg << std::endl;
		}
		else
		{
			std::cout << "advisorbot> The average " << product << " bid price over the last "
				<< i << " timestamps was " << avg << std::endl;
		}
	}
	else
	{
		std::cout << "advisorbot> You have not crossed any timesteps so there is no average" << std::endl;
	}	
}

void Advisorbot::predict(std::string product, OrderBookType type, std::string extremeType)
{
	std::string tempCurrentTime = currentTime; // store the current timestep in a temporary variable

	double sum = 0, avg = 0; // sum will calculate the sum of all the prices
	int i = 0, numberOfTimesteps = 10;

	while ( i < numberOfTimesteps && tempCurrentTime > orderBook.getEarliestTime())
	{
		std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, tempCurrentTime);

		if (extremeType == "max")
		{
			sum += orderBook.getHighPrice(entries);
		}
		else
		{
			sum += orderBook.getLowPrice(entries);
		}

		tempCurrentTime = orderBook.getPreviousTime(tempCurrentTime);
		i++;
	}

	// check if the user has atleast crossed one timestep
	if (i != 0)
	{
		avg = sum / i; // calculate average

		if (i < numberOfTimesteps)
		{
			std::cout << "advisorbot> You have crossed only " << i << " timestamps in the dataset" << std::endl;
		}

		if (type == OrderBookType::ask) // check if order type is ask or bid
		{
			if (extremeType == "max") // check if min or max
			{
				std::cout << "advisorbot> The average " << product << " max ask price over the last " << i << " timesteps was " << avg << std::endl;
			}
			else
			{
				std::cout << "advisorbot> The average " << product << " min ask price over the last " << i << " timesteps was " << avg << std::endl;
			}
		}
		else
		{
			if (extremeType == "max")
			{
				std::cout << "advisorbot> The average " << product << " max bid price over the last " << i << " timesteps was " << avg << std::endl;
			}
			else
			{
				std::cout << "The average " << product << " min bid price over the last " << i << " timesteps was " << avg << std::endl;
			}
		}
	}
	else
	{
		std::cout << "advisorbot> You have not crossed any timesteps so there is no average prediction" << std::endl;
	}
}


double Advisorbot::variance(std::string product, OrderBookType type)
{
	double sum = 0, avg = 0, x = 0, varianceSum = 0, variance = 0; // sum will calculate the sum of all prices

	std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, currentTime);

	for (OrderBookEntry& e : entries)
	{
		sum += e.price;
	}

	avg = sum / entries.size();

	for (OrderBookEntry& e : entries)
	{
		 x = avg - e.price;
		 varianceSum += pow(x, 2);
	}

	variance = varianceSum / entries.size();
	return variance;	
}


double Advisorbot::standardDeviation(std::string product, OrderBookType type)
{
	double standardDeviation = sqrt(variance(product, type));
	return standardDeviation;
}

double Advisorbot::skewness(std::string product, OrderBookType type) 
{
	double sum = 0, avg = 0, standardDev = 0, x = 0;

	std::vector<OrderBookEntry> entries = orderBook.getOrders(type, product, currentTime);

	for (OrderBookEntry& e : entries)
	{
		sum += e.price;
	}

	avg = sum / entries.size();

	standardDev = standardDeviation(product, type);

	for (OrderBookEntry& e : entries)
	{
		x = avg - e.price;
		sum += pow(x, 3);
	}
	double skewness = sum / ( (entries.size() - 1) * pow(standardDev, 3) );
	return skewness;
}


void Advisorbot::printCurrentTimeframe()
{
	std::cout << "advisorbot> " << currentTime << std::endl;
}

void Advisorbot::gotoNextTimeframe()
{
	currentTime = orderBook.getNextTime(currentTime);
	std::cout << "advisorbot> now at " << currentTime << std::endl;
}

void Advisorbot::printErrorMessage()
{
	std::cout << "advisorbot> Bad input, please enter correct command" << std::endl;
}

void Advisorbot::exitProgram()
{
	exit(0); // exit the program
}

void Advisorbot::processUserInput(std::string userInput)
{
	std::vector<std::string> tokens;

	tokens = Command::tokenise(userInput, ' '); // tokenise the user input

	if (tokens.size() == 0 || tokens.size() > 4)  // check if user input is empty 
	{
		printErrorMessage();
	}

	if (tokens.size() == 1)
	{
		if (tokens[0] == "help")
		{
			printHelp();
		}
		else if (tokens[0] == "prod")
		{
			listProducts();
		}
		else if (tokens[0] == "matchStats")
		{
			printSuccessfulMatches();
		}
		else if (tokens[0] == "time")
		{
			printCurrentTimeframe();
		}
		else if (tokens[0] == "step")
		{
			gotoNextTimeframe();
		}
		else if (tokens[0] == "exit")
		{
			exitProgram();
		}
		else
		{
			printErrorMessage();
		}
	}

	if (tokens.size() == 2)
	{
		if (tokens[0] == "help")
		{
			helpCommand(tokens[1]); // call function helpCammand to check and describe the command to the user
		}
		else
		{
			printErrorMessage();
		}
	}

	if (tokens.size() == 3)
	{
		if (checkProduct(tokens[1])) // check if the product entered is in the dataset
		{
			if (tokens[0] == "min") // check if min or max
			{
				if (tokens[2] == "ask")
				{
					findMin(tokens[1], OrderBookType::ask);
				}
				else if (tokens[2] == "bid")
				{
					findMin(tokens[1], OrderBookType::bid);
				}
				else 
				{
					printErrorMessage();
				}
			}
			else if (tokens[0] == "max")
			{
				if (tokens[2] == "ask")
				{
					findMax(tokens[1], OrderBookType::ask);
				}
				else if (tokens[2] == "bid")
				{
					findMax(tokens[1], OrderBookType::bid);
				}
				else
				{
					printErrorMessage();
				}
			}
			else if (tokens[0] == "VAR")
			{
				if (tokens[2] == "ask")
				{
					std::cout << "advisorbot> The Variance for product " << tokens[1] << " ask price in the current timestep is " << variance(tokens[1], OrderBookType::ask) << std::endl;
				}
				else if (tokens[2] == "bid")
				{
					std::cout << "advisorbot> The Variance for product " << tokens[1] << " bid price in the current timestep is " << variance(tokens[1], OrderBookType::bid) << std::endl;
				}
				else
				{
					printErrorMessage();
				}

			}
			else if (tokens[0] == "SD")
			{
				if (tokens[2] == "ask")
				{
					std::cout << "advisorbot> The Standard Deviation for product " << tokens[1] << " ask price in the current timestep is " << variance(tokens[1], OrderBookType::ask) << std::endl;
				}
				else if (tokens[2] == "bid")
				{
					std::cout << "advisorbot> The Standard Deviation for product " << tokens[1] << " bid price in the current timestep is " << variance(tokens[1], OrderBookType::bid) << std::endl;
				}
				else
				{
					printErrorMessage();
				}
			}
			else if (tokens[0] == "skewness")
			{
				if (tokens[2] == "ask")
				{
					std::cout << "advisorbot> The Skewness for product " << tokens[1] << " ask price in the current timestep is " << skewness(tokens[1], OrderBookType::ask) << std::endl;
				}
				else if (tokens[2] == "bid")
				{
					std::cout << "advisorbot> The Skewness for product " << tokens[1] << " bid price in the current timestep is " << skewness(tokens[1], OrderBookType::bid) << std::endl;
				}
				else
				{
					printErrorMessage();
				}
			}
			else
			{
				printErrorMessage();
			}
		}
		else
		{
			std::cout << "The product " << tokens[1] << " is not in the dataset." << std::endl;
		}
	}

	if (tokens.size() == 4)
	{
		if (tokens[0] == "avg")
		{
			int numberOfTimestamps = 0;

			if (checkProduct(tokens[1]))
			{
				try // check if user input is integer or not
				{
					numberOfTimestamps = stoi(tokens[3]);
				}
				catch (const std::exception& e)
				{
					std::cout << "Bad Integer! " << tokens[3] << std::endl;
					return;
				}

				if (tokens[2] == "ask")
				{
					avg(tokens[1], OrderBookType::ask, numberOfTimestamps);
				}
				else if (tokens[2] == "bid")
				{
					avg(tokens[1], OrderBookType::bid, numberOfTimestamps);
				}
				else
				{
					printErrorMessage();
				}
			}
			else
			{
				std::cout << "The product " << tokens[1] << " is not in the dataset." << std::endl;
			}
		}

		else if (tokens[0] == "predict")
		{
			if (checkProduct(tokens[2]))
			{
				if (tokens[1] == "max" || tokens[1] == "min")
				{
					if (tokens[3] == "ask")
					{
						predict(tokens[2], OrderBookType::ask, tokens[1]);
					}
					else if (tokens[3] == "bid")
					{
						predict(tokens[2], OrderBookType::bid, tokens[1]);
					}
					else
					{
						printErrorMessage();
					}
				}
				else
				{
					printErrorMessage();
				}
			}
			else
			{
				std::cout << "The product " << tokens[2] << " is not in the dataset." << std::endl;
			}
		}

		else
		{
			printErrorMessage();
		}
	}

	

	
}