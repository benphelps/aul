#include "aul.hpp"

using namespace Aul;

int main(int argc, char const* argv[])
{
    Signal::Setup();

    while (true) {
        std::cout << "aul > ";

        string input;
        std::getline(std::cin, input);

        // handle errors and ctrl + d
        if (!std::cin) {
            Signal::Action(SIGQUIT);
            return 0;
        }

        Lexer lexer = Lexer(input);
        Parser parser = Parser(lexer);
        Program program = parser.parseProgram();

        // for (Token token = lexer.nextToken(); token.type != TokenType::END_OF_FILE; token = lexer.nextToken()) {
        //     std::cout << token << std::endl;
        // }

        std::cout << program.stringLiteral() << std::endl;

        std::cout << input << std::endl;
    }
}
