#pragma once

#include "lexer/token.hpp"
#include <utility>
#include <vector>
#include <sstream>

using namespace std::string_literals;
using std::string;
using std::stringstream;
using std::vector;

using Aul::Token;
using Aul::TokenLiteral;

namespace Aul::AST
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
        TokenLiteral tokenLiteral() override = 0;
        string stringLiteral() override = 0;
    };

    class Expression : public Node
    {
    public:
        TokenLiteral tokenLiteral() override = 0;
        string stringLiteral() override = 0;
    };

    class Program : public Node
    {
    public:
        vector<Statement*> statements;
        TokenLiteral tokenLiteral() override;
        string stringLiteral() override;

        Program() = default;
        explicit Program(vector<Statement*> statements) : statements(std::move(statements)) { };
    };

    class Identifier : public Expression
    {
    public:
        Token token;
        string value;

        TokenLiteral tokenLiteral() override;
        string stringLiteral() override;

        Identifier(Token token, string value) : token(std::move(token)), value(std::move(value)) { };
        Identifier() = default;
    };

    class LocalStatement : public Statement
    {
    public:
        Token token;
        Identifier name;
        Expression* value;

        TokenLiteral tokenLiteral() override;
        string stringLiteral() override;

        LocalStatement() = default;
        LocalStatement(Token token, Identifier name, Expression* value) : token(std::move(token)), name(std::move(name)), value(value) { };
    };

    class ReturnStatement : public Statement
    {
    public:
        Token token;
        Expression* value;

        TokenLiteral tokenLiteral() override;
        string stringLiteral() override;

        ReturnStatement() = default;
    };

    class ExpressionStatement : public Statement
    {
    public:
        Token token;
        Expression* value{};

        TokenLiteral tokenLiteral() override;
        string stringLiteral() override;

        ExpressionStatement() = default;
    };

    class Error : public Expression
    {
    public:
        Token token;

        TokenLiteral tokenLiteral() override {
            return Expression::tokenLiteral();
        }

        string stringLiteral() override {
            return Expression::stringLiteral();
        }

        Error() = default;
    };
} // namespace Aul
