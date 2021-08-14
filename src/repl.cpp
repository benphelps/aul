#include <signal.h>
#include <stdlib.h>

#include "aul.hpp"

using namespace Aul::Lexer;

void my_handler(int s)
{
    std::cout << std::endl
              << "goodbye :)" << std::endl;
    exit(1);
}

int main(int argc, char const* argv[])
{
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    while (true) {
        std::cout << "aul > ";

        string input;
        std::getline(std::cin, input);

        // handle errors and ctrl + d
        if (!std::cin) {
            std::cout << std::endl
                      << "goodbye :)" << std::endl;
            return 0;
        }

        Lexer lexer = Lexer(input);

        for (Token token = lexer.nextToken(); token.Type != END_OF_FILE; token = lexer.nextToken()) {
            std::cout << token << std::endl;
        }

        std::cout << input << std::endl;
    }
}
