#include "parser/parser.hpp"

namespace Aul
{
    namespace Parser
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
    } // namespace Parser
} // namespace Aul
