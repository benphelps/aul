#pragma once

#include "lexer/token.hpp"
#include <stdio.h>
#include <string>

using std::string;

namespace Lexer
{
    struct LexedNumber {
        string value;
        Token::TokenType type;

        LexedNumber(string value, Token::TokenType type)
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
        Token::TokenType lookupIdentifier(Token::TokenLiteral identifier);

    public:
        Lexer(string input);
        void readChar();
        void skipWhitespace();
        Token::Token nextToken();
    };
} // namespace Lexer
