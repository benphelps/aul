#pragma once

#include "lexer/token.hpp"
#include <stdio.h>
#include <string>

using std::string;

namespace Aul
{
    struct LexedNumber {
        string value;
        TokenType type;

        LexedNumber(string value, TokenType type)
            : value(value)
            , type(type) {};
    };

    class Lexer
    {
    private:
        string input = "";
        int position = 0;
        int read_position = 0;
        char ch = 0;
        bool isLetter(char test);
        bool isDigit(char test);
        string readIdentifier();
        LexedNumber readNumber();
        char peekChar();
        TokenType lookupIdentifier(TokenLiteral identifier);

        int current_line = 1;
        int current_col = 1;

    public:
        Lexer(string input);
        void readChar();
        void stepBack();
        void skipWhitespace();
        Token nextToken();
    };
} // namespace Aul
