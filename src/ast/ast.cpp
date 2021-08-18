#include "ast/ast.hpp"

namespace Aul
{
    namespace AST
    {
        TokenLiteral Program::tokenLiteral()
        {
            if (this->statements.size() > 0) {
                return this->statements.front()->tokenLiteral();
            }
            return ""s;
        }

        string Program::stringLiteral()
        {
            stringstream buffer;

            for (auto&& statement : this->statements) {
                buffer << statement->stringLiteral();
            }

            return buffer.str();
        }
    } // namespace AST
} // namespace Aul
