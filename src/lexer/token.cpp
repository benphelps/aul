#include "lexer/token.hpp"

std::ostream& operator<<(std::ostream& os, const Aul::Token& tk)
{
    os << "Type: " << tk.Type << " Literal: " << tk.Literal;
    return os;
}
