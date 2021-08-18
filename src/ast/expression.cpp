#include "ast/ast.hpp"

namespace Aul
{
    namespace AST
    {
        TokenLiteral Identifier::tokenLiteral()
        {
            return this->token.literal;
        }

        string Identifier::stringLiteral()
        {
            return this->value;
        }
    } // namespace AST
} // namespace Aul
