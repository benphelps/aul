#pragma once

#include <string>
#include <stdio.h>

using std::string;

namespace Lexer {
    typedef string TokenType;
    typedef string TokenLiteral;

    class Token {
    public:
        TokenType Type;
        TokenLiteral Literal;

        Token(const TokenType &type, const TokenLiteral &literal) : Type(type), Literal(literal) {}
        Token() {};
    };

    // Special
    const TokenType ILLEGAL("ILLEGAL");
    const TokenType END_OF_FILE("EOF");

    // Identifiers & Literals
    const TokenType IDENT("IDENT");
    const TokenType INT("INT");

    // Operators
    const TokenType ASSIGN("=");
    const TokenType PLUS("+");

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
}
