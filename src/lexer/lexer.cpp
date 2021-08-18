#include "lexer/lexer.hpp"

namespace Aul
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

        if (this->ch == '\n') {
            this->current_line++;
            this->current_col = 1;
        } else {
            this->current_col++;
        }

        this->position = this->read_position;
        this->read_position += 1;
    }

    void Lexer::stepBack()
    {
        this->read_position -= 1;
        this->position = this->read_position;
        this->ch = this->input[this->read_position];
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

    Token Lexer::nextToken()
    {
        this->skipWhitespace();

        Token token;

        int token_line = this->current_line;
        int token_col = this->current_col;


        switch (this->ch) {
        case '=':
            if (this->peekChar() == '=') {
                char ch = this->ch;
                this->readChar();
                TokenLiteral literal = string(1, ch) + string(1, this->ch);
                token = Token(TokenType::EQ, literal);
            } else {
                token = Token(TokenType::ASSIGN, TokenLiteral(1, this->ch));
            }
            break;
        case '!':
            if (this->peekChar() == '=') {
                char ch = this->ch;
                this->readChar();
                TokenLiteral literal = string(1, ch) + string(1, this->ch);
                token = Token(TokenType::NOT_EQ, literal);
            } else {
                token = Token(TokenType::BANG, TokenLiteral(1, this->ch));
            }
            break;
        case '+':
            token = Token(TokenType::PLUS, TokenLiteral(1, this->ch));
            break;
        case '-':
            token = Token(TokenType::MINUS, TokenLiteral(1, this->ch));
            break;
        case '*':
            token = Token(TokenType::ASTERISK, TokenLiteral(1, this->ch));
            break;
        case '/':
            token = Token(TokenType::SLASH, TokenLiteral(1, this->ch));
            break;
        case '%':
            token = Token(TokenType::MODULO, TokenLiteral(1, this->ch));
            break;
        case ';':
            token = Token(TokenType::SEMICOLON, TokenLiteral(1, this->ch));
            break;
        case '(':
            token = Token(TokenType::LPAREN, TokenLiteral(1, this->ch));
            break;
        case ')':
            token = Token(TokenType::RPAREN, TokenLiteral(1, this->ch));
            break;
        case ',':
            token = Token(TokenType::COMMA, TokenLiteral(1, this->ch));
            break;
        case '{':
            token = Token(TokenType::LBRACE, TokenLiteral(1, this->ch));
            break;
        case '}':
            token = Token(TokenType::RBRACE, TokenLiteral(1, this->ch));
            break;
        case '<':
            token = Token(TokenType::LT, TokenLiteral(1, this->ch));
            break;
        case '>':
            token = Token(TokenType::GT, TokenLiteral(1, this->ch));
            break;
        case 0:
            token = Token(TokenType::END_OF_FILE, TokenLiteral(""));
            break;
        default:
            if (this->isLetter(this->ch)) {
                TokenLiteral literal = TokenLiteral(this->readIdentifier());
                TokenType type = this->lookupIdentifier(literal);

                token = Token(type, literal);

                return token;
            } else if (this->isDigit(this->ch)) {
                LexedNumber number = this->readNumber();
                TokenLiteral literal = TokenLiteral(number.value);
                TokenType type = number.type;
                token = Token(type, literal);
            } else {
                token = Token(TokenType::ILLEGAL, TokenLiteral(1, this->ch));
            }
            break;
        }

        token.line = token_line;
        token.col = token_col;

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
        int current_pos = this->position;

        while (this->isDigit(this->ch) || (!have_decimal && this->ch == '.' && this->isDigit(this->peekChar()))) {
            if (this->ch == '.') {
                have_decimal = true;
            }

            this->readChar();
        }

        string value = this->input.substr(current_pos, (this->position - current_pos));
        this->stepBack();

        if (have_decimal) {
            return LexedNumber(value, TokenType::DOUBLE);
        }
        return LexedNumber(value, TokenType::INT);
    }

    bool Lexer::isLetter(char test)
    {
        return 'a' <= test && test <= 'z' || 'A' <= test && test <= 'Z' || test == '_';
    }

    bool Lexer::isDigit(char test)
    {
        return '0' <= test && test <= '9';
    }

    TokenType Lexer::lookupIdentifier(TokenLiteral identifier)
    {
        if (Keywords.contains(identifier)) {
            return Keywords.find(identifier)->second;
        };

        return TokenType::IDENT;
    }
} // namespace Aul
