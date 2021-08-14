#pragma once

#include "lexer/token.hpp"
#include <stdio.h>
#include <string>

using std::string;

namespace Aul
{
    namespace Lexer
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

        public:
            Lexer(string input);
            void readChar();
            void stepBack();
            void skipWhitespace();
            Token nextToken();
        };
    } // namespace Lexer
} // namespace Aul
