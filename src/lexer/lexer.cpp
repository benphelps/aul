#include "lexer/lexer.hpp"

namespace Lexer
{
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

    void Lexer::skipWhitespace()
    {
        while (this->ch == ' ' || this->ch == '\t' || this->ch == '\n' || this->ch == '\r') {
            this->readChar();
        }
    }

    Token::Token Lexer::nextToken()
    {
        Token::Token token;

        this->skipWhitespace();

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
        default:
            if (this->isLetter(this->ch)) {
                Token::TokenLiteral literal = Token::TokenLiteral(this->readIdentifier());
                Token::TokenType type = this->lookupIdentifier(literal);

                token = Token::Token(type, literal);

                return token;
            } else if (this->isDigit(this->ch)) {
                Token::TokenLiteral literal = Token::TokenLiteral(this->readNumber());
                Token::TokenType type = Token::INT;

                token = Token::Token(type, literal);
            } else {
                token = Token::Token(Token::ILLEGAL, Token::TokenLiteral(1, this->ch));
            }
            break;
        }

        this->readChar();
        return token;
    }

    string Lexer::readIdentifier()
    {
        int position = this->position;
        while (this->isLetter(this->ch)) {
            this->readChar();
        }
        return this->input.substr(position, (this->position - position));
    }

    string Lexer::readNumber()
    {
        int position = this->position;
        while (this->isDigit(this->ch)) {
            this->readChar();
        }
        return this->input.substr(position, (this->position - position));
    }

    bool Lexer::isLetter(char test)
    {
        return 'a' <= test && test <= 'z' || 'A' <= test && test <= 'Z' || test == '_';
    }

    bool Lexer::isDigit(char test)
    {
        return '0' <= ch && ch <= '9';
    }

    Token::TokenType Lexer::lookupIdentifier(Token::TokenLiteral identifier)
    {
        if (Token::KEYWORDS.contains(identifier)) {
            return Token::KEYWORDS.find(identifier)->second;
        };

        return Token::IDENT;
    }
} // namespace Lexer
