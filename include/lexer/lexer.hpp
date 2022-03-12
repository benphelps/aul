#pragma once

#include "lexer/token.hpp"
#include <cstdio>
#include <string>
#include <utility>

using std::string;

namespace Aul
{
    struct LexedNumber {
        string value;
        TokenType type;

        LexedNumber(string value, TokenType type)
            : value(std::move(value))
            , type(type) {};
    };

    class Lexer
    {
    private:
        string input;
        int position = 0;
        int read_position = 0;
        char ch = 0;
        static bool isLetter(char test);
        static bool isDigit(char test);
        string readIdentifier();
        LexedNumber readNumber();
        char peekChar();
        static TokenType lookupIdentifier(const TokenLiteral& identifier);

        int current_line = 1;
        int current_col = 1;

    public:
        explicit Lexer(string input);
        void readChar();
        void stepBack();
        void skipWhitespace();
        Token nextToken();
    };
} // namespace Aul
