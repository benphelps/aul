#pragma once

#include "lexer/token.hpp"
#include <stdio.h>
#include <string>

using std::string;

namespace Lexer
{
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
        string readNumber();
        Token::TokenType lookupIdentifier(Token::TokenLiteral identifier);

    public:
        Lexer(string input);
        void readChar();
        void skipWhitespace();
        Token::Token nextToken();
    };
} // namespace Lexer
