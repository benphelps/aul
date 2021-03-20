#pragma once

#include <string>
#include "lexer/token.hpp"

using std::string;

namespace Lexer {
    class Lexer {
    private:
        string input = "";
        int position = 0;
        int read_position = 0;
        char ch = 0;
    public:
        Lexer(string input);
        void readChar();
        Token::Token nextToken();
    };
}
