#include "ast/ast.hpp"

namespace Aul::AST
{
    TokenLiteral LocalStatement::tokenLiteral()
    {
        return this->token.literal;
    }

    string LocalStatement::stringLiteral()
    {
        stringstream literal;

        literal << this->tokenLiteral() << " " << this->name.value << " = ";

        if (this->value) {
            literal << this->value->stringLiteral();
        }

        return literal.str();
    }

    TokenLiteral ReturnStatement::tokenLiteral()
    {
        return this->token.literal;
    }

    string ReturnStatement::stringLiteral()
    {
        stringstream literal;

        literal << this->tokenLiteral() << " ";

        if (this->value) {
            literal << this->value->stringLiteral();
        }

        return literal.str();
    }

    TokenLiteral ExpressionStatement::tokenLiteral()
    {
        return this->token.literal;
    }

    string ExpressionStatement::stringLiteral()
    {
        if (this->value) {
            return this->value->stringLiteral();
        }

        return ""s;
    }
} // namespace Aul::AST
