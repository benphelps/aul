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

    char Lexer::peekChar()
    {
        if (this->read_position > this->input.length()) {
            return 0;
        }
        return this->input[this->read_position];
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
        case '+':
            token = Token::Token(Token::PLUS, Token::TokenLiteral(1, this->ch));
            break;
        case '-':
            token = Token::Token(Token::MINUS, Token::TokenLiteral(1, this->ch));
            break;
        case '*':
            token = Token::Token(Token::ASTERISK, Token::TokenLiteral(1, this->ch));
            break;
        case '/':
            token = Token::Token(Token::SLASH, Token::TokenLiteral(1, this->ch));
            break;
        case '%':
            token = Token::Token(Token::MODULO, Token::TokenLiteral(1, this->ch));
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
        case '{':
            token = Token::Token(Token::LBRACE, Token::TokenLiteral(1, this->ch));
            break;
        case '}':
            token = Token::Token(Token::RBRACE, Token::TokenLiteral(1, this->ch));
            break;
        case '<':
            token = Token::Token(Token::LT, Token::TokenLiteral(1, this->ch));
            break;
        case '>':
            token = Token::Token(Token::GT, Token::TokenLiteral(1, this->ch));
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
                LexedNumber number = this->readNumber();
                Token::TokenLiteral literal = Token::TokenLiteral(number.value);
                Token::TokenType type = number.type;
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

    LexedNumber Lexer::readNumber()
    {
        bool have_decimal = false;
        int position = this->position;

        while (this->isDigit(this->ch) || (have_decimal == false && this->ch == '.' && this->isDigit(this->peekChar()))) {
            if (this->ch == '.') {
                have_decimal = true;
            }

            this->readChar();
        }

        string value = this->input.substr(position, (this->position - position));

        if (have_decimal) {
            return LexedNumber(value, Token::DOUBLE);
        }
        return LexedNumber(value, Token::INT);
    }

    bool Lexer::isLetter(char test)
    {
        return 'a' <= test && test <= 'z' || 'A' <= test && test <= 'Z' || test == '_';
    }

    bool Lexer::isDigit(char test)
    {
        return '0' <= test && test <= '9';
    }

    Token::TokenType Lexer::lookupIdentifier(Token::TokenLiteral identifier)
    {
        if (Token::KEYWORDS.contains(identifier)) {
            return Token::KEYWORDS.find(identifier)->second;
        };

        return Token::IDENT;
    }
} // namespace Lexer
