#pragma once
#include "OrderBook.h"
#include<string>

class Advisorbot
{
public:
	Advisorbot();
	// I have taken help from the module given code for the init function
	void init(); // start the advisorbot 

private:
	/** print the start statement of the simulation */
	void printStartStatement();

	// I have taken help from the module given code for the getUserInput function
	/** get the user input */
	std::string getUserInput();

	/** print help message */
	void printHelp();

	/** print help message for chosen command */
	void helpCommand(std::string command);

	// I have taken help from code from the module lectures
	/** list all available products */
	void listProducts();

	// I have written the code for the checkProduct function
	/** check if product is available in order book*/
	bool checkProduct(std::string product);

	// I have written the code for the findMin function
	/** find minimum bid or ask for product in current time step */
	void findMin(std::string product, OrderBookType type);

	// I have written the code for the findMax function
	/** find maximum bid or ask for product in current time step */
	void findMax(std::string product, OrderBookType type);

	// I have taken help from the module given code for the printSuccessfulMatches function
	/** print successful matches for each product in the current timestamp */
	void printSuccessfulMatches();

	// I have written the code for the avg function
	/**  compute average ask or bid for the sent product over the sent number
    of time steps */
	void avg(std::string product, OrderBookType type, int numberOfTimestamps);

	// I have written the code for the predict function
	/** predict max or min ask or bid for the sent product for the next time
    step */
	void predict(std::string product, OrderBookType type, std::string extremeType);

	// I have written the code for the variance function
	/** find the variance for the product ask/bid prices in the current time step*/
	double variance(std::string product, OrderBookType type);

	// I have written the code for the standardDeviation function
	/** find the standard deviation for the product ask/bid prices in the current time step*/
	double standardDeviation(std::string product, OrderBookType type);

	// I have written the code for the skewness function
	/** find the skewness for the product ask/bid prices in the current time step*/
	double skewness(std::string product, OrderBookType type);

	// I have taken help from the module given code for the printCurrentTimeFrame function
	/**  state current time in dataset */
	void printCurrentTimeframe();

	// I have taken help from the module given code for the gotoNextTimeframe function
	/**  move to next time step */
	void gotoNextTimeframe();

	// I have written the code for the processUserInput function
	/**  process the user input */
	void processUserInput(std::string userInput);

	// I have written the code for the printErrorMessage function
	/** print error message for invalid user input */
	void printErrorMessage(); 

	// I have written the code for the exitProgram function
	/** exit the program */
	void exitProgram();

	/** keep track of current time frame of the dataset */
	std::string currentTime;

	OrderBook orderBook{ "20200601.csv" };
};

