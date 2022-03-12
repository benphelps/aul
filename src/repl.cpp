#include <readline/readline.h>
#include <readline/history.h>
#include "aul.hpp"

using namespace Aul;

int main(int argc, char const* argv[])
{
    Signal::Setup();

    // disable readline <tab> to autocomplete filenames
    rl_bind_key('\t', rl_insert);

    std::cout << "Welcome to the Aul REPL! You can exit by pressing Ctrl+C at any time..." << std::endl;

    char* buf;
    while ((buf = readline(">> ")) != nullptr) {
        if (strlen(buf) > 0) {
            add_history(buf);
        }

        Lexer lexer = Lexer(buf);
        Parser parser = Parser(lexer);
        Program program = parser.parseProgram();

//        for (Token token = lexer.nextToken(); token.type != TokenType::END_OF_FILE; token = lexer.nextToken()) {
//            std::cout << token.literal << std::endl;
//        }

        std::cout << program.stringLiteral() << std::endl;
        std::cout << buf << std::endl;

        free(buf);
    }
}
