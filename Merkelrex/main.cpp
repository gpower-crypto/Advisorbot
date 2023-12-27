#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Advisorbot.h"

int main()
{
    Advisorbot app{};
    app.init();
}

/*

#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <user_message>\n";
        return 1;
    }

    const char* userMessage = argv[1];
    const char* serverEndpoint = "http://localhost:3000/message";

    // Replace the following line with the actual path to curl.exe on your system
    const char* curlPath = "C:\\Windows\\SysWOW64\\curl.exe";

    // Create the command to send the user message to the server
    char command[256];
    snprintf(command, sizeof(command), "%s -X POST -H \"Content-Type: application/json\" -d \"{\\\"message\\\":\\\"%s\\\"}\" %s", curlPath, userMessage, serverEndpoint);

    // Execute the command using std::system
    std::cout << "Sending request to Node.js server...\n";
    int result = std::system(command);

    if (result == -1) {
        std::cerr << "Error executing command.\n";
        return 1;
    }

    return 0;
}
*/