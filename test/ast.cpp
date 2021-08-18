#include "test.hpp"

using namespace Aul::AST;

CATCH_TEST_CASE("Test AST", "[ast]")
{
    Program program = Program({ new LocalStatement(
        Token(TokenType::LOCAL, "local"),
        Identifier(Token(TokenType::IDENT, "foo"), "foo"),
        new Identifier(Token(TokenType::IDENT, "bar"), "bar")) });

    CATCH_REQUIRE(program.stringLiteral() == "local foo = bar"s);
}
