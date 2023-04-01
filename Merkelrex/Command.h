#pragma once
#include<vector>
#include<string>

class Command
{
	public:
		Command();

		// code for tokenise funciton is used from module given code
		/** function to tokenise the user input */
		static std::vector<std::string> tokenise(std::string userInput, char separater);
};