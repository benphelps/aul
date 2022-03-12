#include "ast/ast.hpp"

namespace Aul::AST
{
    TokenLiteral Identifier::tokenLiteral()
    {
        return this->token.literal;
    }

    string Identifier::stringLiteral()
    {
        return this->value;
    }
} // namespace Aul::AST
