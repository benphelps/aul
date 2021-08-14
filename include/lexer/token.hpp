#pragma once

#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;

namespace Aul
{
    namespace Lexer
    {
        typedef string TokenType;
        typedef string TokenLiteral;

        class Token
        {
        public:
            TokenType Type;
            TokenLiteral Literal;

            Token(const TokenType& type, const TokenLiteral& literal)
                : Type(type)
                , Literal(literal)
            {
            }
            Token() {};
        };

        // Special
        const TokenType ILLEGAL("ILLEGAL");
        const TokenType END_OF_FILE("EOF");

        // Identifiers & Literals
        const TokenType IDENT("IDENT");
        const TokenType INT("INT");
        const TokenType DOUBLE("DOUBLE");

        // Operators
        const TokenType ASSIGN("=");
        const TokenType PLUS("+");
        const TokenType MINUS("-");
        const TokenType BANG("!");
        const TokenType ASTERISK("*");
        const TokenType SLASH("/");
        const TokenType MODULO("%");
        const TokenType LT("<");
        const TokenType GT(">");

        // Equality
        const TokenType EQ("==");
        const TokenType NOT_EQ("!=");

        // Delimiters
        const TokenType COMMA(",");
        const TokenType SEMICOLON(";");
        const TokenType LPAREN("(");
        const TokenType RPAREN(")");
        const TokenType LBRACE("{");
        const TokenType RBRACE("}");

        // Keywords
        const TokenType FUNCTION("FUNCTION");
        const TokenType LOCAL("LOCAL");
        const TokenType END("END");
        const TokenType THEN("THEN");
        const TokenType TRUE("TRUE");
        const TokenType FALSE("FALSE");
        const TokenType IF("IF");
        const TokenType ELSE("ELSE");
        const TokenType RETURN("RETURN");

        const map<string, TokenType> KEYWORDS {
            { "function", FUNCTION },
            { "end", END },
            { "local", LOCAL },
            { "then", THEN },
            { "true", TRUE },
            { "false", FALSE },
            { "if", IF },
            { "else", ELSE },
            { "return", RETURN }
        };
    } // namespace Lexer
} // namespace Aul

std::ostream& operator<<(std::ostream& os, const Aul::Lexer::Token& tk);
