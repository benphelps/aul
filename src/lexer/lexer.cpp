#include "lexer/lexer.hpp"

namespace Aul
{
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
            Token token;

            this->skipWhitespace();

            switch (this->ch) {
            case '=':
                if (this->peekChar() == '=') {
                    char ch = this->ch;
                    this->readChar();
                    TokenLiteral literal = string(1, ch) + string(1, this->ch);
                    token = Token(EQ, literal);
                } else {
                    token = Token(ASSIGN, TokenLiteral(1, this->ch));
                }
                break;
            case '!':
                if (this->peekChar() == '=') {
                    char ch = this->ch;
                    this->readChar();
                    TokenLiteral literal = string(1, ch) + string(1, this->ch);
                    token = Token(NOT_EQ, literal);
                } else {
                    token = Token(BANG, TokenLiteral(1, this->ch));
                }
                break;
            case '+':
                token = Token(PLUS, TokenLiteral(1, this->ch));
                break;
            case '-':
                token = Token(MINUS, TokenLiteral(1, this->ch));
                break;
            case '*':
                token = Token(ASTERISK, TokenLiteral(1, this->ch));
                break;
            case '/':
                token = Token(SLASH, TokenLiteral(1, this->ch));
                break;
            case '%':
                token = Token(MODULO, TokenLiteral(1, this->ch));
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
            case '{':
                token = Token(LBRACE, TokenLiteral(1, this->ch));
                break;
            case '}':
                token = Token(RBRACE, TokenLiteral(1, this->ch));
                break;
            case '<':
                token = Token(LT, TokenLiteral(1, this->ch));
                break;
            case '>':
                token = Token(GT, TokenLiteral(1, this->ch));
                break;
            case 0:
                token = Token(END_OF_FILE, TokenLiteral(""));
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
                    token = Token(ILLEGAL, TokenLiteral(1, this->ch));
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
                return LexedNumber(value, DOUBLE);
            }
            return LexedNumber(value, INT);
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
            if (KEYWORDS.contains(identifier)) {
                return KEYWORDS.find(identifier)->second;
            };

            return IDENT;
        }
    } // namespace Lexer
} // namespace Aul
