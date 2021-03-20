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

    Token::Token Lexer::nextToken()
    {
        Token::Token token;

        switch (this->ch) {
        case '=':
            token = Token::Token(Token::ASSIGN, Token::TokenLiteral(1, this->ch));
            break;
        case ';':
            token = Token::Token(Token::SEMICOLON, Token::TokenLiteral(1, this->ch));
            break;
        case '(':
            token = Token::Token(Token::LPAREN, Token::TokenLiteral(1, this->ch));
            break;
        case ')':
            token = Token::Token(Token::RPAREN, Token::TokenLiteral(1, this->ch));
            break;
        case ',':
            token = Token::Token(Token::COMMA, Token::TokenLiteral(1, this->ch));
            break;
        case '+':
            token = Token::Token(Token::PLUS, Token::TokenLiteral(1, this->ch));
            break;
        case '{':
            token = Token::Token(Token::LBRACE, Token::TokenLiteral(1, this->ch));
            break;
        case '}':
            token = Token::Token(Token::RBRACE, Token::TokenLiteral(1, this->ch));
            break;
        case 0:
            token = Token::Token(Token::END_OF_FILE, Token::TokenLiteral(""));
            break;
        }

        this->readChar();
        return token;
    }
}
