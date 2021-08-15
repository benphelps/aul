#include "parser/parser.hpp"

namespace Aul
{
    Parser::Parser(::Lexer lexer)
        : lexer(lexer)
    {
    }

    void Parser::nextToken()
    {
        this->currentToken = this->peekToken;
        this->peekToken = this->lexer.nextToken();
    }
} // namespace Aul
