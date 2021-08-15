#pragma once

#include "lexer/token.hpp"
#include <vector>

using namespace std::string_literals;
using std::string;
using std::vector;

using Aul::Token;
using Aul::TokenLiteral;

namespace Aul
{
    namespace AST
    {
        class Node
        {
        public:
            virtual TokenLiteral tokenLiteral() = 0;
        };

        class Statement : public Node
        {
        public:
            TokenLiteral tokenLiteral();
        };

        class Expression : public Node
        {
        public:
            TokenLiteral tokenLiteral();
        };

        class Program : public Node
        {
        public:
            vector<Statement> statements;
            TokenLiteral tokenLiteral();
        };

        class Identifier : public Expression
        {
        public:
            Token token;

            TokenLiteral tokenLiteral();
        };

        class LocalStatement : public Statement
        {
        public:
            Token token;
            Identifier name;
            Expression value;

            TokenLiteral tokenLiteral();
        };
    } // namespace AST
} // namespace Aul
