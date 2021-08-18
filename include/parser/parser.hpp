#pragma once

#include "ast/ast.hpp"
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"
#include "helpers/string.hpp"

using namespace Aul::AST;
using Aul::Lexer;

namespace Aul
{
    struct ParserError {
        string error;
        int line = 0;
        int col = 0;
    };

    class Parser
    {
    private:
        Lexer lexer;

    public:
        Token currentToken;
        Token peekToken;

        vector<ParserError> errors = { };

        Parser(Lexer lexer);

        Program parseProgram();
        Statement* parseStatement();
        LocalStatement* parseLocalStatement();

        void nextToken();
        bool currentTokenIs(TokenType type);
        bool currentTokenIsNot(TokenType type);
        bool peekTokenIs(TokenType type);
        bool peekTokenIsNot(TokenType type);
        bool expectPeek(TokenType type);
    };
} // namespace Aul
