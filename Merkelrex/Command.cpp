#include "Command.h"
#include<vector>
#include<string>

Command::Command()
{

}

std::vector<std::string> Command::tokenise(std::string userInput, char separater)
{
    // CODE below is from the module lectures

    std::vector<std::string> tokens;
    std::string token;

    signed int start, end;

    start = userInput.find_first_not_of(separater, 0);

    do
    {
        end = userInput.find_first_of(separater, start);

        if (start == userInput.length() || start == end)
            break;

        if (end >= 0)
            token = userInput.substr(start, end - start);

        else
            token = userInput.substr(start, userInput.length() - start);

        tokens.push_back(token);

        start = end + 1;

    } while (end > 0);

    return tokens;
}