#include "ast/ast.hpp"

namespace Aul
{
    namespace AST
    {
        TokenLiteral Statement::tokenLiteral()
        {
            return ""s;
        }

        TokenLiteral Expression::tokenLiteral()
        {
            return ""s;
        }

        TokenLiteral Program::tokenLiteral()
        {
            if (this->statements.size() > 0) {
                return this->statements.front()->tokenLiteral();
            }
            return ""s;
        }

        TokenLiteral Identifier::tokenLiteral()
        {
            return this->token.literal;
        }

        TokenLiteral LocalStatement::tokenLiteral()
        {
            return this->token.literal;
        }
    } // namespace AST
} // namespace Aul
