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

    typedef Expression* (*PrefixParser)();
    typedef Expression* (*InfixParser)(Expression *);

    class Parser
    {
    private:
        Lexer lexer;

    public:
        Token currentToken;
        Token peekToken;

        vector<ParserError> errors = { };

        explicit Parser(Lexer lexer);

        Program parseProgram();
        Statement* parseStatement();
        LocalStatement* parseLocalStatement();
        ReturnStatement* parseReturnStatement() const;

        void nextToken();
        bool currentTokenIs(TokenType type) const;
        bool currentTokenIsNot(TokenType type) const;
        bool peekTokenIs(TokenType type) const;
        bool peekTokenIsNot(TokenType type) const;
        bool expectPeek(TokenType type);
    };
} // namespace Aul
