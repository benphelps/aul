#pragma once

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"

using Aul::AST::Program;
using Aul::Lexer;

namespace Aul
{
    class Parser
    {
    private:
        Lexer lexer;

    public:
        Token currentToken;
        Token peekToken;

        Parser(Lexer lexer);
        void nextToken();

        Program parseProgram();
    };
} // namespace Aul
