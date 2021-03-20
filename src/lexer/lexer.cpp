#include "lexer/lexer.hpp"

namespace Lexer {
    Lexer::Lexer(string input)
    {
        this->input = input;
        this->readChar();
    }

    void Lexer::readChar()
    {
        if (this->read_position > this->input.length()) {
            this->ch = 0;
        } else {
            this->ch = this->input[this->read_position];
        }

        this->position = this->read_position;
        this->read_position += 1;
    }

    Token Lexer::nextToken()
    {
        Token token;

        switch (this->ch) {
        case '=':
            token = Token(ASSIGN, TokenLiteral(1, this->ch));
            break;
        case ';':
            token = Token(SEMICOLON, TokenLiteral(1, this->ch));
            break;
        case '(':
            token = Token(LPAREN, TokenLiteral(1, this->ch));
            break;
        case ')':
            token = Token(RPAREN, TokenLiteral(1, this->ch));
            break;
        case ',':
            token = Token(COMMA, TokenLiteral(1, this->ch));
            break;
        case '+':
            token = Token(PLUS, TokenLiteral(1, this->ch));
            break;
        case '{':
            token = Token(LBRACE, TokenLiteral(1, this->ch));
            break;
        case '}':
            token = Token(RBRACE, TokenLiteral(1, this->ch));
            break;
        case 0:
            token = Token(END_OF_FILE, TokenLiteral(""));
            break;
        }

        this->readChar();
        return token;
    }
}
