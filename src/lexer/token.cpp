#include "lexer/token.hpp"

std::ostream& operator<<(std::ostream& os, const Aul::Token& tk)
{
    os << "Type: " << tk.type << " Literal: " << tk.literal;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Aul::TokenType& tt)
{
    os << Aul::sTokenType[tt];
    return os;
}
