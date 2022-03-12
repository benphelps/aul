#pragma once

#include <iostream>
#include <map>
#include <string>
#include <utility>

using std::map;
using std::vector;
using std::string;

namespace Aul
{
    typedef string TokenLiteral;

    #define TOKEN_TYPES(_) \
        _(ILLEGAL) \
        _(END_OF_FILE) \
        _(IDENT) \
        _(INT) \
        _(DOUBLE) \
        _(ASSIGN) \
        _(PLUS) \
        _(MINUS) \
        _(BANG) \
        _(ASTERISK) \
        _(SLASH) \
        _(MODULO) \
        _(LT) \
        _(GT) \
        _(EQ) \
        _(NOT_EQ) \
        _(COMMA) \
        _(SEMICOLON) \
        _(LPAREN) \
        _(RPAREN) \
        _(LBRACE) \
        _(RBRACE) \
        _(FUNCTION) \
        _(LOCAL) \
        _(END) \
        _(THEN) \
        _(TRUE) \
        _(FALSE) \
        _(IF) \
        _(ELSE) \
        _(RETURN)

    #define AS_TYPE(_) _,
    #define AS_TYPE_STR(_) #_,

    typedef enum {
        TOKEN_TYPES(AS_TYPE)
    } TokenType;

    static const char* sTokenType[] = {
    #define X(String) MACROSTR(_),
        TOKEN_TYPES(AS_TYPE_STR)
    #undef X
    };

    const map<string, TokenType> Keywords {
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

    class Token
    {
    public:
        TokenLiteral literal;
        TokenType type;

        int line = 0;
        int col = 0;

        Token(TokenType type, TokenLiteral literal)
            : type(type)
            , literal(std::move(literal))
        {
        }

        Token() = default;
    };
} // namespace Aul

std::ostream& operator<<(std::ostream& os, const Aul::Token& tk);
std::ostream& operator<<(std::ostream& os, const Aul::TokenType& tt);
