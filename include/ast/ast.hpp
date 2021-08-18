#pragma once

#include "lexer/token.hpp"
#include <vector>
#include <sstream>

using namespace std::string_literals;
using std::string;
using std::stringstream;
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
            virtual string stringLiteral() = 0;
        };

        class Statement : public Node
        {
        public:
            virtual TokenLiteral tokenLiteral() = 0;
            virtual string stringLiteral() = 0;
        };

        class Expression : public Node
        {
        public:
            virtual TokenLiteral tokenLiteral() = 0;
            virtual string stringLiteral() = 0;
        };

        class Program : public Node
        {
        public:
            vector<Statement*> statements;
            TokenLiteral tokenLiteral();
            string stringLiteral();

            Program() {};
            Program(vector<Statement*> statements) : statements(statements) { };
        };

        class Identifier : public Expression
        {
        public:
            Token token;
            string value;

            TokenLiteral tokenLiteral();
            string stringLiteral();

            Identifier(Token token, string value) : token(token), value(value) { };
            Identifier() { };
        };

        class LocalStatement : public Statement
        {
        public:
            Token token;
            Identifier name;
            Expression* value;

            TokenLiteral tokenLiteral();
            string stringLiteral();

            LocalStatement() { };
            LocalStatement(Token token, Identifier name, Expression* value) : token(token), name(name), value(value) { };
        };

        class ReturnStatement : public Statement
        {
        public:
            Token token;
            Expression* value;

            TokenLiteral tokenLiteral();
            string stringLiteral();

            ReturnStatement() { };
        };

        class ExpressionStatement : public Statement
        {
        public:
            Token token;
            Expression* value;

            TokenLiteral tokenLiteral();
            string stringLiteral();

            ExpressionStatement() { };
        };

        class Error : public Expression
        {
        public:
            Token token;

            TokenLiteral tokenLiteral();
            string stringLiteral();

            Error() { };
        };
    } // namespace AST
} // namespace Aul
